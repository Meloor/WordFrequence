#pragma once
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<algorithm>
#include<fstream>
using namespace std;
struct ZM {
	char name;
	float wf;
	ZM(char n = 'a', float w = 0) {
		name = n;
		wf = w;
	}
	//重载sort函数
	bool operator<(const ZM &b) const
	{
		return (wf > b.wf) || (wf == b.wf&&name < b.name);//频率大的排在前面
	}
};

class WF_c
{
private:
	static const int MAX_LINE = 1024;
	int num[26];
	int total;//约3e6字符，5e4行 
	ZM wf[26];
	char buf[MAX_LINE + 1];  /*缓冲区*/
private:
	void judge(char a[]);
	//bool cmp(ZM a, ZM b);
	void solve(char *file_name);
public:
	WF_c();
	~WF_c();
	static void Solve(char *file_name);//main函数中输入的是char*
};

