/*
 * @ 该类用于参数处理并调用具体的功能函数
 */
#pragma once
#include <string>
#include <vector>
using namespace std;
class Go
{
private:
	bool _c;
	bool _f;
	bool _p;
	bool _d;
	bool _s;
	bool _n;
	bool _x;
	bool _v;
	string file_path;
	string _x_file_path;
	string _v_file_path;
	//string floder_name;
	int _p_num;
	int _n_num;

	string prefix_path;//前缀路径，文件路径分为文件名和文件名前面的部分，这个前面的部分我称之为前缀路径
	string program_name;//程序名

	vector<string> parameters;
private:
	void separate_path(string file_path, vector<string> &part);
	bool is_enough(int id, string parameter);
	bool is_followed_(int id, string parameter);
	void analyse_parameters(int argc, char *argv[]);
	void test_analyse();
	void hint();
	void solve(int argc, char *argv[]);
public:
	Go();
	~Go();
	static void Solve(int argc, char *argv[]);
};

