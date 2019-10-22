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
		return (cnt > b.cnt) || (cnt == b.cnt && va > b.va);;//Ƶ�ʴ������ǰ��
	}
};
class WF_f
{
private:
	static const int  MAX_LINE = 1024;
	vector<Word> wds;
	map<string, int> wmp;
	string wd = "";//����
	int total;//���������� 
	char buf[MAX_LINE + 1];  /*������*/
private:
	void judge(char *a);
	void write_file(fstream &fout);
	void open_write(char *origin_file_name);
	void solve(char *file_name);
public:
	WF_f();
	~WF_f();
	static void Solve(char* file_name);
};

