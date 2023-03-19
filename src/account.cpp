#include<iostream>
#include<string>
#include"../headers/account.h"
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include<boost/uuid/uuid_io.hpp>
using namespace std;
offlineAccount::offlineAccount(string name,int type)
{
    this->name=name;
    
    this->accessToken="0";
    if(type==GENERATE_FROM_NAME)
    {
        boost::uuids::uuid uuid=boost::uuids::string_generator()(name);
        this->uuid=boost::uuids::to_string(uuid);
    }
    else if(type==GENERATE_RANDOMLY)
    {
        boost::uuids::uuid uuid=boost::uuids::random_generator()();
        this->uuid=boost::uuids::to_string(uuid);
    }
    else
    {
        this->uuid="0";
    }
}
