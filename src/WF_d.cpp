#include "pch.h"
#include "WF_d.h"
#include "WF_f.h"

WF_d::WF_d()
{
}


WF_d::~WF_d()
{
}
void WF_d::getFilesInFloder(string path,bool _s)
{
	//cout << path << endl;
	/*files�洢�ļ���·��������(eg.   C:\Users\WUQP\Desktop\test_devided\data1.txt)
	 ownnameֻ�洢�ļ�������(eg.     data1.txt)*/

	 //�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			/*
			 * "."��".."������Ӧ�����ļ���
			 */
			//�����Ŀ¼ 
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (_s) {//��Ҫ�ݹ����ļ���
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFilesInFloder(p.assign(path).append("\\").append(fileinfo.name), _s);
				}
			}
			else//�������,�����б� 
			{			
				file_path.push_back(path + "\\" + fileinfo.name);
				file_name.push_back(fileinfo.name);				
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
bool WF_d::cmp(string &a, string &b) {
	return a < b;//С������ǰ��
	//return a > b;
}
void WF_d::solve_c(string floder_name, bool _n, int _n_num, bool _s) {


}
/*
 *@ ������ǰ�����⣬�������ڶ����ļ�ʱ�ͻᱨ��
 */
void WF_d::solve_f(string floder_name, bool _n, int _n_num, bool _s) {
	file_path.clear();
	file_name.clear();
	getFilesInFloder(floder_name, _s);
	printf("file num:%d\n", file_path.size());

	sort(file_path.begin(), file_path.end(),cmp);
	for (int i = 0; i < file_path.size(); i++) {
		cout << file_path[i] << endl;
	}
	//��ȡ�ļ�����û�����

	for (int i = 0; i < file_path.size(); i++) {
		printf("%2d statisticsing file \"%s\" ...\n", i + 1, file_name[i].data());
		WF_f::Solve(file_path[i],_n,_n_num);
	}
}
void WF_d::solve_p(string floder_name, bool _n, int _n_num, bool _s) {

}
void WF_d::Solve_c(string floder_name, bool _n, int _n_num, bool _s) {

}
void WF_d::Solve_f(string floder_name, bool _n, int _n_num, bool _s) {
	WF_d wf_d;
	wf_d.solve_f(floder_name,_n,_n_num,_s);
}
void WF_d::Solve_p(string floder_name, bool _n, int _n_num, bool _s) {

}
