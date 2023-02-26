#include<iostream>
#include<string>
#include"launch.h"
using namespace std;
class LaunchOption
{
    public:
    string GameDir;
    string versionName;
    string defaultJVMArgs=" -XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow -Dfml.ignoreInvalidMinecraftCertificates=True -Dfml.ignorePatchDiscrepancies=True -Dlog4j2.formatMsgNoLookups=true -XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump";
    int maxMemory;
    int minMemory;
    LaunchOption()
    {
        this->maxMemory=1024;
        this->minMemory=512;
    }
};
void Launch(LaunchOption option)
{
    string launchCommand="";
    launchCommand+="java";
    launchCommand+=option.defaultJVMArgs;
    launchCommand+=" -Xmx"+to_string(option.maxMemory)+"M";
    launchCommand+=" -Xms"+to_string(option.minMemory)+"M";
}