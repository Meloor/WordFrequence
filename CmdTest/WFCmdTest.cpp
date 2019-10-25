// WFCmdTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
using namespace std;
vector<string> tests;
string path;
const int N = 5;
void init_tests() {
	tests.clear();
	//tests.push_back("WF.exe -c \"1.I Have a Dream.txt\"");

	//-f功能，目前支持-n,-d -s,-x,-v
	//tests.push_back("WF.exe -f \"1.I Have a Dream.txt\"");
	//tests.push_back("WF.exe -f \"1.I Have a Dream.txt\" -n 5");
	//tests.push_back("WF.exe -f -d tests -n 5 -x \"stopwords.txt\"");
	//tests.push_back("WF.exe -f -d -s tests -n 5 -x \"stopwords.txt\"");
	//tests.push_back("WF.exe -f \"1.I Have a Dream.txt\" -n 5 -x \"stopwords.txt\"");
	//-v测试
	tests.push_back("WF.exe -f verbs.txt -n 50 ");
	tests.push_back("WF.exe -f verbs.txt -n 50  -v verbs.txt");
	//和挺词表一起使用测试正常，停词表中加入了排名前几的单词，加入后就不再输出了
	tests.push_back("WF.exe -f verbs.txt -n 50 -x stopwords.txt -v verbs.txt");
	tests.push_back("WF.exe -f -d tests -n 10 -x stopwords.txt -v verbs.txt");
	//-p功能，目前支持-n,-d -s,
	//tests.push_back("WF.exe -p 2 \"hello.txt\"");
	//tests.push_back("WF.exe -p 3 \"hello.txt\"");
	//tests.push_back("WF.exe -p 2 \"1.I Have a Dream.txt\" -n 5");
	//tests.push_back("WF.exe -p 2 -d tests -n 5");

}
void run_tests() {
	cout << "now path:" << path << endl;
	cout << "cd E:\\VSProjs\\VS2017Proj\\WF\\Debug\\" << endl;
	//system("cd E:\\VSProjs\\VS2017Proj\\WF\\Debug\\");//这行命令无法转换盘符
	SetCurrentDirectory(TEXT("E:\\VSProjs\\VS2017Proj\\WF\\Debug\\"));
	for (int i = 0; i < tests.size(); i++) {
		cout << "test cmd " << i + 1 << ":" << tests[i] << endl;
		system(tests[i].data());
		cout << endl;
		cout << "按任意键继续..." << endl;
		cout << endl;
		getchar();
	}
}
int main(int argc,char *argv[]) {
	path = argv[0];
	init_tests();
	run_tests();
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
