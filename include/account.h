#ifndef ACCOUNT_H
#define ACCOUNT_H

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

#endif