#include "pch.h"
#include "WF_c.h"


WF_c::WF_c()
{
}

WF_c::~WF_c()
{
}
int to_id(char x) {
	if (isupper(x))	return x - 'A';
	else if (islower(x))	return x - 'a';
}
void WF_c::judge(char a[]) {
	for (int i = 0; a[i]; i++) {
		if(isalpha(a[i])){
			total++;
			num[to_id(a[i])]++;
		}
	}
}
void WF_c::solve(char *file_name) {
	memset(num, 0, sizeof(num));
	total = 0;

	ifstream fin;
	fin.open(file_name);
	if (!fin.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}

	while (!fin.eof())
	{
		fin.getline(buf, MAX_LINE);
		judge(buf);
	}	
	for (int i = 0; i < 26; i++) {
		wf[i].name = i + 'a';
		wf[i].wf = 1.0*num[i] / total;
	}
	sort(wf, wf + 26);
	for (int i = 0; i < 26; i++) {
		printf("%2d %c:%.2f\n", i + 1, wf[i].name, wf[i].wf);
	}
}
void WF_c::Solve(char *file_name) {
	WF_c* wf_c = new WF_c();
	wf_c->solve(file_name);
}
