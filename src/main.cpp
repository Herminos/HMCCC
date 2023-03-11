#include"../headers/download.h"
#include"../headers/download.h"
#include"../headers/system.h"
#include"../headers/launch.h"
#include<iostream>
#include<fstream>
#include<io.h>
using namespace std;
int main()
{
//     downloadOption option;
//     option.GameDir="C:/Users/hermi/Desktop/HMCCC/demo";
//     option.version="1.12.2";
//     option.versionName="Demo";
//     downloadVersion(option);
//     system("pause");
//     launchOption LaunchOption(option);
//     Account account("Demo","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","xxxxx","xxxx","Mojang");
//     launchGame(LaunchOption,account);
//     system("pause");
//     //我也不知道
    downloadServerOption option;
    option.serverDir="C:/Users/hermi/Desktop/HMCCC/demoserver";
    option.version="1.12.2";
    option.serverName="Demo";
    downloadServer(option);
    system("pause");
    launchServerOption LaunchOption(option);
    launchServer(LaunchOption);
    system("pause");
}