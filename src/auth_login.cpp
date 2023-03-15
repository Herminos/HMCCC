#include<cpprest/http_client.h>
#include<cpprest/uri.h>
#include<cpprest/json.h>
#include<cpprest/http_listener.h>
#include<cpprest/oauth2.h>
#include<iostream>
#include<string>
#include<Windows.h>
#include<shellapi.h>
using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;
//打开浏览器
void openBrowser(const string& url)
{
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
class OAuth2_listener
{
public:
    OAuth2_listener(uri listen_uri):
        m_listener(new http_listener(listen_uri))
    {
        m_listener->support([this](http_request request)->void {
            //处理HTTP 请求
            if (request.request_uri().path() == U("/") &&
                request.request_uri().query() != U(""))
            {
                m_lock.lock();
                
                //处理返回的授权码,并设置为完成
                m_tce.set(true);
 
                request.reply(status_codes::OK, U("Ok."));
                m_lock.unlock();
            }
            else
            {
                request.reply(status_codes::NotFound, U("Not found"));
            }
        });
        m_listener->open().wait();//打开HTTP 监听
    }
 
    ~OAuth2_listener()
    {
        m_listener->close().wait();//关闭HTTP Listener
    }
 
    pplx::task<bool> listen_for_code()
    {
        return pplx::create_task(m_tce); //等待认证服务器的授权码
    }
private:
    std::unique_ptr<http_listener> m_listener; //HTTP监听
    pplx::task_completion_event<bool> m_tce;//收到授权码的确认事件
    std::mutex m_lock;
};
    //string URL="https://login.live.com/oauth20_authorize.srf?client_id=26797a23-6bd5-448a-8fe7-e9b936690b2a&response_type=code&scope=service%3A%3Auser.auth.xboxlive.com%3A%3AMBI_SSL&redirect_uri=http%3A%2F%2Flogin.live.com%2Foauth20_desktop.srf"
    //string URL="https://login.live.com/oauth20_authorize.srf?client_id=26797a23-6bd5-448a-8fe7-e9b936690b2a&response_type=code&scope=service%3A%3Auser.auth.xboxlive.com%3A%3AMBI_SSL&redirect_uri=https%3A%2F%2F127.0.0.1%3A30828&";
void oauthAuthorize()
{
    string URL="https://login.live.com/oauth20_authorize.srf?client_id=26797a23-6bd5-448a-8fe7-e9b936690b2a&response_type=code&scope=service%3A%3Auser.auth.xboxlive.com%3A%3AMBI_SSL&redirect_uri=https%3A%2F%2F127.0.0.1%3A30828&";
    openBrowser(URL);
    OAuth2_listener listener(U("https://127.0.0.1:30828"));
    listener.listen_for_code().wait();
}
