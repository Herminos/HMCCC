#pragma once

#include<iostream>
#include<curl/curl.h>
using namespace std;

void OAuth2Login();

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