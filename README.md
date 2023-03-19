# HMCCC

 A Minecraft launcher core written in C++

## Description

Due to the rencent NetEase Company crackdown on third-party Minecraft Launchers,<br>
The original project "CMCL" (a complete launcher) was turned into a launcher core.

## Usage

HMCCC is a launcher core, not a complete launcher, it offers some functions and classes to download and launch Minecraft.

These are some demos:

```c++
#include"include/download.h"
#include"include/launch.h"
using namespace std;
int main()
{
     downloadOption option;
     option.GameDir="C:/Users/hermi/Desktop/HMCCC/demo";
     option.version="1.12.2";
     option.versionName="Demo";
     downloadVersion(option);
     launchOption LaunchOption(option);
     Account account("Demo","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx","xxxxx","xxxx","Mojang");
     launchGame(LaunchOption,account);
}
```

This allows user to download a 1.12.2 Minecraft and launch it(build passed on Windows 11).

## Build

```powershell
git clone https://github.com/Herminos/HMCCC.git
```
