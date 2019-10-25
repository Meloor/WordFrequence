/*
 *@���·��Ҳ���Է�Ϊpath,��name,file_path = path + name
 *����file_name:test\hello.txt��һ�����·��,��ֺ�path:test\, name:hello.txt
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
		return (cnt > b.cnt) || (cnt == b.cnt && va > b.va);//Ƶ�ʴ������ǰ��
	}
};
class WF_f
{
private:
	string buf;
	vector<Word> words_sequence;
	map<string,int> stopwords_mp;
	map<string, int> words_mp;
	map<string, int> verbs_mp;//�����ж��ʣ�map[string]�е�ֵ����ԭ����verbs_proto�е��±�
	vector<string> verbs_proto;//�涯��ԭ��
	string floder_path;
	string file_name;
	int total;
private:
	//��ȡ���ʼ���������map
	void get_words_from_line(string buf, map<string, int> &mp);
	void get_words_from_file(string file_path, map<string, int> &mp);
	//�������
	void write_file(fstream &fout);
	void print_cnt(bool _n, int num);
	void open_write(string file_path);
	void print_stopwords();
	//����·��
	void separate_path(string file_path);
	//
	void get_stopwords(string _x_file_path);
	void get_words(string file_path);
	void get_word_sequence(bool _v);
	void get_verbs(string file_path);
	//���ܺ���
	void solve(string file_path, bool _n, int _n_num, bool _x, string _x_file_path, bool _v, string _v_file_path);
public:
	WF_f();
	~WF_f();
	static void Solve(string file_path, bool _n,int _n_num,bool _x,string _x_file_path, bool _v, string _v_file_path);
};

