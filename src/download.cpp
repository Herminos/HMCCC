#include<iostream>
#include<urlmon.h>
#include<tchar.h>
#include<fstream>
#include<io.h>
#include<stdio.h>
#include<list>
#include<direct.h>
#include"../headers/json/json.h"
#include"../headers/download.h"
#include"../headers/system.h"
#pragma comment(lib,"urlmon.lib")
using namespace std;
int downloadVersion(downloadOption option)
{
    if(_access(option.GameDir.c_str(),0)==-1)
    {
        cout<<"Game directory not found, make a new one."<<endl;
        _mkdir(option.GameDir.c_str());
    }
    JavaBinPath javaBinPath;
    javaBinPath=getByJREPath();
    if(javaBinPath.count==0)
        javaBinPath=getByJDKPath();
    if(javaBinPath.count==0)
    {
        cout<<"Your computer didn't install Java."<<endl;
        return 0;
    }
    string javaBinPathStr=javaBinPath.path[0];
    string manifestURL="https://piston-meta.mojang.com/mc/game/version_manifest.json";
    string manifestPath=option.GameDir+"/version_manifest.json";
    download(manifestURL,manifestPath);
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    ifstream manifestfile;
    manifestfile.open(manifestPath);
    bool parse_ok=Json::parseFromStream(builder,manifestfile,&root,&errs);
    //cout<<manifestPath<<endl;
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
            versionPath=option.GameDir+"/versions/"+option.versionName+"/"+option.version+".json";
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
    //cout<<versionPath<<endl;
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
        // cout<<libraryPath<<endl;
        // cout<<libraryURL<<endl;
        download(libraryURL,libraryPath);
        if((*it)["downloads"].isMember("classifiers")&&(*it)["downloads"]["classifiers"].isMember("natives-windows"))
        {
            string libraryNativesURL=(*it)["downloads"]["classifiers"]["natives-windows"]["url"].asString();
            string libraryNativesPath=option.GameDir+"/libraries/"+(*it)["downloads"]["classifiers"]["natives-windows"]["path"].asString();
            download(libraryNativesURL,libraryNativesPath);

            string libraryNativesPath2=option.GameDir+"/versions/"+option.versionName+"/"+option.versionName+"-natives/"+"tmpfile.jar";
            download(libraryNativesURL,libraryNativesPath2);
            string curDir=GetCurDir();

            EnterDir(option.GameDir+"/versions/"+option.versionName+"/"+option.versionName+"-natives/");
            string cmd="\""+javaBinPathStr+"/jar.exe\" xvf "+libraryNativesPath2;
            system(cmd.c_str());

            string removeJar;
            removeJar="del "+libraryNativesPath2;
            system(removeJar.c_str());

            string removeMETA;
            removeMETA="rmdir META-INF";
            system(removeMETA.c_str());

            EnterDir(curDir);
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

int downloadServer(downloadServerOption option)
{
    string manifestURL="https://piston-meta.mojang.com/mc/game/version_manifest.json";
    string manifestPath=option.serverDir+"/version_manifest.json";
    download(manifestURL,manifestPath);
    Json::Value root;
    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    ifstream manifestFile;
    manifestFile.open(manifestPath);
    bool parse_ok=Json::parseFromStream(builder,manifestFile,&root,&errs);
    if(!parse_ok)
    {
        cout<<"Open manifest file failed!"<<endl;
    }
    manifestFile.close();
    Json::Value versions=root["versions"];
    bool found=false;
    string versionPath;
    for(Json::Value::iterator it=versions.begin();it!=versions.end();it++)
    {
        if((*it)["id"]==option.version)
        {
            string versionURL=(*it)["url"].asString();
            versionPath=option.serverDir+"/"+option.serverName+"/"+option.version+".json";
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
    download(versionRoot["downloads"]["server"]["url"].asString(),option.serverDir+"/"+option.serverName+"/"+option.version+".jar");
    ofstream eulaFile;
    eulaFile.open(option.serverDir+"/"+option.serverName+"/eula.txt");
    eulaFile<<"eula=true";
    eulaFile.close();
    return 0;
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
        mkMultiDir(dir);
    }
    HRESULT result;
    result=URLDownloadToFileW(NULL, stringToLPCWSTR(URL),stringToLPCWSTR(path),0,NULL);
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
string GetPathDir(string filePath)
{
    string dirPath = filePath;
    size_t p = filePath.find_last_of('/');
    if (p != -1)
    {
        dirPath.erase(p);
    }
    return dirPath;
}
void mkMultiDir(string dir)
{
    if (_access(dir.c_str(), 00) == 0)
        return;

    list <string> dirList;
    dirList.push_front(dir);

    string curDir=GetPathDir(dir);
    while (curDir!=dir)
    {
        if (_access(curDir.c_str(), 00) == 0)
            break;
        dirList.push_front(curDir);
        dir=curDir;
        curDir=GetPathDir(dir);
    }
    for (auto it:dirList)
    {       
        _mkdir(it.c_str());
    }
}