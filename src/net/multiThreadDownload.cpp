#include<curl/curl.h>
using namespace std;
class multiThreadDownload
{
    public:
    CURLM *multiHandle;
    int stillRunning;
    multiThreadDownload()
    {
        multiHandle=curl_multi_init();
        stillRunning=0;
    }
    void addHandle(CURL *handle)
    {
        curl_multi_add_handle(multiHandle,handle);
    }
    void removeHandle(CURL *handle)
    {
        curl_multi_remove_handle(multiHandle,handle);
    }
    void perform()
    {
        curl_multi_perform(multiHandle,&stillRunning);
    }
    void wait()
    {
        curl_multi_wait(multiHandle,NULL,0,1000,NULL);
    }
    void close()
    {
        curl_multi_cleanup(multiHandle);
    }
};