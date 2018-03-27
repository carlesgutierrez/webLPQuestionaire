#pragma once
#include "ofMain.h"
//#include "ofxJSON.h"

class AppEvents{
public:
	static ofEvent <AppEvents> animationQuestionEnd;//Event: Questionaire --> FrontEndApp
	//static ofEvent <AppEvents> animationQuestionEnd;//
	
	//ofxJSONElement messageJson; //Check if Mutex should be implemented or not here!
};
