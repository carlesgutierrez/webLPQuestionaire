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

//-------------------------------------------
void FrontEndApp::resetQuestionaire() {

	bReadyToStart = true;

	if(point2MyWeb->myQuestions.size()>0)idCurrentQuestion = 0;
	else {
		idCurrentQuestion = -1;
	}

	//reset of results questionaire
	answersQuestions.clear();
	answersQuestions.resize(point2MyWeb->myQuestions.size());
	
	for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
		point2MyWeb->myQuestions[i].resetAnimations();
	}

}


//--------------------------------------------
void FrontEndApp::drawGui() {
	ImVec2 size100 = ImVec2(50, 50);
	ImVec2 size200 = ImVec2(100, 100);

	gui.begin();

	ImGui::Text("///////////////////////////////////////");

	if (bReadyToStart) {
		if (ImGui::Button("READY?", size200)) {
			bReadyToStart = false;
		}
	}
	else {

		//If there is a question to work with
		if (point2MyWeb->myQuestions.size()) {
			if(idCurrentQuestion > -1){
				string myQuestionText = point2MyWeb->myQuestions[idCurrentQuestion].theQuestion.question;
				static bool read_only = false;
				//ImGui::InputTextMultiline("##source", myQuestionText.c_str, IM_ARRAYSIZE(myQuestionText.c_str), ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput | (read_only ? ImGuiInputTextFlags_ReadOnly : 0));
				ImGui::Text(myQuestionText.c_str());

			}

			
			ImGui::Text("Please Drag and Drog Yes or Not into ANSWER");

			if (ImGui::Button("YES", size100)) {
				if (point2MyWeb->myQuestions.size() > idCurrentQuestion) {
					answersQuestions.push_back(point2MyWeb->myQuestions[idCurrentQuestion].theQuestion.dataTokenYes);
				}
				if (point2MyWeb->myQuestions.size() - 1 > idCurrentQuestion) {
					point2MyWeb->myQuestions[idCurrentQuestion].startAnimAnswer();
					idCurrentQuestion++; //TODO This should come after animation. // Then After WebCam ScreenShoot // Then increase to Next Question.
				}
			}

			ImGui::SameLine();

			if (ImGui::Button("NO", size100)) {
				if (point2MyWeb->myQuestions.size() > idCurrentQuestion) {
					answersQuestions.push_back(point2MyWeb->myQuestions[idCurrentQuestion].theQuestion.dataTokenNo);
				}
				if (point2MyWeb->myQuestions.size() - 1 > idCurrentQuestion) {
					point2MyWeb->myQuestions[idCurrentQuestion].startAnimAnswer();
					idCurrentQuestion++; //TODO This should come after animation. // Then After WebCam ScreenShoot // Then increase to Next Question.
				}
			}

			//ImGui::IsItemHovered()
			ImGui::Button("ANSWER", size200);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("DragHere YES or NOT");
				if (ImGui::IsItemActive()) {
					ImGui::SetTooltip("IsItemActive!");
				}
			}
		}


		
	}


	if (ImGui::Button("Reset Questionaire")) {
		resetQuestionaire();
	}

	ImGui::Text("///////////////////////////////////////");

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
	


	gui.end();
}

//--------------------------------------------
void FrontEndApp::drawVisualizationsTokens(int _x, int _y) {

	//Let's draw just active question
	idCurrentQuestion = getActiveQuestion();

	int marginX = 100;
	int marginY = 100;

	for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
		if (idCurrentQuestion == i) {
			point2MyWeb->myQuestions[i].draw(_x+ marginX, _y+ marginY);
		}
	}
}

//-------------------------------------------------
int FrontEndApp::getActiveQuestion() {
	int idActive = -1;//This negative index will never happen, always checking inside myQuestions. If MyQuestions is 0 there is no get values in
	if (point2MyWeb->myQuestions.size() > 0)
		idActive = idCurrentQuestion;
	return idActive;
}