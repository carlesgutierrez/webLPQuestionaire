#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "QuestionRestFul.h"
#include "webServicesManager.h"
//#include "SQLiteCpp.h"
#include "ofxThreadedImage.h"

#include "ofxImGui.h"
#include "ThemeLocalProjects.h"
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


enum statusFrontEnd {showingReady2start, showingQuestions, showingViz, showingResultWithCam, showingEnd};


class FrontEndApp
{
public:
	FrontEndApp();
	~FrontEndApp();
	void setup(webServicesManager* _webServices);
	void setupShader();
	void update();
	void updateVisualizationTokens(int currentQuestion);
	void resetQuestionaire();
	void drawGui();
	void drawVisualizationsTokens(int x, int y);
	//int getActiveQuestion();
	void draw();

	//Main access to Data -> Questions
	webServicesManager* point2MyWeb;

public: 

	//Flow Questionaire
	int myTimeBeforePhoto = -1;
	int timeBeforeTakePhoto = 5;
	statusFrontEnd myFlowStatus;//init a setup
	//bool bReadyToStart;
	vector<ofxJSONElement>answersQuestions;
	int idCurrentQuestion = 0;


public:

	//Gui
	ofxImGui::Gui gui;
	bool bShowingOptionsGui = false;
	fineTunningGuiDraw myDrawFineTunning;

public:

	//DragAndDrop
	bool bDragAndDropY = false;
	bool bDragAndDropN = false;

public:

	ofVideoGrabber myCam;
	ofxThreadedImage imgCam;
	ofShader shader;
	ofFbo fbo;
	ofFbo maskFbo;
	ofImage imageMask;
	
};

