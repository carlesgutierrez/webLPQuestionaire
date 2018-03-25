#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "QuestionRestFul.h"
#include "webServicesManager.h"
//#include "SQLiteCpp.h"
#include "ofxImGui.h"
#include "ThemeLocalProjects.h"


class FrontEndApp
{
public:
	FrontEndApp();
	~FrontEndApp();
	void setup(webServicesManager* _webServices);
	void update();
	void updateVisualizationTokens();
	void drawGui();
	void drawVisualizationsTokens(int x, int y);
	int getActiveQuestion();
	void draw();

public: 

	webServicesManager* point2MyWeb;
	ofxImGui::Gui gui;
	ofVideoGrabber myCam;
};

