#pragma once
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include "Phrase.h"
#include <algorithm>
using namespace std; 
class WF_p
{
private:
	map<string, int> stopwords_mp;
	vector<Phrase> phrases_sequence;
	map<Phrase, int> phrases_mp;
	string buf;
private:
	void print_cnt(bool _n, int num);
	void get_words_from_line(string buf, map<string, int> &mp);
	void get_words_from_file(string file_path, map<string, int> &mp);
	void get_stopwords(string _x_file_path);
	void get_phrases_from_line(string buf, int _p_num, map<Phrase, int> &mp);
	void get_phrases_from_file(string file_path, int _p_num, map<Phrase, int> &mp);
	void get_phrase_sequence();
	void solve(string file_path, int _p_num, bool _n, int _n_num, bool _x, string _x_file_path);
public:
	WF_p();
	~WF_p();
	static void Solve(string file_path, int _p_num, bool _n, int _n_num, bool _x, string _x_file_path);
};

