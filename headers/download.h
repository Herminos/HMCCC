#pragma once

#include <string>
using namespace std;

class downloadOption
{
    public:
    string version;
    string GameDir;
    string versionName;
    void setVersion(string version)
    {
        this->version=version;
    }
    void setGameDir(string GameDir)
    {
        this->GameDir=GameDir;
    }
    void setVersionName(string versionName)
    {
        this->versionName=versionName;
    }
};
class downloadServerOption
{
    public:
    string version;
    string serverDir;
    string serverName;
    
    void setVersion(string version)
    {
        this->version=version;
    }
    void setServerDir(string serverDir)
    {
        this->serverDir=serverDir;
    }
    void setServerName(string serverName)
    {
        this->serverName=serverName;
    }
};
int downloadVersion(downloadOption option);

int download(string URL, string path);

void mkMultiDir(string dir);

int downloadServer(downloadServerOption option);