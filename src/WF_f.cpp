/*
function:����ļ������в��ظ��ĵ��ʣ����ճ��ִ����ɶൽ�����У����ִ���ͬ����ģ����ֵ������С�
date:2019/9/25
author:Meloor

question:���ʵ��-v����
����verbs_file��ÿһ�У����Ƚ�ÿ��������ӵ�verbs_mp��
��ÿ�еĵ�һ������take��ӵ�verbs_proto��
�������е��ʶ�Ӧ��mpָ��vector�д���ԭ�͵��±�

map<string,int> verbs;
vector<string> verbs_proto;//ֻ��ԭ��
Ŀǰ��������words_mp������е��ʣ��ڱ������mpʱ�������ж����������verbs_mp���Ƿ���ڣ�����������滻Ϊԭ�͡�
Ȼ�����ж��Ƿ���ͣ�ʱ���Ϊԭ�ͣ��У�����ڣ�����ھͲ���ӵ�vector�С�

*/
#include "pch.h"
#include "WF_f.h"
#include <string>

WF_f::WF_f()
{
	stopwords_mp.clear();
	words_mp.clear();
	words_sequence.clear();
	verbs_mp.clear();
	verbs_proto.clear();
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

//����һ�е��ַ�����ȡ���ʵ�ָ��mp��
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

/*
�ú���������get_words_from_file,���ڶ��ʻ��漰��һ��vector,���Ծ���дget_words_from_file��
*/
void WF_f::get_verbs(string file_path) {
	verbs_mp.clear();
	verbs_proto.clear();

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
		//�����ȡverb��verbs_mp,verbs_proto��
		string wd = "";
		map<string, int> &mp = verbs_mp;
		vector<string> &vp = verbs_proto;
		bool is_first = true;
		for (int i = 0; i < buf.length(); i++) {
			unsigned char ch = buf[i];
			if (wd.length() == 0) {
				if (isalpha(ch)) {
					wd = wd + (char)tolower(ch);

					//���ʳ���ֻ��1�����,��ӵ���					
					if (i == buf.length() - 1) {
						if (is_first) {//�Ǹ��еĵ�һ������
							is_first = false;
							vp.push_back(wd);//�����һ��ԭ��
						}
						if (mp.count(wd) == 0) {
							mp[wd] = vp.size() - 1;//ԭ���±�
						}
						mp[wd] = vp.size() - 1;
						wd = "";
					}
				}
			}
			else {
				if (isalnum(ch))
					wd = wd + (char)tolower(ch);
				if (!isalnum(ch) || i == buf.length() - 1) {
					//��ӵ���
					if (is_first) {//�Ǹ��еĵ�һ������
						is_first = false;
						vp.push_back(wd);//�����һ��ԭ��
					}
					if (mp.count(wd) == 0) {
						mp[wd] = vp.size() - 1;//ԭ���±�
					}
					mp[wd] = vp.size() - 1;
					wd = "";
				}
			}
		}
		//cout << buf << endl;
	}
}
void WF_f::get_word_sequence(bool _v) {
	total = 0;
	//����Ҫ��words_mp�е����ö��ʶ��滻��ԭ�ͣ����ԣ��ټ�һ��mp
	if (_v) {
		map<string, int> mp;
		map<string, int>::iterator  it;
		string wd = "";
		for (it = words_mp.begin(); it != words_mp.end(); it++) {
			wd = it->first;
			if (verbs_mp.count(it->first) == 1) {//�������verbs�д���
				wd = verbs_proto[verbs_mp[it->first]];//����Ϊ��ԭ��
			}
			if (mp.count(wd) == 0)
				mp[wd] = it->second;
			else mp[wd] = mp[wd] + it->second;
		}
		words_mp = mp;
	}
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
void WF_f::solve(string file_path, bool _n, int _n_num, bool _x, string _x_file_path,bool _v,string _v_file_path) {
	if (_v) {
		get_verbs(_v_file_path);
	}
	if (_x) {//���������ͦ�ʱ�
		get_stopwords(_x_file_path);
		//print_stopwords();
	}

	get_words(file_path);
	get_word_sequence(_v);
	print_cnt(_n, _n_num);
}
void WF_f::Solve(string file_path, bool _n, int _n_num, bool _x, string _x_file_path, bool _v, string _v_file_path) {
	WF_f wf_f;
	wf_f.solve(file_path,_n,_n_num,_x,_x_file_path,_v,_v_file_path);
}