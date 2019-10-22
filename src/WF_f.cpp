/*
function:输出文件中所有不重复的单词，按照出现次数由多到少排列，出现次数同样多的，以字典序排列。
date:2019/9/25
author:Meloor
*/
#include "pch.h"
#include "WF_f.h"


WF_f::WF_f()
{
}


WF_f::~WF_f()
{
}

//处理一行字符 
void WF_f::judge(char *a) {
	for (int i = 0; a[i]; i++) {
		if (wd.length() == 0) {
			if (isalpha(a[i]))
				wd = wd + (char)tolower(a[i]);
		}
		else {
			if (isalnum(a[i]))
				wd = wd + (char)tolower(a[i]);
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
void WF_f::open_write(char *origin_file_name) {
	fstream f1;
	char fname[128] = "word sequence of ";
	strcat_s(fname, origin_file_name);
	printf("write to \"%s\"\n", fname);
	f1.open(fname, ios::in);//以读的方式打开 
	if (!f1) {//文件不存在 
		f1.close();
		f1.open(fname, ios::out);//则创建它
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
void WF_f::solve(char *file_name) {
	//初始化 
	wds.clear();
	wmp.clear();
	total = 0;
	wd = "";

	ifstream fin;
	fin.open(file_name);
	if (!fin.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	while (!fin.eof())
	{
		fin.getline(buf, MAX_LINE);
		judge(buf);
	}


	map<string, int>::iterator  it;
	for (it = wmp.begin(); it != wmp.end(); it++) {
		wds.push_back(Word(it->first, it->second));
	}
	sort(wds.begin(), wds.end());
	open_write(file_name);
}
void WF_f::Solve(char *file_name) {
	WF_f* wf_f = new WF_f();
	wf_f->solve(file_name);
}