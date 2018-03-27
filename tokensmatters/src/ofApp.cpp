#include "ofApp.h"

//---------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(30);

	ofSetLogLevel(OF_LOG_VERBOSE);

	myWeb.setup(); //back-end
	myFronEnd.setup(&myWeb);//Let's set a refernce to our web data service to get direct access into data.

}

//--------------------------------------
void ofApp::draw()
{
	ofBackground(255);
	
	myWeb.draw();


	myFronEnd.update();
	myFronEnd.draw();
}


void ofApp::exit()
{
	// Set the logger back to the default to make sure any
	// remaining messages are logged correctly.
	ofLogToConsole();
}

void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_TAB) {
		myFronEnd.bShowingOptionsGui = !myFronEnd.bShowingOptionsGui;
	}
}


