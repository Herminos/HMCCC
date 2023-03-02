#include<iostream>
#include<io.h>
#include"../headers/system.h"
using namespace std;

JavaBinPath getByJREPath()
{
	if(!_access("C:/Program Files/Java",0)==0)
	{
		cout<<"Your computer didn't install Java."<<endl;
	}
	string fileName;
	_finddata_t file;
	intptr_t fileHandle;
	if ((fileHandle=_findfirst("C:/Program Files/Java/jre*",&file))==-1)
	{
		return JavaBinPath();
	}
	else
	{
		JavaBinPath javaBinPath;
		while (_findnext(fileHandle, &file)==0)
		{
			string JavaBinPath="C:/Program Files/Java/"+(string)file.name+"/bin";
			javaBinPath.path[javaBinPath.count]=JavaBinPath;
			javaBinPath.count++;
		}
		_findclose(fileHandle);	
		return javaBinPath;
	}
}
JavaBinPath getByJDKPath()
{
	if(!_access("C:/Program Files/Java",0)==0)
	{
		cout<<"Your computer didn't install Java."<<endl;
	}
	string fileName;
	_finddata_t file;
	intptr_t fileHandle;
	if ((fileHandle=_findfirst("C:/Program Files/Java/jdk*",&file))==-1)
	{
		return JavaBinPath();
	}
	else
	{
		JavaBinPath javaBinPath;
		while (_findnext(fileHandle, &file)==0)
		{
			string JavaBinPath="C:/Program Files/Java/"+(string)file.name+"/bin";
			javaBinPath.path[javaBinPath.count]=JavaBinPath;
			javaBinPath.count++;
		}
		_findclose(fileHandle);	
		return javaBinPath;
	}
}