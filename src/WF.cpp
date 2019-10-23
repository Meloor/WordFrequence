// WordFrequence.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "WF.h"

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("请在命令行中运行该程序！\n");
		cout << hint << endl;
	}
	else if (argc == 2) {
		cout << hint << endl;
	}
	else if (argc == 3) {
		if (strcmp(argv[1], "-c") == 0) {
			WF_c::Solve(string(argv[2]));
		}
		else if (strcmp(argv[1], "-f") == 0) {
			WF_f::Solve(string(argv[2]));
		}
		else if (strcmp(argv[1], "-d") == 0) {
			WF_d::Solve(string(argv[2]));
		}
		else printf("%s\n", hint);
	}
	else if (argc == 4) {
		if (strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-s") == 0) {
			WF_d_s::Solve(string(argv[3]));
		}
	}
	else cout << hint << endl;
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
