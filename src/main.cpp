#include"json/json.h"
#include"headers/download.h"
#include"headers/system.h"
#include"headers/launch.h"
#include<iostream>
#include<fstream>
#include<io.h>
using namespace std;
int main()
{
    downloadOption option;
    option.GameDir="./.minecraft";
    option.version="1.12.2";
    option.versionName="Demo";
    downloadVersion(option);
    system("pause");
    launchOption LaunchOption(option);
    Account account("Demo","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","xxxxx","xxxx","Mojang");
    launchGame(LaunchOption,account);
    system("pause");
    //我也不知道
}