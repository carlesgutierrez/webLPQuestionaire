#pragma once


#include "ofMain.h"

#include "webServicesManager.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void draw();
	void exit();

private:

	webServicesManager myWeb;

};