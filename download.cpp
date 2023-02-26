#include<iostream>
#include<urlmon.h>
#include<tchar.h>
#include<fstream>
#include<io.h>
#include<stdio.h>
#include<direct.h>
#include"json/json.h"
#include"download.h"
#pragma comment(lib,"urlmon.lib")
using namespace std;

int downloadVersion(downloadOption option)
{
    string manifestURL="https://piston-meta.mojang.com/mc/game/version_manifest.json";
    string manifestPath=option.GameDir+"/version_manifest.json";
    download(manifestURL,manifestPath);
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    ifstream manifestfile;
    manifestfile.open(manifestPath);
    bool parse_ok=Json::parseFromStream(builder,manifestfile,&root,&errs);
    cout<<manifestPath<<endl;
    if(!parse_ok)
    {
        cout<<"Open manifest file failed!"<<endl;
    }

    manifestfile.close();
    Json::Value versions=root["versions"];
    bool found=false;
    string versionPath;
    for(Json::Value::iterator it=versions.begin();it!=versions.end();it++)
    {
        if((*it)["id"]==option.version)
        {
            string versionURL=(*it)["url"].asString();
            if(_access((option.GameDir+"/versions").c_str(),0)==-1)
                _mkdir((option.GameDir+"/versions").c_str());
            if(_access((option.GameDir+"/versions/"+option.versionName).c_str(),0)==-1)
                _mkdir((option.GameDir+"/versions/"+option.versionName).c_str());
            versionPath=option.GameDir+"/versions/"+option.versionName+"\\"+option.version+".json";
            download(versionURL,versionPath);
            found=true;
            break;
        }
    }
    if(!found)
    {
        cout<<"Version not found!"<<endl;
        return -1;
    }
    cout<<versionPath<<endl;
    Json::Value versionRoot;
    Json::CharReaderBuilder versionBuilder;
    JSONCPP_STRING versionErrs;
    ifstream versionfile;
    versionfile.open(versionPath);
    parse_ok=Json::parseFromStream(versionBuilder,versionfile,&versionRoot,&versionErrs);
    if(!parse_ok)
    {
        cout<<"Open version file failed!"<<endl;
    }
    versionfile.close();

    cout<<"Downloading game jar file..."<<endl;
    string GameJarFileURL=versionRoot["downloads"]["client"]["url"].asString();
    string GameJarFilePath=option.GameDir+"/versions/"+option.versionName+"/"+option.versionName+".jar";
    download(GameJarFileURL,GameJarFilePath);

    cout<<"Downloading game libraries..."<<endl;
    for(Json::Value::iterator it=versionRoot["libraries"].begin();it!=versionRoot["libraries"].end();it++)
    {
        string libraryURL=(*it)["downloads"]["artifact"]["url"].asString();
        string libraryPath=option.GameDir+"/libraries/"+(*it)["downloads"]["artifact"]["path"].asString();
        cout<<libraryPath<<endl;
        cout<<libraryURL<<endl;
        download(libraryURL,libraryPath);
        if((*it)["downloads"].isMember("classifiers")&&(*it)["downloads"]["classifiers"].isMember("natives-windows"))
        {
            string libraryNativesURL=(*it)["downloads"]["classifiers"]["natives-windows"]["url"].asString();
            string libraryNativesPath=option.GameDir+"/libraries/"+(*it)["downloads"]["classifiers"]["natives-windows"]["path"].asString();
            download(libraryNativesURL,libraryNativesPath);
        }
    }

    if(_access((option.GameDir+"/assets").c_str(),0)==-1)
        _mkdir((option.GameDir+"/assets").c_str());
    if(_access((option.GameDir+"/assets/indexes").c_str(),0)==-1)
        _mkdir((option.GameDir+"/assets/indexes").c_str());
    if(_access((option.GameDir+"/assets/objects").c_str(),0)==-1)
        _mkdir((option.GameDir+"/assets/objects").c_str());

    string GameAssestIndexURL=versionRoot["assetIndex"]["url"].asString();
    download(GameAssestIndexURL,option.GameDir+"/assets/indexes/"+versionRoot["assetIndex"]["id"].asString()+".json");

    ifstream assestIndexFile;
    assestIndexFile.open(option.GameDir+"/assets/indexes/"+versionRoot["assetIndex"]["id"].asString()+".json");
    Json::Value assestIndexRoot;
    parse_ok=Json::parseFromStream(versionBuilder,assestIndexFile,&assestIndexRoot,&errs);
    if(!parse_ok)
    {
        cout<<"Open assest index file failed!"<<endl;
    }
    for(Json::Value::iterator it=assestIndexRoot["objects"].begin();it!=assestIndexRoot["objects"].end();it++)
    {
        string assestPrePath=(*it)["hash"].asString().substr(0,2)+"/"+(*it)["hash"].asString();
        download("https://resources.download.minecraft.net/"+assestPrePath,option.GameDir+"/assets/objects/"+assestPrePath);
    }

}

LPCWSTR stringToLPCWSTR(string str)
{
    int len;
    len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    unsigned short * wszString = new unsigned short[len + 1];
    memset(wszString, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)wszString, len);
    return (LPCWSTR)wszString;
}

int download(string URL,string path)
{

    int length=path.length();
    string dir;
    for(int i=length-1;i>=0;i--)
    {
        if(path[i]=='/')
        {
            dir=path.substr(0,i);
            break;
        }
    }
    if(_access(dir.c_str(),0)==-1)
    {
        mkdir(dir.c_str());
    }
    HRESULT result;
    URLDownloadToFileW(NULL, stringToLPCWSTR(URL),stringToLPCWSTR(path),0,NULL);
    if(result==S_OK)
        return 0;
    else
    {
        cout<<"Download failed!"<<endl;
        if(result==E_OUTOFMEMORY)
        {
            cout<<"Out of memory!"<<endl;
        }
        if(result==INET_E_DOWNLOAD_FAILURE)
        {
            cout<<"Invaild resource!"<<endl;
        }
    }
}

