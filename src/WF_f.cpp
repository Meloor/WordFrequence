/*
function:输出文件中所有不重复的单词，按照出现次数由多到少排列，出现次数同样多的，以字典序排列。
date:2019/9/25
author:Meloor
*/
#include "pch.h"
#include "WF_f.h"
#include <string>

WF_f::WF_f()
{
}


WF_f::~WF_f()
{
}

//处理一行字符 
void WF_f::judge(string buf) {
	for (int i = 0; buf[i]; i++) {
		unsigned char ch = buf[i];
		if (wd.length() == 0) {
			if (isalpha(ch))
				wd = wd + (char)tolower(ch);
		}
		else {
			if (isalnum(ch))
				wd = wd + (char)tolower(ch);
			else {
				if (wmp.count(wd) == 0) {
					wmp[wd] = 0;
					total++;
				}
				wmp[wd] = wmp[wd] + 1;
				wd = "";
			}
		}
	}
}
/*
 *@这个函数会将输出写入到文件，如果不存在则会创建
 */
void WF_f::write_file(fstream &fout) {
	fout << "排名\t\t\t单词\t\t\t出现次数" << endl;
	for (int i = 0; i < wds.size(); i++) {
		fout << i + 1 << "\t\t\t";
		fout << wds[i].va.data();
		int nt = wds[i].va.length() / 8;
		//int flag = wds[i].va.length()%8;
		//if(flag==0)
		for (int j = 0; j < 3 - nt; j++)fout << "\t";
		fout << wds[i].cnt << endl;
	}
}

//分离file_path为floder_path + file_name
void WF_f::separate_path(string file_path) {
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
	floder_path = file_path.substr(0,id+1);//[0,id]是id+1个字符
	file_name = file_path.substr(id+1);//拷贝后面的

}
/*如果穿进来的参数不只是文件名，而是包含了路径，那么
 *输出的文件名是要小心谨慎的
 */
void WF_f::open_write(string file_path) {
	separate_path(file_path);
	string str = "word sequence of ";
	string fname = floder_path + str + file_name;//输入文件路径（相对）
	printf("write to \"%s\"\n", fname.data());
	
	fstream f1;
	f1.open(fname, ios::in);//以读的方式打开 
	if (!f1) {//文件不存在 
		f1.close();
		f1.open(fname, ios::out);//则创建它
		if (!f1)cout << "创建失败" << endl;
		write_file(f1);
		f1.close();
	}
	else {//存在 
		f1.close();
		f1.open(fname, ios::out | ios::trunc);//将文件清空再打开 
		write_file(f1);
		f1.close();
	}
	
}
/* function: 统计file_path对应文件的单词频率，并输出排行
 *@这个函数会打开file_path文件，如果文件不存在就会报错并退出
 */

void WF_f::get_word_sequence(string file_path) {
	//初始化 
	wds.clear();
	wmp.clear();
	total = 0;
	wd = "";

	ifstream fin;
	fin.open(file_path);
	if (!fin.is_open())
	{
		cout << "Error opening file,file is not found"<<endl;
		exit(1);
	}
	while (!fin.eof())
	{
		getline(fin, buf);//使用string来读取没有长度限制
		judge(buf);
		//cout << buf << endl;
	}


	map<string, int>::iterator  it;
	for (it = wmp.begin(); it != wmp.end(); it++) {
		wds.push_back(Word(it->first, it->second));
	}
	sort(wds.begin(), wds.end());
	//open_write(file_path);//输出到文件中
	//print_cnt();
}
/*
 *@打印到屏幕上,打印前num个
 */
void WF_f::print_cnt(bool _n,int num) {
	int n;
	if (_n)
		n = min(num,(int)wds.size());//防止n大于wds.size()
	else //没有设置_n参数,默认输出所有
		n = wds.size();
	if (num = -1)
		cout << "排名\t\t\t单词\t\t\t出现次数" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t\t\t";
		cout << wds[i].va;
		int nt = wds[i].va.length() / 8;//1~7,3t;8~15,2t;16~23,1t;24~31,0t;
		for (int i = 0; i < 3 - nt; i++)
			cout << "\t";
		cout << wds[i].cnt << endl;
	}
}
/*
 * 这个函数加了num限制，用于输出频率排行，可以被反复调用
 */
void WF_f::solve(string file_path,bool _n, int _n_num) {
	get_word_sequence(file_path);
	print_cnt(_n, _n_num);
}
void WF_f::Solve(string file_path,bool _n,int _n_num) {
	WF_f wf_f;
	wf_f.solve(file_path,_n,_n_num);
}