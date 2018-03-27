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
void QuestionRestFul::startAnimAnswer() {
	bStartAnimAnswer = true;
}

//--------------------------------------------
void QuestionRestFul::update()
{
	//update Visualizations
	//Update
	if (bStartAnimAnswer) {
		bAnimRunning = true;
		initTime = ofGetElapsedTimef();
		bStartAnimAnswer = false;
		//TODO send event to FrontEndApp we finished to show our SHow


	}

	if (bAnimRunning) {

		auto duration = 1.f;
		auto endTime = initTime + duration;
		auto now = ofGetElapsedTimef();

		vector<string>tokensnames = theQuestion.dataTokenYes.getMemberNames();

		//incomeTax for now
		for (int i = 0; i < tokenYPosEasing.size(); i++) {

			int endPosition = ofMap(theQuestion.dataTokenYes[tokensnames[i]].asFloat(), -5, 5, -100, 100);
			tokenYPosEasing[i] = ofxeasing::map_clamp(now, initTime, endTime, 0, endPosition, &ofxeasing::linear::easeIn);

		}

	}


}

void QuestionRestFul::updateFineTunningGuiDraw(fineTunningGuiDraw _myFineTunningDrawGui)
{
	myFineTunningDrawGui = _myFineTunningDrawGui;
}


//--------------------------------------------
void QuestionRestFul::draw(int _x, int _y)
{
	ofPushStyle();
	ofSetLineWidth(5);
	//draw Visualizations
	ofSetColor(ofColor::darkCyan);
	
	int w = 20;
	int tokensNamesMaxWidth = 150;
	int gapXTokens = 100;
	int gapYNameTokens = 20;
	int marginYTokens = 60;

	//Draw Question
	ofSetColor(ofColor::white);
	ofDrawBitmapStringHighlight("#"+ofToString(theQuestion.id)+"->"+theQuestion.question, _x+ myFineTunningDrawGui.guiQuestionPosX, _y+ myFineTunningDrawGui.guiQuestionPosY, ofColor::darkCyan);
	ofSetColor(ofColor::darkCyan);

	//draw Text Tokens vertical drawn at left colum
	vector<string>tokensnamesVertical = theQuestion.dataTokenYes.getMemberNames();//Yes or not same name
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		ofDrawBitmapStringHighlight(tokensnamesVertical[i], _x - tokensNamesMaxWidth + myFineTunningDrawGui.guiInfoTokensPosX, myFineTunningDrawGui.guiInfoTokensPosY + _y + gapYNameTokens * i);
	}

	ofSetColor(ofColor::black);
	//Simple line in the middle of the chart
	int middleHeightChartViz = _y + marginYTokens + myFineTunningDrawGui.guiTokensBarsY;
	ofLine(myFineTunningDrawGui.guiTokensBarsX + _x, middleHeightChartViz, myFineTunningDrawGui.guiTokensBarsX + _x + (tokenYPosEasing.size()-1)*gapXTokens + w, middleHeightChartViz);

	ofSetColor(ofColor::darkCyan);
	//Tokens Yes
	int HZeroSize = 1;
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		if(tokenYPosEasing[i] == 0)	ofDrawRectangle(myFineTunningDrawGui.guiTokensBarsX + _x + i*gapXTokens, _y + marginYTokens + myFineTunningDrawGui.guiTokensBarsY + HZeroSize, w, HZeroSize*2); // 0 IncomeTax, 1 ... , ..
		else {
			ofDrawRectangle(myFineTunningDrawGui.guiTokensBarsX + _x + i*gapXTokens, middleHeightChartViz, w, tokenYPosEasing[i]); // 0 IncomeTax, 1 ... , ..
		}
		
	}

	//Tokens NO
	//for (int i = 0; i < tokenYPosEasing.size(); i++) {
	//	ofDrawRectangle(_x + i*gapXTokens, _y, w, tokenYPosEasing[i]); // 0 IncomeTax, 1 ... , ..
	//}

	//draw Text Tokens horizontal Ids
	vector<string>tokensnamesHorizontal = theQuestion.dataTokenYes.getMemberNames();//Yes or not same name
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		vector<string> slitedName = ofSplitString(tokensnamesHorizontal[i], " ");
		ofDrawBitmapStringHighlight(slitedName[0], myFineTunningDrawGui.guiTokensBarsX + _x+ i*gapXTokens, _y + marginYTokens * 3 );
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

//-------------------------------------------
void QuestionRestFul::resetAnimations()
{
	bStartAnimAnswer = true; //Reset
	bAnimRunning = false;
	for (int i = 0; i < tokenYPosEasing.size(); i++) {
		tokenYPosEasing[i] = 0;//Reset Animations
	}
}



