#include "pch.h"
#include "Phrase.h"


Phrase::Phrase()
{
	words.clear();
}


Phrase::~Phrase()
{
}
void Phrase::clear() {
	words.clear();
}
void Phrase::push_back(string word) {
	words.push_back(word);
}
int Phrase::size() {
	return words.size();
}
string Phrase::to_string()const {
	string str = "";
	for (int i = 0; i < words.size(); i++) {
		str += words[i];
		if (i != words.size() - 1)str += " ";
	}
	return str;
}
bool Phrase::operator<(const Phrase &b)const
{
	string str1 = to_string();
	string str2 = b.to_string();
	return (num > b.num)||(num == b.num&& str1 < str2);//频率大的排在前面
}
//bool Phrase::operator>(Phrase &b)
//{
//	string str1 = this->to_string();
//	string str2 = b.to_string();
//	return str1 >str2;
//}
//bool Phrase::operator==(Phrase &b)
//{
//	string str1 = this->to_string();
//	string str2 = b.to_string();
//	return str1 == str2;
//}
string Phrase::operator[](int i) {
	return words[i];
}

