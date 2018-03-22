#include "ofApp.h"

//---------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(30);

	ofSetLogLevel(OF_LOG_VERBOSE);

	myWeb.setup();

}

//--------------------------------------
void ofApp::draw()
{
	ofBackground(255);
	
	myWeb.draw();
}


void ofApp::exit()
{
	// Set the logger back to the default to make sure any
	// remaining messages are logged correctly.
	ofLogToConsole();
}


