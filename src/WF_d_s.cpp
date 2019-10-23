#include "pch.h"
#include "WF_d_s.h"


WF_d_s::WF_d_s()
{
}


WF_d_s::~WF_d_s()
{
}
void WF_d_s::solve(string floder_name) {
	WF_d::solve(floder_name,true);
}
void WF_d_s::Solve(string floder_name) {
	WF_d_s WF_d_s;
	WF_d_s.solve(floder_name);
}
