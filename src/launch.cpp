#include<iostream>
#include<string>
#include<fstream>
#include"../headers/launch.h"
#include"../headers/json/json.h"
#include"../headers/download.h"
#include"../headers/system.h"
using namespace std;

void launchGame(launchOption option,Account account)
{
    string launchCommand="";
    launchCommand+="java";
    launchCommand+=option.defaultJVMArgs;
    launchCommand+=" -Xmx"+to_string(option.maxMemory)+"M";
    launchCommand+=" -Xms"+to_string(option.minMemory)+"M";
    launchCommand+=" -Djava.library.path="+option.GameDir+"/versions/"+option.versionName+"/"+option.versionName+"-natives";
    string libraryPath=" ";
    Json::Value root;
    string versionJSONPath=option.GameDir+"/versions/"+option.versionName+"/"+option.version+".json";
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    ifstream versionJSONFile;
    versionJSONFile.open(versionJSONPath);
    bool parse_ok=Json::parseFromStream(builder,versionJSONFile,&root,&errs);
    if(!parse_ok)
    {
        cout<<"Open version json file failed!"<<endl;
    }
    versionJSONFile.close();
    Json::Value libraries=root["libraries"];
    for(Json::Value::iterator it=libraries.begin();it!=libraries.end();it++)
    {
        if((*it)["downloads"]["artifact"]["path"].asString()!="")
        {
            libraryPath+=option.GameDir+"/libraries/"+(*it)["downloads"]["artifact"]["path"].asString()+";";
        }
    }
    libraryPath+=option.GameDir+"/versions/"+option.versionName+"/"+option.versionName+".jar";
    launchCommand+=" -cp "+libraryPath;
    launchCommand+=" "+root["mainClass"].asString();
    launchCommand+=" --username "+account.userName;
    launchCommand+=" --version "+option.version;
    launchCommand+=" --gameDir "+option.GameDir;
    launchCommand+=" --assetsDir "+option.GameDir+"/assets";
    launchCommand+=" --assetIndex "+root["assetIndex"]["id"].asString();
    launchCommand+=" --uuid "+root["id"].asString();
    launchCommand+=" --accessToken "+account.accessToken;
    launchCommand+=" --userType "+account.userType;
    launchCommand+=" --versionType "+option.versionType;
    launchCommand+=" --height"+option.height;
    launchCommand+=" --width"+option.width;
    
    cout<<launchCommand<<endl;
    system(launchCommand.c_str());
}

void launchServer(launchServerOption option)
{
    string launchCommand="";
    launchCommand+="java";
    //launchCommand+=option.defaultJVMArgs;
    launchCommand+=" -Xmx"+to_string(option.maxMemory)+"M";
    launchCommand+=" -Xms"+to_string(option.minMemory)+"M";
    launchCommand+=" -jar "+option.serverDir+"/"+option.serverName+"/"+option.version+".jar";
    if(option.ifNoGui)
        launchCommand+=" nogui";
    cout<<launchCommand<<endl;
    EnterDir(option.serverDir+"/"+option.serverName);
    system("pause");
    system(launchCommand.c_str());
}