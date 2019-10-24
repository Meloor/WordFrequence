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
	stopwords_mp.clear();
	words_mp.clear();
	words_sequence.clear();
	total = 0;
}


WF_f::~WF_f()
{
}
/*
 * @这个函数会将输出写入到文件，如果不存在则会创建
 */
void WF_f::write_file(fstream &fout) {
	fout << "排名\t\t\t单词\t\t\t出现次数" << endl;
	for (int i = 0; i < words_sequence.size(); i++) {
		fout << i + 1 << "\t\t\t";
		fout << words_sequence[i].va.data();
		int nt = words_sequence[i].va.length() / 8;
		//int flag = words_sequence[i].va.length()%8;
		//if(flag==0)
		for (int j = 0; j < 3 - nt; j++)fout << "\t";
		fout << words_sequence[i].cnt << endl;
	}
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
/*
 *@打印到屏幕上,打印前num个
 */
void WF_f::print_cnt(bool _n, int num) {
	int n;
	if (_n)
		n = min(num, (int)words_sequence.size());//防止n大于words_sequence.size()
	else //没有设置_n参数,默认输出所有
		n = words_sequence.size();
	if (num = -1)
		cout << "排名\t\t\t单词\t\t\t出现次数" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t\t\t";
		cout << words_sequence[i].va;
		int nt = words_sequence[i].va.length() / 8;//1~7,3t;8~15,2t;16~23,1t;24~31,0t;
		for (int i = 0; i < 3 - nt; i++)
			cout << "\t";
		cout << words_sequence[i].cnt << endl;
	}
}

//处理一行的字符，提取单词到制定mp中
void WF_f::get_words_from_line(string buf, map<string, int> &mp) {
	string wd = "";
	for (int i = 0; i<buf.length(); i++) {
		unsigned char ch = buf[i];
		if (wd.length() == 0) {
			if (isalpha(ch)) {
				wd = wd + (char)tolower(ch);
				//单词长度只有1的情况,添加单词
				if (i == buf.length() - 1) {
					if (mp.count(wd) == 0) {
						mp[wd] = 0;
					}
					mp[wd] = mp[wd] + 1;
					wd = "";
				}
			}					
		}
		else {
			if (isalnum(ch))
				wd = wd + (char)tolower(ch);
			if(!isalnum(ch)||i==buf.length()-1) {
				/* 原来问题：遗漏最后一个单词
				原因：进入这个else(进入这个代码块才会添加单词)的前提是判断的字母是“非数字字母”符号。
				当判断最后一个字符时是不会进入的。（因为string中是没有存'\0'的)。
				*/
				//添加单词
				if (mp.count(wd) == 0) {
					mp[wd] = 0;
				}
				mp[wd] = mp[wd] + 1;
				wd = "";
			}
		}
	}
}
void WF_f::get_words_from_file(string file_path, map<string, int> &mp) {
	ifstream fin;
	fin.open(file_path);
	if (!fin.is_open())
	{
		cout << "Error opening file,file " +file_path+" is not found!" << endl;
		exit(1);
	}
	while (!fin.eof())
	{
		getline(fin, buf);//使用string来读取没有长度限制
		get_words_from_line(buf,mp);
		//cout << buf << endl;
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
void WF_f::print_stopwords() {
	map<string, int>::iterator  it;
	for (it = stopwords_mp.begin(); it != stopwords_mp.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
}
void WF_f::get_stopwords(string _x_file_path) {
	stopwords_mp.clear();
	get_words_from_file(_x_file_path, stopwords_mp);
}
void WF_f::get_words(string file_path) {
	words_mp.clear();
	get_words_from_file(file_path,words_mp);
}

void WF_f::get_word_sequence() {
	total = 0;
	map<string, int>::iterator  it;
	for (it = words_mp.begin(); it != words_mp.end(); it++) {
		if (stopwords_mp.count(it->first) == 0) {//停词表中没有这个单词就加入到统计中
			words_sequence.push_back(Word(it->first, it->second));
			total += it->second;
		}
	}
	sort(words_sequence.begin(), words_sequence.end());
}

/*
 * 这个函数加了num限制，用于输出频率排行，可以被反复调用
 */
void WF_f::solve(string file_path, bool _n, int _n_num, bool _x, string _x_file_path) {
	if (_x) {//如果设置了挺词表
		get_stopwords(_x_file_path);
		//print_stopwords();
	}
	get_words(file_path);
	get_word_sequence();
	print_cnt(_n, _n_num);
}
void WF_f::Solve(string file_path, bool _n, int _n_num, bool _x, string _x_file_path) {
	WF_f wf_f;
	wf_f.solve(file_path,_n,_n_num,_x,_x_file_path);
}