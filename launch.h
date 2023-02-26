#pragma once
#include"download.h"

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


void launchGame(launchOption option,Account account);




