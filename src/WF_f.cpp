/*
function:����ļ������в��ظ��ĵ��ʣ����ճ��ִ����ɶൽ�����У����ִ���ͬ����ģ����ֵ������С�
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

//����һ���ַ� 
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
	fout << "����\t\t\t����\t\t\t���ִ���" << endl;
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
	f1.open(fname, ios::in);//�Զ��ķ�ʽ�� 
	if (!f1) {//�ļ������� 
		f1.close();
		f1.open(fname, ios::out);//�򴴽���
		write_file(f1);
		f1.close();
	}
	else {//���� 
		f1.close();
		f1.open(fname, ios::out | ios::trunc);//���ļ�����ٴ� 
		write_file(f1);
		f1.close();
	}
}
void WF_f::solve(char *file_name) {
	//��ʼ�� 
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