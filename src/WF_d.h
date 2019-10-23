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
	void solve_c(string floder_name, bool _n, int _n_num, bool _s);
	void solve_f(string floder_name, bool _n, int _n_num, bool _s);
	void solve_p(string floder_name, bool _n, int _n_num, bool _s);
public:
	WF_d();
	~WF_d();
	static void Solve_c(string floder_name,bool _n,int _n_num,bool _s);
	static void Solve_f(string floder_name,bool _n,int _n_num,bool _s);
	static void Solve_p(string floder_name,bool _n,int _n_num,bool _s);
};

