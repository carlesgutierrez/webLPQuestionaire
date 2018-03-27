#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "QuestionRestFul.h"
#include "webServicesManager.h"
//#include "SQLiteCpp.h"

#include "ofxImGui.h"
#include "ThemeLocalProjects.h"
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


class FrontEndApp
{
public:
	FrontEndApp();
	~FrontEndApp();
	void setup(webServicesManager* _webServices);
	void update();
	void updateVisualizationTokens();
	void resetQuestionaire();
	void drawGui();
	void drawVisualizationsTokens(int x, int y);
	int getActiveQuestion();
	void draw();

public: 

	//Flow Questionaire
	bool bReadyToStart;
	vector<ofxJSONElement>answersQuestions;
	int idCurrentQuestion = 0;

public: 

	webServicesManager* point2MyWeb;
	ofVideoGrabber myCam;


	//Gui
	ofxImGui::Gui gui;
	fineTunningGuiDraw myDrawFineTunning;


	
};

