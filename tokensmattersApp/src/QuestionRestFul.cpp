#include "QuestionRestFul.h"


//--------------------------------------------
QuestionRestFul::QuestionRestFul()
{
	//Creating model that tokens user interaction will use dinamically
	string incomeTaxValue;
	string publicHealthValue;
	string entrepreneurshipValue;
	string immigrationValue;

	incomeTaxValue = ofToString(0, 0);
	publicHealthValue = ofToString(0, 0);
	entrepreneurshipValue = ofToString(0, 0);
	immigrationValue = ofToString(0, 0);

	string dataTokenDefault =
		"{\"#0 incomeTax\":" + incomeTaxValue +
		", \"#1 publicHealth\" : " + publicHealthValue +
		", \"#2 entrepreneurship\" : " + entrepreneurshipValue +
		", \"#3 immigration\" : " + immigrationValue + " }";
	theQuestion.dataTokenYes.parse(dataTokenDefault);
	theQuestion.dataTokenNo.parse(dataTokenDefault);

	//For Drawing
	tokenYPosEasing.resize(4);
	tokenNPosEasing.resize(4);
}

//--------------------------------------------
QuestionRestFul::~QuestionRestFul()
{
}

//--------------------------------------------
void QuestionRestFul::setup()
{
	simulateTokensValues();
}


//--------------------------------------------
void QuestionRestFul::update()
{
	//update Visualizations
	//Update
	if (ofGetKeyPressed()) {
		bStartAnim = true;
		initTime = ofGetElapsedTimef();
	}

	auto duration = 1.f;
	auto endTime = initTime + duration;
	auto now = ofGetElapsedTimef();
	
	vector<string>tokensnames = theQuestion.dataTokenYes.getMemberNames();

	//incomeTax for now
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		
		int endPosition = ofMap(theQuestion.dataTokenYes[tokensnames[i]].asFloat(),-5, 5, -100, 100);
		tokenYPosEasing[i] = ofxeasing::map_clamp(now, initTime, endTime, 0, endPosition, &ofxeasing::linear::easeIn);

	}


}


//--------------------------------------------
void QuestionRestFul::draw(int _x, int _y)
{
	ofPushStyle();
	ofSetLineWidth(5);
	//draw Visualizations
	ofSetColor(ofColor::darkCyan);
	
	auto w = 20;
	int tokensNamesMaxWidth = 150;
	int gapXTokens = 100;
	int gapYNameTokens = 20;
	int marginYTokens = 60;

	ofSetColor(ofColor::white);
	ofDrawBitmapStringHighlight(theQuestion.question, _x, _y);
	ofSetColor(ofColor::darkCyan);

	//draw Text Tokens vertical drawn at left colum
	vector<string>tokensnamesVertical = theQuestion.dataTokenYes.getMemberNames();//Yes or not same name
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		ofDrawBitmapStringHighlight(tokensnamesVertical[i], _x - tokensNamesMaxWidth, _y + gapYNameTokens * i);
	}

	//Tokens Yes
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		ofDrawRectangle(_x+i*gapXTokens, _y + marginYTokens, w, tokenYPosEasing[i]); // 0 IncomeTax, 1 ... , ..
	}

	//Tokens NO
	//for (int i = 0; i < tokenYPosEasing.size(); i++) {
	//	ofDrawRectangle(_x + i*gapXTokens, _y, w, tokenYPosEasing[i]); // 0 IncomeTax, 1 ... , ..
	//}

	//draw Text Tokens horizontal
	vector<string>tokensnamesHorizontal = theQuestion.dataTokenYes.getMemberNames();//Yes or not same name
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		vector<string> slitedName = ofSplitString(tokensnamesHorizontal[i], " ");
		ofDrawBitmapStringHighlight(slitedName[0], _x+ i*gapXTokens, _y + marginYTokens * 3 );
	}

	//string name;
	//vector<string> slitedName = ofSplitString(name, " ");
	
	ofPopStyle();
}



//--------------------------------------------
void QuestionRestFul::simulateTokensValues()
{

	int incomeTaxValue;
	int immigrationValue;
	int entrepreneurshipValue;
	int publicHealthValue;

	incomeTaxValue = (int)ofRandom(-5, 5);
	publicHealthValue = (int)ofRandom(-5, 5);
	entrepreneurshipValue = (int)ofRandom(-5, 5);
	immigrationValue = (int)ofRandom(-5, 5);

	theQuestion.dataTokenYes["#0 incomeTax"] = incomeTaxValue;
	theQuestion.dataTokenYes["#1 publicHealth"] = publicHealthValue;
	theQuestion.dataTokenYes["#2 entrepreneurship"] = entrepreneurshipValue;
	theQuestion.dataTokenYes["#3 immigration"] = immigrationValue;

	ofLogVerbose() << "Random tokens Yes:" << theQuestion.dataTokenYes;


	incomeTaxValue = (int)ofRandom(-5, 5);
	publicHealthValue = (int)ofRandom(-5, 5);
	entrepreneurshipValue = (int)ofRandom(-5, 5);
	immigrationValue = (int)ofRandom(-5, 5);

	theQuestion.dataTokenNo["#0 incomeTax"] = incomeTaxValue;
	theQuestion.dataTokenNo["#1 publicHealth"] = publicHealthValue;
	theQuestion.dataTokenNo["#2 entrepreneurship"] = entrepreneurshipValue;
	theQuestion.dataTokenNo["#3 immigration"] = immigrationValue;

	ofLogVerbose() << "Random tokens No:" << theQuestion.dataTokenNo;

}



