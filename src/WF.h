/*
	�����漰�����������
	WF.exe -c file_name
	WF.exe -f file_name
	WF.exe -d file_name
	WF.exe -d -s file_name
	wf.exe -x <stopwordfile>  -f <file>
	wf.exe  -p <number>  ���� <number> ˵��Ҫ������ٸ��ʵĶ���
	ǰ���˳���ǹ̶��Ŀ�ֱ��ʹ��if,else

	wf.exe -v <verb file>���й��ܺ��涼���Լ�-v
	-v���Է���ǰ��Ҳ���Է��ں���
	��������Ŀ���û��˳��
	WF.exe -f file_name -v <verb file>
	WF.exe -d file_name -v <verb file>
	WF.exe -d -s file_name -v <verb file>
	wf.exe -x <stopwordfile>  -f <file>  -v <verb file>
	wf.exe  -p <number>   -v <verb file>

	û�в��� ���hint
	-c ͳ����ĸƵ�����У��ɸߵ�������
	-f ͳ�Ƶ���Ƶ�����У��ɸߵ�������
	-d ָ���ļ�Ŀ¼��Ĭ���ǵ�ǰĿ¼��
	-s �ݹ���Ŀ¼�����ָ�����ļ�Ŀ¼����Ĭ�ϲ��ݹ飩
	-n �������һ������num������ֻ������а�ǰnum����Ĭ��Ϊ���ȫ��
	-x ָ��ͣ�ʱ���ͳ�Ƶ���ʱ������Щ���ʣ�
	-p �������һ������num, ͳ�ƶ���Ƶ�����У��ɸߵ������У�ֻͳ����num��������ɵĶ���
	-v ָ��������̬��ÿ��һ�鵥�ʣ�����һ�����ʵĲ�ͬ��̬��

	���ܵ���ϣ�
	(-c) (-d -s floder_name)|(file_path) (-n num)
	(-f) (-d -s floder_name)|(file_path)  (-n num) (-x file_path) (-v file_path)
	(-p num) (-d -s floder_name)|(file_path) (-n num) (-x file_path) (-v file_path) 
	���������е��Ǳ���
	-------------------------------------------------------------
	[]�����е��Ǳ���Ҫѡһ���Ĳ�����Ȼ������֮���˳����Ը�
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




