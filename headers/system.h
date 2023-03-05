#pragma once
#include<string>
using namespace std;

struct JavaBinPath
{
	string path[20];
	int count=0;
};

JavaBinPath getByJREPath();

JavaBinPath getByJDKPath();

string GetCurDir();

int EnterDir(string dir);