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

int downloadVersion(downloadOption option);

int download(string URL, string path);