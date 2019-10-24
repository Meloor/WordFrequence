/*
������ʵ�ͣ�ʱ��У���ô��
*/


#include "pch.h"
#include "WF_p.h"
#include "Phrase.h"
WF_p::WF_p()
{
}


WF_p::~WF_p()
{
}
void WF_p::print_cnt(bool _n, int num) {
	int n;
	if (_n)
		n = min(num, (int)phrases_sequence.size());//��ֹn����phrases_sequence.size()
	else //û������_n����,Ĭ���������
		n = phrases_sequence.size();
	if (num = -1)
		cout << "����\t\t\t����\t\t\t���ִ���" << endl;
	for (int i = 0; i < n; i++) {
		cout << i + 1 << "\t\t\t";
		cout << phrases_sequence[i].to_string();
		int nt = phrases_sequence[i].to_string().length() / 8;//1~7,3t;8~15,2t;16~23,1t;24~31,0t;
		for (int i = 0; i < 3 - nt; i++)
			cout << "\t";
		cout << phrases_sequence[i].num << endl;
	}
}
void WF_p::get_words_from_line(string buf, map<string, int> &mp) {
	string wd = "";
	for (int i = 0; i < buf.length(); i++) {
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
			if (!isalnum(ch) || i == buf.length() - 1) {
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
void WF_p::get_words_from_file(string file_path, map<string, int> &mp) {
	ifstream fin;
	fin.open(file_path);
	if (!fin.is_open())
	{
		cout << "Error opening file,file " + file_path + " is not found!" << endl;
		exit(1);
	}
	while (!fin.eof())
	{
		getline(fin, buf);//ʹ��string����ȡû�г�������
		get_words_from_line(buf, mp);
		//cout << buf << endl;
	}
}

//����һ�е��ַ�����ȡ���ʵ��ƶ�mp��
void WF_p::get_phrases_from_line(string buf,int _p_num, map<Phrase, int> &mp) {
	string wd = "";
	Phrase phrase;
	int id = 0;//��ǰ�����һ���ַ���buf�е�λ��
	for (int i = 0; i < buf.length(); i++) {
		unsigned char ch = buf[i];
		if (wd.length() == 0) {
			if (isalpha(ch)) {
				wd = wd + (char)tolower(ch);
				//���ʳ���ֻ��1�����,��ӵ���
				if (i == buf.length() - 1) {
					//if (stopwords_mp.count(wd) == 0)//����ͣ�ʱ���
						phrase.push_back(wd) ;
					wd = "";
					if (phrase.size() >= _p_num) {//��������ˣ���ô�����ֹ
						if (mp.count(phrase) == 0) {
							mp[phrase] = 0;
						}
						mp[phrase] = mp[phrase] + 1;
						
						//��iָ��buf�е���һ�����ʵĿ�ͷ����֤ÿ����һ��Phrase,iָ������һ�����ʣ�
						i = id + phrase[0].length();
						while (!isalpha((unsigned char)buf[i]))i++;
						id = i;
						
						phrase.clear();
						i--;//��Ϊ�������ִ��һ��i++
					}
				}
			}
		}
		else {
			if (isalnum(ch))
				wd = wd + (char)tolower(ch);
			if (!isalnum(ch) || i == buf.length() - 1) {
				phrase.push_back(wd);
				wd = "";
				if (phrase.size() >= _p_num) {//��������ˣ���ô�����ֹ
					if (mp.count(phrase) == 0) {
						mp[phrase] = 0;
					}
					mp[phrase] = mp[phrase] + 1;
					
					//��iָ��buf�е���һ�����ʵĿ�ͷ����֤ÿ����һ��Phrase,iָ������һ�����ʣ�
					i = id + phrase[0].length();
					while (!isalpha((unsigned char)buf[i]))i++;
					id = i;

					phrase.clear();
					i--;//��Ϊ�������ִ��һ��i++
				}
			}
		}
	}
}
void WF_p::get_phrases_from_file(string file_path,int _p_num, map<Phrase, int> &mp) {
	ifstream fin;
	fin.open(file_path);
	if (!fin.is_open())
	{
		cout << "Error opening file,file " + file_path + " is not found!" << endl;
		exit(1);
	}
	while (!fin.eof())
	{
		getline(fin, buf);//ʹ��string����ȡû�г�������
		get_phrases_from_line(buf,_p_num, mp);
		//cout << buf << endl;
	}
}
void WF_p::get_phrase_sequence() {
	Phrase phrase;
	map<Phrase, int>::iterator  it;
	for (it = phrases_mp.begin(); it != phrases_mp.end(); it++) {		
		phrase = it->first;
		phrase.num = it->second;
		phrases_sequence.push_back(phrase);		
	}
	sort(phrases_sequence.begin(), phrases_sequence.end());
}

void WF_p::get_stopwords(string _x_file_path) {
	stopwords_mp.clear();
	get_words_from_file(_x_file_path, stopwords_mp);
}
void WF_p::solve(string file_path, int _p_num, bool _n, int _n_num, bool _x, string _x_file_path) {
	if (_x) {//���������ͦ�ʱ�
		//get_stopwords(_x_file_path);
		cout << "�ȴ�ʵװ" << endl;
		//print_stopwords();
	}
	get_phrases_from_file(file_path,_p_num,phrases_mp);
	get_phrase_sequence();
	print_cnt(_n, _n_num);
}
void WF_p::Solve(string file_path,int _p_num, bool _n, int _n_num, bool _x, string _x_file_path) {
	WF_p wf_p;
	wf_p.solve(file_path,_p_num,_n,_n_num,_x,_x_file_path);
}
