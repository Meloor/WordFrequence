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
	file_path = "file_path";
	_x_file_path = "_x_file_path";
	_v_file_path = "_v_file_path";
}


Go::~Go()
{
}
//����file_pathΪprefix_path + file_name
void Go::separate_path(string file_path,vector<string> &part) {
	int len = file_path.length();
	int id = -1;
	//Ѱ�Ҳ���¼�����һ����б��\��λ��
	for (int i = len - 1; i >= 0; i--) {
		if (file_path[i] == '\\') {
			id = i;
			break;
		}
	}
	//���file_path����Ҳֻ���ļ�������ôfile_path == file_name
	part.push_back(file_path.substr(0, id + 1));//[0,id]��id+1���ַ�
	part.push_back(file_path.substr(id + 1));//���������
}
/* function:��鵱ǰ��λ���Ƿ��в���
 * parameter: ���滹��Ҫ�������Ǹ������Ĳ�������
 * id: ��ǰλ
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
/* function:��鵱ǰ��λ�����Ƿ����"-*"����
 * parameter: ���滹��Ҫ�������Ǹ������Ĳ�������
 * id: ��ǰλ
 */
bool Go::is_followed_(int id,string parameter) {
	if (parameters[id][0] == '-') {
		cout << parameter + " does not need to be followed by the \"-*\" parameter" << endl;
		return true;
		exit(1);
	}
	return false;
}
//������������������
void Go::analyse_parameters(int argc, char *argv[]) {
	//������ת��Ϊstring���Ͳ��浽vector��
	parameters.clear();
	for (int i = 0; i < argc; i++)
		parameters.push_back(argv[i]);
	//�������
	vector<string> part;
	separate_path(parameters[0], part);
	prefix_path = part[0];
	program_name = part[1];
	for (int i = 1; i < parameters.size(); i++) {
		if (parameters[i] == string("-c")) {
			_c = true;
			is_enough(i + 1, "(-c)");//i+1�в���
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
			else {//û��-d, -c��������һ��·������
				is_followed_(i + 1, "(-c)");
				file_path = parameters[i + 1];
			}
		}
		else if (parameters[i] == string("-f")) {
			_f = true;
			is_enough(i + 1, "(-f)");//i+1�в���
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
			else {//û��-d, -c��������һ��·������
				is_followed_(i + 1, "(-f)");
				file_path = parameters[i + 1];
			}
		}
		else if (parameters[i] == string("-p")) {
			_p = true;
			is_enough(i + 1, "(-p)");
			is_followed_(i + 1, "(-p)");
			_p_num = stoi(parameters[i + 1]);

			is_enough(i + 2, "(-p num)");//i+2�в���
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
			else {//û��-d, -p num��������һ��·������
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
	string examples = string("examples:\n") +
		"WF.exe -c file_path\n" +
		"WF.exe -f file_path\n" +
		"WF.exe -f -d floder_path\n" +
		"WF.exe -f -d -s floder_path\n" +
		"WF.exe -f -d -s floder_path -n num\n"+
		"WF.exe -f -d -s floder_path -n num -x _x_file_path\n" +
		"If the file_path contains space, please use this format:\n" +
		"WF.exe -f \"file_path\"\n";
	string hints = string("����˵����\n") +
		"-c ͳ����ĸƵ�����У��ɸߵ�������\n" +
		"-f ͳ�Ƶ���Ƶ�����У��ɸߵ�������\n" +
		"-d ָ���ļ�Ŀ¼��Ĭ���ǵ�ǰĿ¼��\n" +
		"-s �ݹ���Ŀ¼�����ָ�����ļ�Ŀ¼����Ĭ�ϲ��ݹ飩\n" +
		"-n �������һ������num������ֻ������а�ǰnum����Ĭ��Ϊ���ȫ��\n" +
		"-x ָ��ͣ�ʱ���ͳ�Ƶ���ʱ������Щ���ʣ�\n" +
		"-p �������һ������num, ͳ�ƶ���Ƶ�����У��ɸߵ������У�ֻͳ����num��������ɵĶ���\n" +
		"-v ָ��������̬��ÿ��һ�鵥�ʣ�����һ�����ʵĲ�ͬ��̬\n";
	cout << hints << endl;
	cout << examples << endl;
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
	cout << "_x_file_path:" << _x_file_path << endl;
	cout << "_p_num:" << _p_num << endl;
	cout << "_n_num:" << _n_num << endl << endl;;
}
void Go::solve(int argc, char *argv[]) {
	analyse_parameters(argc, argv);
	//test_analyse();
	if (_c) {		
		if (_d) {//���_dΪtrue����ôfile_pathΪfloder_name
			//WF_d::Solve_c(file_path, _n, _num, _s);
			cout << "�ȴ�ʵװ" << endl;
		}
		else {
			WF_c::Solve(file_path);
			//WF_c::Solve(file_path, _n, _n_num);
			//cout << "�ȴ�ʵװ" << endl;
		}
	}
	else if (_f) {
		if (_d) {
			WF_d::Solve_f(file_path,_n,_n_num, _x,_x_file_path,_s);
		}
		else{
			WF_f::Solve(file_path,_n,_n_num,_x,_x_file_path);
		}
	}
	else if (_p) {
		if (_d) {
			WF_d::Solve_p(file_path,_p_num, _n, _n_num,_x,_x_file_path, _s);
		}
		else {
			WF_p::Solve(file_path,_p_num, _n, _n_num,_x,_x_file_path);
		}
		
	}
	else hint();
}
void Go::Solve(int argc, char *argv[]) {
	Go go;
	go.solve(argc, argv);
}