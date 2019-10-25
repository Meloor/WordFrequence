# WordSequence
* 开发工具：VS2017
* 实现方式：C++, 所有功能都对应一个类封装
* 提示：
	* 目前所有功能只考虑了相对路径的情况，绝对路径没有测试，有可能会出错。
    * 工程名是WF,所以生成的的exe文件名是WF.exe, 后面会改成wf.exe

## 源码更新说明：
* 实现了功能6,-v参数的作用。
* 主要更改了WF_f类
* 添加了VS2017工程压缩包
* 添加了wf.exe(由WF.exe更名过来)，在Proj目录下

## 单元测试程序WFCmdTest使用说明

* 原因：
	* 由于VS中的单元测试无法调用命令行来测试命令行参数，所以改用自定义程序。
* 使用：
	* 将测试程序设置为启动项之后编译运行
		* 该测试程序首先会将文件路径跳转到WF.exe所在的Debug目录下
		* 然后按照添加的命令行测试代码逐条测试WF.exe程序。
	* 测试文件路径
		* 由于用的是相对路径
		* 所以测试文本在WF.exe同级目录下有一篇。
        * 在文件夹TestDatas中有50篇。
        * stopwords.txt也是在同级目录下。
        
## 功能0：`-c file_path`

* 输出某个英文文本文件中 26 字母出现的频率，由高到低排列，并显示字母出现的百分比，精确到小数点后面两位。
* 例子：·`wf.exe -c file_path`

## 功能1： `-f file_path`

* 输出文件中所有不重复的单词，按照出现次数由多到少排列，出现次数同样多的，以字典序排列。
* 例子：`wf.exe -f file_path`

## 功能2： `-d (-s) floder_name`

* 无-s,指定文件目录，对目录下每一个文件执行  `wf.exe -f file_path` 的操作。
* 有-s,递归子目录:`wf.exe -f -d -s  floder_name`,功能同上,区别是会递归遍历目录下的所有子目录。
* 这里对这个功能做了小的修改，为了使“-*”命令可以叠加，这里比之前要加一个“-f"后面会解释。

## 功能3：`-n num`

* 支持 -n 参数，输出出现次数最多的前 n 个单词
* 例1:`wf.exe -f file_path -n num`
* 例2：`wf.exe -f -d -s floder_name -n num`

## 功能4: `-x _x_file_name`

* 指定stop word 文件 （停词表）， 在统计词汇的时候，跳过这些词
* 例1：`wf.exe -f file_path -n num -x _x_file_path`
* 例2：`wf.exe -f -d file_path -n num -x _x_file_path`

## 功能5：`-p _p_num`

* 输出文件中所有不重复的由固定个数单词组成的短语，按照出现次数由多到少排列，出现次数同样多的，以字典序排列。_p_num指定短语所包含的单词数。
* 例1：`wf.exe -p 2 file_path`
* 例2：`wf.exe -p 3 file_path -n _n_num`
* 例3：`wf.exe -p 2 -d -s floder_path`

## 功能6：`-v _v_file_path`

* 支持动词形态的归一化,就是把动词的各种变形都归为它的原型来统计
* 支持-f对应的功能，-p还未实现
* 例1：`wf.exe -f file_path -n _n_num -x _x_file_path -v _v_file_path`

* 例2：`wf.exe -f file_path -n _n_num -x _x_file_path -v _v_file_path`
* 例3：`wf.exe -f file_path -d floder_name -n _n_num  -v _v_file_path`




