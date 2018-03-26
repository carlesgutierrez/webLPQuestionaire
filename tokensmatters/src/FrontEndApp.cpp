#include "FrontEndApp.h"

//--------------------------------------------
FrontEndApp::FrontEndApp(){

}

//--------------------------------------------
FrontEndApp::~FrontEndApp()
{
}

//--------------------------------------------
void FrontEndApp::setup(webServicesManager* _webServices){
	ofSetCircleResolution(256);

	point2MyWeb = _webServices;  // now I can have access everywhere in my app

	myCam.setup(320, 240);

	//required call
	gui.setup(new ThemeLocalProjects());
	//gui.setTheme(new ThemeLocalProjects());
}


//--------------------------------------------
void FrontEndApp::update() {

	updateVisualizationTokens();

	myCam.update();
}

//--------------------------------------------
void FrontEndApp::draw() {

	int margin = 10;

	ofSetColor(ofColor::lightGray);
	ofRectangle myCameraArea = ofRectangle(margin+ myDrawFineTunning.guiCameraPosX, margin+ myDrawFineTunning.guiCameraPosY, myCam.getWidth() + margin*2, myCam.getHeight() + margin*2);
	ofDrawRectangle(myCameraArea);

	ofSetColor(255);
	myCam.draw(myCameraArea.getPosition().x, myCameraArea.getPosition().y+ myDrawFineTunning.guiCameraPosY);

	ofSetColor(ofColor::white);
	int posXQuestionareArea = myCam.getWidth() + margin;
	int sizeWQuestionareArea = ofGetWidth() - posXQuestionareArea;
	ofRectangle myDrawQuestionaireArea = ofRectangle(posXQuestionareArea, margin, sizeWQuestionareArea - margin, 500);
	ofDrawRectangle(myDrawQuestionaireArea);

	ofSetColor(255);
	drawVisualizationsTokens(myDrawQuestionaireArea.getPosition().x, myDrawQuestionaireArea.getPosition().y);

	//GUI
	ofSetColor(255);
	drawGui();
}

//--------------------------------------------
void FrontEndApp::updateVisualizationTokens() {
	for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
		point2MyWeb->myQuestions[i].update();
	}
}


//--------------------------------------------
void FrontEndApp::drawGui() {
	gui.begin();
	if (ImGui::Button("Camera settings")){
		myCam.videoSettings();
	}
	if(ImGui::CollapsingHeader("Fine Tunning GUI Items Locations")) {
		
		bool bModifs = false;
		ImGui::PushItemWidth(50);
		if (ImGui::SliderInt("Camera X", &myDrawFineTunning.guiCameraPosX, -200, 200))bModifs = true;
		if (ImGui::SliderInt("Camera Y", &myDrawFineTunning.guiCameraPosY, -200, 200))bModifs = true;
		if(ImGui::SliderInt("Question X", &myDrawFineTunning.guiQuestionPosX, -400, 400))bModifs = true;
		if(ImGui::SliderInt("Question Y", &myDrawFineTunning.guiQuestionPosY, -200, 200))bModifs = true;
		if(ImGui::SliderInt("Labels Tokens X", &myDrawFineTunning.guiInfoTokensPosX, -200, 200))bModifs = true;
		if(ImGui::SliderInt("Labels Tokens Y", &myDrawFineTunning.guiInfoTokensPosY, -200, 200))bModifs = true;
		if(ImGui::SliderInt("Bars Tokens X", &myDrawFineTunning.guiTokensBarsX, -200, 200))bModifs = true;
		if (ImGui::SliderInt("Bars Tokens Y", &myDrawFineTunning.guiTokensBarsY, -200, 200))bModifs = true;

		if(ImGui::SliderInt("Id's Tokens X", &myDrawFineTunning.guiInfoTokensIdsPosX, -200, 200))bModifs = true;
		ImGui::PopItemWidth();
		//There should be a more elegant way to.
		if (bModifs) {
			for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
				point2MyWeb->myQuestions[i].updateFineTunningGuiDraw(myDrawFineTunning);
			}
		}
	}
	ImGui::Text("Please reply following questions. Yes or Not");


	gui.end();
}

//--------------------------------------------
void FrontEndApp::drawVisualizationsTokens(int _x, int _y) {

	//Let's draw just active question
	int idQuestionActive = getActiveQuestion();

	int marginX = 100;
	int marginY = 100;

	for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
		if (idQuestionActive == i) {
			point2MyWeb->myQuestions[i].draw(_x+ marginX, _y+ marginY);
		}
	}
}

//-------------------------------------------------
int FrontEndApp::getActiveQuestion() {
	return point2MyWeb->myQuestions.size()-1;
}