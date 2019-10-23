#include "pch.h"
#include "Go.h"
#include <iostream>
#include "WF_c.h"
#include "WF_f.h"
#include "WF_d.h"
#include "WF_p.h"
Go::Go()
{
	_c = false;
	_f = false;
	_p = false;
	_d = false;
	_s = false;
	_n = false;
	_x = false;
	_v = false;

	_n_num = 0;
	_p_num = 0;
}


Go::~Go()
{
}
//分离file_path为prefix_path + file_name
void Go::separate_path(string file_path,vector<string> &part) {
	int len = file_path.length();
	int id = -1;
	//寻找并记录下最后一个反斜杠\的位置
	for (int i = len - 1; i >= 0; i--) {
		if (file_path[i] == '\\') {
			id = i;
			break;
		}
	}
	//如果file_path本来也只有文件名，那么file_path == file_name
	part.push_back(file_path.substr(0, id + 1));//[0,id]是id+1个字符
	part.push_back(file_path.substr(id + 1));//拷贝后面的
}
/* function:检查当前“位”是否还有参数
 * parameter: 后面还需要参数的那个参数的参数类型
 * id: 当前位
 */
bool Go::is_enough(int id,string parameter) {
	if (id < parameters.size()) {
		return true;
	}else {
		cout <<"The parameters after "+ parameter + " are not enough!" << endl;
		return false;
		exit(1);
	}
}
/* function:检查当前“位”后是否紧跟"-*"参数
 * parameter: 后面还需要参数的那个参数的参数类型
 * id: 当前位
 */
bool Go::is_followed_(int id,string parameter) {
	if (parameters[id][0] == '-') {
		cout << parameter + " does not need to be followed by the \"-*\" parameter" << endl;
		return true;
		exit(1);
	}
	return false;
}
//解析参数到类属性中
void Go::analyse_parameters(int argc, char *argv[]) {
	//将参数转换为string类型并存到vector中
	parameters.clear();
	for (int i = 0; i < argc; i++)
		parameters.push_back(argv[i]);
	//处理参数
	vector<string> part;
	separate_path(parameters[0], part);
	prefix_path = part[0];
	program_name = part[1];
	for (int i = 1; i < parameters.size(); i++) {
		if (parameters[i] == string("-c")) {
			_c = true;
			is_enough(i + 1, "(-c)");//i+1有参数
			if (parameters[i + 1] == string("-d")) {
				_d = true;
				is_enough(i + 2, "(-d)");
				if (parameters[i + 2] == string("-s")) {
					_s = true;
					is_enough(i + 3, "(-d -s)");
					file_path = parameters[i + 3];
				}
				else {
					is_followed_(i + 2, "(-d)");
					file_path = parameters[i + 2];
				}
			}
			else {//没有-d, -c后必须紧跟一个路径参数
				is_followed_(i + 1, "(-c)");
				file_path = parameters[i + 1];
			}
		}
		else if (parameters[i] == string("-f")) {
			_f = true;
			is_enough(i + 1, "(-f)");//i+1有参数
			if (parameters[i + 1] == string("-d")) {
				_d = true;
				is_enough(i + 2, "(-d)");
				if (parameters[i + 2] == string("-s")) {
					_s = true;
					is_enough(i + 3, "(-d -s)");
					file_path = parameters[i + 3];
				}
				else {
					is_followed_(i + 2, "(-d)");
					file_path = parameters[i + 2];
				}
			}
			else {//没有-d, -c后必须紧跟一个路径参数
				is_followed_(i + 1, "(-f)");
				file_path = parameters[i + 1];
			}
		}
		else if (parameters[i] == string("-p")) {
			_p = true;
			is_enough(i + 1, "(-p)");
			is_followed_(i + 1, "(-p)");
			_p_num = stoi(parameters[i + 1]);

			is_enough(i + 2, "(-p num)");//i+2有参数
			if (parameters[i + 2] == string("-d")) {
				_d = true;
				is_enough(i + 3, "(-d)");
				if (parameters[i + 3] == string("-s")) {
					_s = true;
					is_enough(i + 4, "(-d -s)");
					file_path = parameters[i + 4];
				}
				else {
					is_followed_(i + 3, "(-d)");
					file_path = parameters[i + 3];
				}
			}
			else {//没有-d, -p num后必须紧跟一个路径参数
				is_followed_(i + 2, "(-p num)");
				file_path = parameters[i + 2];
			}
		}
		else if (parameters[i] == string("-n")) {
			_n = true;
			is_enough(i + 1, "(-n)");
			is_followed_(i + 1, "(-n)");
			_n_num = stoi(parameters[i + 1]);
		}
		else if (parameters[i] == string("-x")) {
			_x = true;
			is_enough(i + 1, "(-x)");
			is_followed_(i + 1, "(-x)");
			_x_file_path = parameters[i + 1];
		}
		else if (parameters[i] == string("-v")) {
			_v = true;
			is_enough(i + 1, "(-v)");
			is_followed_(i + 1, "(-v)");
			_v_file_path = parameters[i + 1];
		}
	}
}
void Go::hint() {
	string hints = string("Input format:\n") +
		"WF.exe -c file_name\n" +
		"WF.exe -f file_name\n" +
		"WF.exe -d file_name\n" +
		"WF.exe -d -s file_name\n" +
		"If the file_name contains space, please use this format:\n" +
		"WF.exe -c \"file_name\"\n";
	cout << hints << endl;
}
void Go::test_analyse() {
	cout << "analyse parameters:" << endl;
	cout << "_c:" << _c << endl;
	cout << "_f:" << _f << endl;
	cout << "_p:" << _p << endl;
	cout << "_d:" << _d << endl;
	cout << "_s:" << _s << endl;
	cout << "_n:" << _n << endl;
	cout << "_x:" << _x << endl;
	cout << "_v:" << _v << endl;

	cout << "file_path:" << file_path << endl;
	cout << "_n_num:" << _n_num << endl << endl;;
}
void Go::solve(int argc, char *argv[]) {
	analyse_parameters(argc, argv);
	test_analyse();
	if (_c) {		
		if (_d) {//如果_d为true，那么file_path为floder_name
			//WF_d::Solve_c(file_path, _n, _num, _s);
			cout << "等待实装" << endl;
		}
		else {
			//WF_c::Solve(file_path, _n, _n_num);
			cout << "等待实装" << endl;
		}
	}
	else if (_f) {
		if (_d) {
			WF_d::Solve_f(file_path,_n,_n_num,_s);
		}
		else {
			WF_f::Solve(file_path,_n,_n_num);
		}
	}
	else if (_p) {
		if (_d) {
			//WF_d::Solve_p(file_path, _n, _num, _s);
			cout << "等待实装" << endl;
		}
		else {
			//WF_p::Solve(file_path, _n, _n_num);
			cout << "等待实装" << endl;
		}
		
	}
	else hint();
}
void Go::Solve(int argc, char *argv[]) {
	Go go;
	go.solve(argc, argv);
}