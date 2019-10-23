#pragma once
#include <iostream>
#include <string>
#include "WF_c.h"
#include "WF_f.h"
#include "WF_d.h"
#include "WF_d_s.h"
using namespace std;
string hint = string("Input format:\n") +
"WF.exe -c file_name\n" +
"WF.exe -f file_name\n" +
"WF.exe -d file_name\n" +
"WF.exe -d -s file_name\n" +
"If the file_name contains space, please use this format:\n" +
"WF.exe -c \"file_name\"\n";


