/*
function:输出文件中所有不重复的单词，按照出现次数由多到少排列，出现次数同样多的，以字典序排列。 
date:2019/9/25
author:Meloor
*/

#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<algorithm>
#include<vector>
#include<map>
#include<ctype.h>
#define MAX_LINE 1024
using namespace std;
struct Word{
	string va;
	int cnt;
	Word(string v = "a",int c = 0){
		va = v;
		cnt = c;
	}
};
vector<Word> wds; 
map<string,int> wmp;
string wd = "";//单词
int total;//单词种类数 
char buf[MAX_LINE+1];  /*缓冲区*/
char hint[1024] = "Input format:wf.exe -f file_name\nIf the file_name contains space, please use this format:Input format:wf.exe -f \"file_name\"\n";//文件名 
 
//处理一行字符 
void judge(char *a){
	for(int i=0;a[i];i++){
		if(wd.length() == 0){
			if(isalpha(a[i]))
				wd = wd + (char)tolower(a[i]);	
		}else{
			if(isalnum(a[i]))
				wd = wd + (char)tolower(a[i]);
			else{
				if(wmp.count(wd) == 0){
					wmp[wd] = 0; 
				 	total++;
				} 
				wmp[wd] = wmp[wd] + 1;
				wd = "";	
			} 						
		}
	}
}
bool cmp(Word a,Word b){
	return (a.cnt > b.cnt)||(a.cnt == b.cnt && a.va > b.va);
}
void write_file(fstream &fout){
	fout<<"排名\t\t\t单词\t\t\t出现次数"<<endl; 
    for(int i=0;i<wds.size();i++){
    	fout<<i+1<<"\t\t\t";
    	fout<<wds[i].va;
		int nt = wds[i].va.length()/8;
		//int flag = wds[i].va.length()%8;
		//if(flag==0)
		for(int j=0;j<3-nt;j++)fout<<"\t";
		fout<<wds[i].cnt<<endl;	
	}
}
void open_write(char *origin_file_name){
	fstream f1;
	char fname[128] = "word rate of ";
	strcat(fname,origin_file_name);
	printf("write to \"%s\"\n",fname);
    f1.open(fname, ios::in);//以读的方式打开 
    if(!f1){//文件不存在 
        f1.close();
        f1.open(fname, ios::out);//则创建它
        write_file(f1);
        f1.close();
    }else{//存在 
        f1.close();
        f1.open(fname, ios::out|ios::trunc);//将文件清空再打开 
        write_file(f1);
        f1.close();
    }
}
void wf(char *file_name){
	//初始化 
	wds.clear();
	wmp.clear();
	total = 0;
	wd = "";		
	
	//打开文件		
	FILE *fp;            /*文件指针*/
	int len;             /*行字符个数*/
	if((fp = fopen(file_name,"r")) == NULL){
		perror("fail to read file");
		exit (1) ;
	}
	
	//处理文本 
	while(fgets(buf,MAX_LINE,fp) != NULL){
		len = strlen(buf);
		judge(buf);
	}

	map<string, int>::iterator  it;
	for(it = wmp.begin();it != wmp.end();it++){
		wds.push_back(Word(it->first,it->second));
    }
    sort(wds.begin(),wds.end(),cmp);
    open_write(file_name);
}
int main(int argc,char *argv[]){
	//printf("%d\n",argc);运行了argc就是1,只有一个参数就是程序路径 
	if(argc==1){
		printf("请在命令行中运行该程序！\n");
		printf("%s\n",hint);
	}else if(argc==2){
		printf("%s\n",hint);
	}else if(argc==3){
		if(strcmp(argv[1],"-f")==0){
			wf(argv[2]);
		}else printf("%s\n",hint);
	}
	return 0;
} 


