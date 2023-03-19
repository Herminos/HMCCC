#pragma once

#define GENERATE_FROM_NAME 0
#define GENERATE_RANDOMLY 1

#include <string>
using namespace std;

class offlineAccount
{
    public:
    string name;
    string uuid;
    string accessToken;
    offlineAccount(string name,int type);
};