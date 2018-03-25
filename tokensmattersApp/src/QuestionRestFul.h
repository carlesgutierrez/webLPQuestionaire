#pragma once

#include "ofMain.h"

#include "ofxJSONRPC.h"
#include "ofxJSON.h"


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

	void draw();

	void simulateTokensValues();

	dataQuestion theQuestion;

public: 
	//vars for visualization
	float initTime;
	float endPosition;
	std::vector<float> tokenYPosValues;

};

