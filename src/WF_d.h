#pragma once
#include <io.h>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class WF_d
{
private:
	vector<string> file_path;
	vector<string> file_name;
private:
	void getFilesInFloder(string path, bool is_recursive_subfolder);	
	static bool cmp(string &a, string &b);
protected:
	void solve(string floder_name, bool is_recursive_subfolder);
public:
	WF_d();
	~WF_d();
	static void Solve(string floder_name);
};

