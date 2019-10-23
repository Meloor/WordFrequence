/*
 *@相对路径也可以分为path,和name,file_path = path + name
 *比如file_name:test\hello.txt是一个相对路径,拆分后，path:test\, name:hello.txt
 */
#pragma once
#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<algorithm>
#include<vector>
#include<map>
#include<ctype.h>
#include<string>
using namespace std;
struct Word {
	string va;
	int cnt;
	Word(string v = "a", int c = 0) {
		va = v;
		cnt = c;
	}
	bool operator<(const Word &b) const
	{
		return (cnt > b.cnt) || (cnt == b.cnt && va > b.va);;//频率大的排在前面
	}
};
class WF_f
{
private:
	string buf;
	vector<Word> wds;
	map<string, int> wmp;
	string wd = "";//单词
	int total;//单词种类数 
	string floder_path;
	string file_name;
private:
	void judge(string buf);
	void write_file(fstream &fout);
	void print_cnt();
	void open_write(string file_path);
	void separate_path(string file_path);
	void solve(string file_path);
public:
	WF_f();
	~WF_f();
	static void Solve(string file_path);
};

