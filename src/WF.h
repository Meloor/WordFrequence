/*
	可能涉及到的命令组合
	WF.exe -c file_name
	WF.exe -f file_name
	WF.exe -d file_name
	WF.exe -d -s file_name
	wf.exe -x <stopwordfile>  -f <file>
	wf.exe  -p <number>  参数 <number> 说明要输出多少个词的短语
	前面的顺序是固定的可直接使用if,else

	wf.exe -v <verb file>所有功能后面都可以加-v
	-v可以放在前面也可以放在后面
	多个参数的可以没有顺序
	WF.exe -f file_name -v <verb file>
	WF.exe -d file_name -v <verb file>
	WF.exe -d -s file_name -v <verb file>
	wf.exe -x <stopwordfile>  -f <file>  -v <verb file>
	wf.exe  -p <number>   -v <verb file>

	没有参数 输出hint
	-c 统计字母频率排行，由高到低排列
	-f 统计单词频率排行，由高到低排列
	-d 指定文件目录，默认是当前目录下
	-s 递归子目录（如果指定了文件目录）（默认不递归）
	-n 后面紧跟一个参数num，设置只输出排行榜前num个，默认为输出全部
	-x 指定停词表（在统计单词时跳过这些单词）
	-p 后面紧跟一个参数num, 统计短语频率排行，由高到低排列，只统计由num个单词组成的短语
	-v 指定动词形态表（每行一组单词，都是一个动词的不同形态）

	可能的组合：
	(-c) (-d -s floder_name)|(file_path) (-n num)
	(-f) (-d -s floder_name)|(file_path)  (-n num) (-x file_path) (-v file_path)
	(-p num) (-d -s floder_name)|(file_path) (-n num) (-x file_path) (-v file_path) 
	首先括号中的是必须
	-------------------------------------------------------------
	[]括号中的是必须要选一个的参数，然后他们之间的顺序可以改
	[(-c)] + [(-d (-s) floder_name)|(file_path)] + (-n num)

	[(-f)|(-p num)] + [(-d (-s) floder_name)|(file_path)] + (-n num) + (-x file_path) + (-v file_path) 


*/
#pragma once
#include <iostream>
#include <string>
#include "WF_c.h"
#include "WF_f.h"
#include "WF_d.h"
#include "Go.h"
using namespace std;




