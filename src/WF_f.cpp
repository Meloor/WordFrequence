/*
function:����ļ������в��ظ��ĵ��ʣ����ճ��ִ����ɶൽ�����У����ִ���ͬ����ģ����ֵ������С�
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

//����һ���ַ� 
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
 *@��������Ὣ���д�뵽�ļ��������������ᴴ��
 */
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

//����file_pathΪfloder_path + file_name
void WF_f::separate_path(string file_path) {
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
	floder_path = file_path.substr(0,id+1);//[0,id]��id+1���ַ�
	file_name = file_path.substr(id+1);//���������

}
/*����������Ĳ�����ֻ���ļ��������ǰ�����·������ô
 *������ļ�����ҪС�Ľ�����
 */
void WF_f::open_write(string file_path) {
	separate_path(file_path);
	string str = "word sequence of ";
	string fname = floder_path + str + file_name;//�����ļ�·������ԣ�
	printf("write to \"%s\"\n", fname.data());
	
	fstream f1;
	f1.open(fname, ios::in);//�Զ��ķ�ʽ�� 
	if (!f1) {//�ļ������� 
		f1.close();
		f1.open(fname, ios::out);//�򴴽���
		if (!f1)cout << "����ʧ��" << endl;
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
/* function: ͳ��file_path��Ӧ�ļ��ĵ���Ƶ�ʣ����������
 *@����������file_path�ļ�������ļ������ھͻᱨ���˳�
 */

void WF_f::get_word_sequence(string file_path) {
	//��ʼ�� 
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
		getline(fin, buf);//ʹ��string����ȡû�г�������
		judge(buf);
		//cout << buf << endl;
	}


	map<string, int>::iterator  it;
	for (it = wmp.begin(); it != wmp.end(); it++) {
		wds.push_back(Word(it->first, it->second));
	}
	sort(wds.begin(), wds.end());
	//open_write(file_path);//������ļ���
	//print_cnt();
}
/*
 *@��ӡ����Ļ��,��ӡǰnum��
 */
void WF_f::print_cnt(bool _n,int num) {
	int n;
	if (_n)
		n = min(num,(int)wds.size());//��ֹn����wds.size()
	else //û������_n����,Ĭ���������
		n = wds.size();
	if (num = -1)
		cout << "����\t\t\t����\t\t\t���ִ���" << endl;
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
 * �����������num���ƣ��������Ƶ�����У����Ա���������
 */
void WF_f::solve(string file_path,bool _n, int _n_num) {
	get_word_sequence(file_path);
	print_cnt(_n, _n_num);
}
void WF_f::Solve(string file_path,bool _n,int _n_num) {
	WF_f wf_f;
	wf_f.solve(file_path,_n,_n_num);
}