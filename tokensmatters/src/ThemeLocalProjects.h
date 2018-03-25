#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

class ThemeLocalProjects
	: public ofxImGui::BaseTheme
{
public:
	ThemeLocalProjects()
	{
		col_main_text = ofColor::gray;
		col_main_head = ofColor::orange;
		col_main_area = ofColor::green;
		col_win_popup = ofColor::yellow;
		col_win_backg = ofColor::blue;
	}
};
