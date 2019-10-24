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
	stopwords_mp.clear();
	words_mp.clear();
	words_sequence.clear();
	total = 0;
}


WF_f::~WF_f()
{
}
/*
 * @��������Ὣ���д�뵽�ļ��������������ᴴ��
 */
void WF_f::write_file(fstream &fout) {
	fout << "����\t\t\t����\t\t\t���ִ���" << endl;
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
/*
 *@��ӡ����Ļ��,��ӡǰnum��
 */
void WF_f::print_cnt(bool _n, int num) {
	int n;
	if (_n)
		n = min(num, (int)words_sequence.size());//��ֹn����words_sequence.size()
	else //û������_n����,Ĭ���������
		n = words_sequence.size();
	if (num = -1)
		cout << "����\t\t\t����\t\t\t���ִ���" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t\t\t";
		cout << words_sequence[i].va;
		int nt = words_sequence[i].va.length() / 8;//1~7,3t;8~15,2t;16~23,1t;24~31,0t;
		for (int i = 0; i < 3 - nt; i++)
			cout << "\t";
		cout << words_sequence[i].cnt << endl;
	}
}

//����һ�е��ַ�����ȡ���ʵ��ƶ�mp��
void WF_f::get_words_from_line(string buf, map<string, int> &mp) {
	string wd = "";
	for (int i = 0; i<buf.length(); i++) {
		unsigned char ch = buf[i];
		if (wd.length() == 0) {
			if (isalpha(ch)) {
				wd = wd + (char)tolower(ch);
				//���ʳ���ֻ��1�����,��ӵ���
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
				/* ԭ�����⣺��©���һ������
				ԭ�򣺽������else(������������Ż���ӵ���)��ǰ�����жϵ���ĸ�ǡ���������ĸ�����š�
				���ж����һ���ַ�ʱ�ǲ������ġ�����Ϊstring����û�д�'\0'��)��
				*/
				//��ӵ���
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
		getline(fin, buf);//ʹ��string����ȡû�г�������
		get_words_from_line(buf,mp);
		//cout << buf << endl;
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
		if (stopwords_mp.count(it->first) == 0) {//ͣ�ʱ���û��������ʾͼ��뵽ͳ����
			words_sequence.push_back(Word(it->first, it->second));
			total += it->second;
		}
	}
	sort(words_sequence.begin(), words_sequence.end());
}

/*
 * �����������num���ƣ��������Ƶ�����У����Ա���������
 */
void WF_f::solve(string file_path, bool _n, int _n_num, bool _x, string _x_file_path) {
	if (_x) {//���������ͦ�ʱ�
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