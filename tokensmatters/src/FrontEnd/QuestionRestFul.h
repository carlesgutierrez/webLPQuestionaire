#pragma once

#include "ofMain.h"

#include "ofxJSONRPC.h"
#include "ofxJSON.h"
#include "ofxEasing.h"


struct fineTunningGuiDraw {

	int guiQuestionPosX = -67;
	int guiQuestionPosY = -100;
	int guiInfoTokensPosX = 78;
	int guiInfoTokensPosY = 112;
	int guiTokensBarsX = 128;
	int guiTokensBarsY = 0;
	int guiInfoTokensIdsPosX = 0;

	//Camera
	int guiCameraPosX = 0;
	int guiCameraPosY = 11;
};

struct dataToken { //TODO chahge this direct from JSON format at Defaoult constructor
	int incomeTax = 0;
	int publicHealth = 0;
	int entrepreneurship = 0;
	int communityArt = 0;
	int immigration = 0;
};


struct dataQuestion {
	int id = -1;
	string question = "empty";
	int answer = -1; // 0 (false), 1 (true), 2 (others) 
	ofxJSONElement dataTokenYes; //dataToken ofxJSONElement
	ofxJSONElement dataTokenNo; //dataToken ofxJSONElement
};

class QuestionRestFul
{
public:
	QuestionRestFul();
	~QuestionRestFul();

	void setup();
	void startAnimAnswer();
	void update();
	void updateFineTunningGuiDraw(fineTunningGuiDraw myFineTunningDrawGui);
	void draw(int x, int y);
	
	void simulateTokensValues();
	void resetAnimations();

	dataQuestion theQuestion;
	

public: 
	//vars for visualization
	bool bStartAnimAnswer = false;
	float initTime;
	float endPosition;
	std::vector<float> tokenYPosEasing, tokenNPosEasing; //TODO CHECK HOW TO REMOVE THIS
	bool bAnimRunning = false;

private:
	fineTunningGuiDraw myFineTunningDrawGui;
};

