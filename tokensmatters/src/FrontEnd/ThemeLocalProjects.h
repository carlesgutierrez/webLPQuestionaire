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

	////--------------------------------------------------------------
	//void ThemeLocalProjects::setup()
	//{
	//	ImGuiStyle* style = &ImGui::GetStyle();

	//	style->WindowMinSize = ImVec2(160, 65);
	//	style->FramePadding = ImVec2(4, 2);
	//	style->ItemSpacing = ImVec2(6, 2);
	//	style->ItemInnerSpacing = ImVec2(6, 4);
	//	style->Alpha = 1.0f;
	//	style->WindowRounding = 0.0f;
	//	style->FrameRounding = 0.0f;
	//	style->IndentSpacing = 6.0f;
	//	style->ItemInnerSpacing = ImVec2(2, 4);
	//	style->ColumnsMinSpacing = 50.0f;
	//	style->GrabMinSize = 14.0f;
	//	style->GrabRounding = 0.0f;
	//	style->ScrollbarSize = 12.0f;
	//	style->ScrollbarRounding = 0.0f;
	//}
};
