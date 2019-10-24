/*
如果单词但停词表中，那么，
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
		n = min(num, (int)phrases_sequence.size());//防止n大于phrases_sequence.size()
	else //没有设置_n参数,默认输出所有
		n = phrases_sequence.size();
	if (num = -1)
		cout << "排名\t\t\t单词\t\t\t出现次数" << endl;
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
			if (!isalnum(ch) || i == buf.length() - 1) {
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
		getline(fin, buf);//使用string来读取没有长度限制
		get_words_from_line(buf, mp);
		//cout << buf << endl;
	}
}

//处理一行的字符，提取单词到制定mp中
void WF_p::get_phrases_from_line(string buf,int _p_num, map<Phrase, int> &mp) {
	string wd = "";
	Phrase phrase;
	int id = 0;//当前短语第一个字符在buf中的位置
	for (int i = 0; i < buf.length(); i++) {
		unsigned char ch = buf[i];
		if (wd.length() == 0) {
			if (isalpha(ch)) {
				wd = wd + (char)tolower(ch);
				//单词长度只有1的情况,添加单词
				if (i == buf.length() - 1) {
					//if (stopwords_mp.count(wd) == 0)//不在停词表中
						phrase.push_back(wd) ;
					wd = "";
					if (phrase.size() >= _p_num) {//间隔数超了，那么短语截止
						if (mp.count(phrase) == 0) {
							mp[phrase] = 0;
						}
						mp[phrase] = mp[phrase] + 1;
						
						//让i指向buf中的下一个单词的开头，保证每插入一个Phrase,i指往后退一个单词，
						i = id + phrase[0].length();
						while (!isalpha((unsigned char)buf[i]))i++;
						id = i;
						
						phrase.clear();
						i--;//因为最后它会执行一次i++
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
				if (phrase.size() >= _p_num) {//间隔数超了，那么短语截止
					if (mp.count(phrase) == 0) {
						mp[phrase] = 0;
					}
					mp[phrase] = mp[phrase] + 1;
					
					//让i指向buf中的下一个单词的开头，保证每插入一个Phrase,i指往后退一个单词，
					i = id + phrase[0].length();
					while (!isalpha((unsigned char)buf[i]))i++;
					id = i;

					phrase.clear();
					i--;//因为最后它会执行一次i++
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
		getline(fin, buf);//使用string来读取没有长度限制
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
	if (_x) {//如果设置了挺词表
		//get_stopwords(_x_file_path);
		cout << "等待实装" << endl;
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
