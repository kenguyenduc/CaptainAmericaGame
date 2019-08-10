#pragma once
#include<vector>
#include<d3dx9.h>
#include<fstream>
#include<string>
#include<string.h>
#include<sstream>
#include<map>
#include<vector>

using namespace std;

class LoadTXT
{
public:
	static LoadTXT* instance;
	LoadTXT();
	static LoadTXT* Instance();
	RECT* LoadRect(char* path);
	~LoadTXT();
};

