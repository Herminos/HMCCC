#pragma once
#include"download.h"
#include"account.h"

class Account
{
    public:
    string userName;
    string uuid;
    string accessToken;
    string clientToken;
    string userType;
    Account(string userName,string uuid,string accessToken,string clientToken,string userType)
    {
        this->userName=userName;
        this->uuid=uuid;
        this->accessToken=accessToken;
        this->clientToken=clientToken;
        this->userType=userType;
    }
    Account(offlineAccount account)
    {
        this->userName=account.name;
        this->uuid=account.uuid;
        this->accessToken=account.accessToken;
        this->userType="offline";
    }
};



class launchOption
{
    public:
    string GameDir;
    string version;
    string versionName;
    string versionType="HMCCC";
    string defaultJVMArgs=" -XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow -Dfml.ignoreInvalidMinecraftCertificates=True -Dfml.ignorePatchDiscrepancies=True -Dlog4j2.formatMsgNoLookups=true -XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump";
    int maxMemory=2048;
    int minMemory=512;
    int height=480;
    int width=854;
    launchOption(downloadOption option)
    {
        this->GameDir=option.GameDir;
        this->version=option.version;
        this->versionName=option.versionName;
    };
};

class launchServerOption
{
    public:
    string serverDir;
    string serverName;
    string version;
    bool ifNoGui=false;
    int maxMemory=2048;
    int minMemory=512;
    string extraJVMArgs="";
    void setServerDir(string serverDir)
    {
        this->serverDir=serverDir;
    }
    void setServerName(string serverName)
    {
        this->serverName=serverName;
    }
    void setVersion(string version)
    {
        this->version=version;
    }
    launchServerOption(downloadServerOption option)
    {
        this->serverDir=option.serverDir;
        this->serverName=option.serverName;
        this->version=option.version;
    }
};
void launchGame(launchOption option,Account account);

void launchServer(launchServerOption option);