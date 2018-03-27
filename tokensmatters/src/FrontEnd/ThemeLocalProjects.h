#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

class ThemeLocalProjects
	: public ofxImGui::BaseTheme
{
public:
	ThemeLocalProjects()
	{
		col_main_text = ofColor::antiqueWhite;
		col_main_head = ofColor::darkCyan;
		col_main_area = ofColor::blueSteel;
		col_win_popup = ofColor::yellow;
		col_win_backg = ofColor::black;
	}
};
