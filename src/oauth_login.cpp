#include<curl/curl.h>
#include<iostream>
#include"../headers/json/json.h"
#include"../headers/oauth_login.h"
using namespace std;
class httpRequest
{
    public:
        httpRequest();
        ~httpRequest();
        void setURL(string URL);
        void setRequestType(string type);
        void setRequestData(const char *data);//if the argument type is string, the response of the request will be error(why?)
        void appendRequestHeader(string header);
        void setRequestHeader();
        int sendRequest();
        string getResponse();
    private:
        CURL *curl;
        CURLcode res;
        struct curl_slist *headers=NULL;
        string url;
        unique_ptr<string> readBuffer=make_unique<string>();
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};
httpRequest::httpRequest()
{
    curl=curl_easy_init();
    if(curl)
    {
        cout<<"curl_easy_init() success"<<endl;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer.get());

    }
}
void httpRequest::setURL(string URL)
{
    url=URL;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
}
void httpRequest::setRequestType(string type)
{
    if(type=="POST")
        curl_easy_setopt(curl, CURLOPT_POST, 1);
    else if(type=="GET")
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    else
        cerr<<"request type error"<<endl;
}
void httpRequest::setRequestData(const char* data)
{
    //cout<<"data:"<<data.c_str()<<endl;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.size());
}
void httpRequest::setRequestHeader()
{
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}
size_t httpRequest::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size*nmemb);
    return size*nmemb;
}
void httpRequest::appendRequestHeader(string header)
{
    headers=curl_slist_append(headers, header.c_str());
}
int httpRequest::sendRequest()
{
    res=curl_easy_perform(curl);
    if(res!=CURLE_OK)
    {
        cerr<<"curl_easy_perform() failed: "<<curl_easy_strerror(res)<<endl;
        return -1;
    }
    return 0;
}
string httpRequest::getResponse()
{
    return *readBuffer;
}
httpRequest::~httpRequest()
{
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();
}

class codeInfo
{
    public:
    string client_id;
    string device_code;
    string user_code;
    string verification_uri;
    string expires_in;
    string interval;
    string message;
};

class tokenInfo
{
    public:
    string access_token;
    string refresh_token;
    string expires_in;
    string scope;
    string token_type;
};
void setClipBoard(const char* str)
{
    if (OpenClipboard(NULL))
    {
        EmptyClipboard();
        HGLOBAL hClip = GlobalAlloc(GMEM_MOVEABLE, strlen(str) + 1);
        char* pBuf;
        pBuf = (char*)GlobalLock(hClip);
        strcpy(pBuf, str);
        GlobalUnlock(hClip);
        SetClipboardData(CF_TEXT, hClip);
        CloseClipboard();
    }
}
codeInfo getDeviceCode(string client_id="6731de76-14a6-49ae-97bc-6eba6914391e")
{
    httpRequest request;

    request.setURL("https://login.microsoftonline.com/common/oauth2/v2.0/devicecode");
    request.setRequestType("POST");
    string httpArgs="client_id="+client_id+"&scope=user.read%20openid%20profile";
    request.setRequestData(httpArgs.c_str());

    request.sendRequest();
    string response=request.getResponse();
    Json::Value root;
    Json::Reader reader;
    string device_code;
    codeInfo info;
    if(reader.parse(response, root))
    {
        device_code=root["device_code"].asString();
        info.device_code=root["device_code"].asString();
        info.user_code=root["user_code"].asString();
        info.verification_uri=root["verification_uri"].asString();
        info.expires_in=root["expires_in"].asString();
        info.interval=root["interval"].asString();
        info.message=root["message"].asString();
        info.client_id=client_id;
    }
    else
    {
        cerr<<"parse json error"<<endl;
    }
    return info;
}
void authInBrowser(codeInfo info)
{
    cout<<"A browser will be opened to authenticate your account."<<endl;
    cout<<"Please enter the code to the browser: "<<info.user_code<<endl;
    cout<<"If you don't have a Microsoft account, please create one first."<<endl;
    cout<<"The code has been copied into your clipboard."<<endl;
    setClipBoard(info.user_code.c_str());
    cout<<"The code will expire in "<<info.expires_in<<" seconds, so you'd better hurry up!"<<endl;
    system("pause");
    string url=info.verification_uri;
    string cmd="start "+url;
    system(cmd.c_str());
    cout<<"If you finish the authentication, please press any key to continue."<<endl;
    system("pause");
    return;
}
tokenInfo getToken(codeInfo info)
{
    httpRequest request;
    request.setURL("https://login.microsoftonline.com/common/oauth2/v2.0/token");
    request.setRequestType("POST");
    string httpArgs="client_id="+info.client_id+"&scope=user.read%20openid%20profile&code="+info.device_code+"&grant_type=urn:ietf:params:oauth:grant-type:device_code";
    request.setRequestData(httpArgs.c_str());
    request.sendRequest();
    string response=request.getResponse();
    cout<<"response:"<<response<<endl;
    Json::Value root;
    Json::Reader reader;
    tokenInfo token;
    if(reader.parse(response, root))
    {
        token.access_token=root["access_token"].asString();
        token.refresh_token=root["refresh_token"].asString();
        token.expires_in=root["expires_in"].asString();
        token.scope=root["scope"].asString();
        token.token_type=root["token_type"].asString();
    }
    else
    {
        cerr<<"parse json error"<<endl;
    }
    return token;
}


void OAuth2Login()
{
    curl_global_init(CURL_GLOBAL_ALL);
    codeInfo info=getDeviceCode();
    authInBrowser(info);
    tokenInfo token=getToken(info);
    cout<<"access_token:"<<token.access_token<<endl;
    system("pause");
}
