/*
function:ͳ��Ӣ���ı���26����ĸ���ֵ�Ƶ�� 
date:2019/9/25
author:Meloor
*/

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<algorithm>
#define MAX_LINE 1024
using namespace std;
struct ZM{
	char name;
	float wf;
	ZM(char n = 'a',float w = 0){
		name = n;
		wf = w;
	}
};
int num[26];
int total;//Լ3e6�ַ���5e4�� 
ZM wf[26];
char buf[MAX_LINE+1];  /*������*/
char hint[1024] = "Input format:wf.exe -c file_name\nIf the file_name contains space, please use this format:Input format:wf.exe -c \"file_name\"\n";//�ļ��� 
 
bool is_uppercase_letter(char x){
	return 'A' <= x && x <= 'Z';
}
bool is_lowercase_letter(char x){
	return 'a' <= x && x <= 'z';
}
bool is_letter(char x){
	return is_uppercase_letter(x)||is_lowercase_letter(x);		
}
int to_id(char x){
	if(is_uppercase_letter(x))	return x-'A';
	else if(is_lowercase_letter(x))	return x-'a';
} 
void judge(char a[]){
	for(int i=0;a[i];i++){
		if(is_letter(a[i])){
			total++;
			num[to_id(a[i])]++;
		}
	}
}
bool cmp(ZM a,ZM b){
	return (a.wf > b.wf) || (a.wf == b.wf&&a.name<b.name);
}
void WF(char *file_name){
	memset(num,0,sizeof(num)*26);
	total = 0;	
	//file_name = "Gone With The Wind.docx"; 
			
	FILE *fp;            /*�ļ�ָ��*/
	int len;             /*���ַ�����*/
	if((fp = fopen(file_name,"r")) == NULL){
		perror("fail to read file");
		exit (1) ;
	}
	while(fgets(buf,MAX_LINE,fp) != NULL){
		len = strlen(buf);
		judge(buf);
		//printf("%s %d \n",buf,len - 1);
	}
	for(int i=0;i<26;i++){
		wf[i].name = i + 'a';
		wf[i].wf = 1.0*num[i]/total;
	}			
	sort(wf,wf+26,cmp);
	for(int i=0;i<26;i++){
		printf("%2d %c:%.2f\n",i+1,wf[i].name,wf[i].wf);
	}
}
int main(int argc,char *argv[]){
	//printf("%d\n",argc);������argc����1,ֻ��һ���������ǳ���·�� 
	if(argc==1){
		printf("���������������иó���\n");
		printf("%s\n",hint);
	}else if(argc==2){
		printf("%s\n",hint);
	}else if(argc==3){
		if(strcmp(argv[1],"-c")==0){
			WF(argv[2]);
		}else printf("%s\n",hint);
	}
	return 0;
} 


