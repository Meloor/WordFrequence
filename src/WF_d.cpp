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
	/*files存储文件的路径及名称(eg.   C:\Users\WUQP\Desktop\test_devided\data1.txt)
	 ownname只存储文件的名称(eg.     data1.txt)*/

	 //文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			/*
			 * "."和".."的属性应该是文件夹
			 */
			//如果是目录 
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (_s) {//需要递归子文件夹
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFilesInFloder(p.assign(path).append("\\").append(fileinfo.name), _s);
				}
			}
			else//如果不是,加入列表 
			{			
				file_path.push_back(path + "\\" + fileinfo.name);
				file_name.push_back(fileinfo.name);				
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
bool WF_d::cmp(string &a, string &b) {
	return a < b;//小的排在前面
	//return a > b;
}
void WF_d::solve_c(string floder_name, bool _n, int _n_num, bool _s) {


}
/*
 *@ 函数当前的问题，当读到第二个文件时就会报错
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
	//获取文件名是没问题的

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
