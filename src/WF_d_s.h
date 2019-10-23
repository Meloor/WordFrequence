#pragma once
#include "WF_d.h"
class WF_d_s:public WF_d
{
private:
	void solve(string floder_name);
	
public:
	WF_d_s();
	~WF_d_s();
	static void Solve(string floder_name);
};

