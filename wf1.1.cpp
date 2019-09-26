/*
function:����ļ������в��ظ��ĵ��ʣ����ճ��ִ����ɶൽ�����У����ִ���ͬ����ģ����ֵ������С� 
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
string wd = "";//����
int total;//���������� 
char buf[MAX_LINE+1];  /*������*/
char hint[1024] = "Input format:wf.exe -f file_name\nIf the file_name contains space, please use this format:Input format:wf.exe -f \"file_name\"\n";//�ļ��� 
 
//����һ���ַ� 
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
	fout<<"����\t\t\t����\t\t\t���ִ���"<<endl; 
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
    f1.open(fname, ios::in);//�Զ��ķ�ʽ�� 
    if(!f1){//�ļ������� 
        f1.close();
        f1.open(fname, ios::out);//�򴴽���
        write_file(f1);
        f1.close();
    }else{//���� 
        f1.close();
        f1.open(fname, ios::out|ios::trunc);//���ļ�����ٴ� 
        write_file(f1);
        f1.close();
    }
}
void wf(char *file_name){
	//��ʼ�� 
	wds.clear();
	wmp.clear();
	total = 0;
	wd = "";		
	
	//���ļ�		
	FILE *fp;            /*�ļ�ָ��*/
	int len;             /*���ַ�����*/
	if((fp = fopen(file_name,"r")) == NULL){
		perror("fail to read file");
		exit (1) ;
	}
	
	//�����ı� 
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
	//printf("%d\n",argc);������argc����1,ֻ��һ���������ǳ���·�� 
	if(argc==1){
		printf("���������������иó���\n");
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


