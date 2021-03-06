#pragma once


#include "ofMain.h"

#include "webServicesManager.h"
#include "FrontEndApp.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void exit();

	void keyPressed(int key);

private:

	webServicesManager myWeb;
	FrontEndApp myFronEnd;
};