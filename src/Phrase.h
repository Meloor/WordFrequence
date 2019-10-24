#pragma once
#include <string>
#include <vector>   
using namespace std;
class Phrase
{
private:
	vector<string> words;
public:
	int num;//该短语出现的次数
public:
	bool operator<(const Phrase &b)const;
	//bool operator>(Phrase &b);
	//bool operator==(Phrase &b);
	string operator[](int i);
public:
	Phrase();
	~Phrase();
	void clear();
	int size();
	void push_back(string word);
	string to_string()const;
};

