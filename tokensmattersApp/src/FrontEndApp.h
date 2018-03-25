#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "QuestionRestFul.h"
#include "webServicesManager.h"
//#include "SQLiteCpp.h"


class FrontEndApp
{
public:
	FrontEndApp();
	~FrontEndApp();
	void setup(webServicesManager* _webServices);
	void update();
	void updateVisualizationTokens();
	void drawVisualizationsTokens(int x, int y);
	int getActiveQuestion();
	void draw();

public: 

	webServicesManager* point2MyWeb;

	ofVideoGrabber myCam;
};

