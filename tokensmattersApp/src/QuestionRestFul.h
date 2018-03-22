#pragma once

#include "ofMain.h"

#include "ofxJSONRPC.h"
#include "ofxJSON.h"


struct dataToken {
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
	ofxJSONElement dataTokenYes;
	ofxJSONElement dataTokenNo;
};

class QuestionRestFul
{
public:
	QuestionRestFul();
	~QuestionRestFul();

	void setup();


	dataQuestion theQuestion;


};

