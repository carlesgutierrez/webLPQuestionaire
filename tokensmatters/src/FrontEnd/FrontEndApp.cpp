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
	imgCam.allocate(ofGetWidth(),ofGetHeight(), OF_IMAGE_COLOR);

	gui.setup(new ThemeLocalProjects());
	//gui.setTheme(new ThemeLocalProjects());

	myFlowStatus = showingReady2start;
	resetQuestionaire();
}


//--------------------------------------------
void FrontEndApp::update() {

	updateVisualizationTokens(idCurrentQuestion);

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

	if (myFlowStatus == showingQuestions || myFlowStatus == showingViz || myFlowStatus == showingResultWithCam) {
		ofSetColor(255);
		drawVisualizationsTokens(myDrawQuestionaireArea.getPosition().x, myDrawQuestionaireArea.getPosition().y);
	}
	//GUI
	ofSetColor(255);
	drawGui();
}

//--------------------------------------------
void FrontEndApp::updateVisualizationTokens(int _currentQuestionId) { //TODO that should be only our question
	//for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
	if(_currentQuestionId<point2MyWeb->myQuestions.size())
		point2MyWeb->myQuestions[_currentQuestionId].update();
	//}
}

//-------------------------------------------
void FrontEndApp::resetQuestionaire() {

	if(point2MyWeb->myQuestions.size()>0)idCurrentQuestion = 0;

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

	static bool no_titlebar = true;
	static bool no_border = true;
	static bool no_resize = true;
	static bool no_move = true;
	static bool no_scrollbar = true;
	static bool no_collapse = true;
	static bool no_menu = true;
	//required call
	// Demonstrate the various window flags. Typically you would just use the default.
	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
	//if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
	//if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
	//if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
	//if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	//if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
	//if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;

	//ImGui::SetNextWindowPos(ofVec2f(10, 400), ImGuiSetCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiSetCond_FirstUseEver);
	static bool open = true;
	ImGui::Begin("LocalProjects Demo Questionaire", &open, window_flags);

	if (myFlowStatus == showingReady2start || point2MyWeb->myQuestions.size() == 0) {
		if (point2MyWeb->myQuestions.size() == 0) {
			ImGui::Separator();
			ImGui::Text("There are no Questions available\n"
				"Please add some in the Questionaire Manager");
		}
		else if (ImGui::Button("READY?", size200)) {
			myFlowStatus = showingQuestions;
		}
	}
	
	
	if(myFlowStatus == showingQuestions){ //Ready to Start Activated with some questions in the server then

		if (point2MyWeb->myQuestions.size()>0) {
			//if(idCurrentQuestion >= 0 && idCurrentQuestion < point2MyWeb->myQuestions.size()){
				string myQuestionText = point2MyWeb->myQuestions[idCurrentQuestion].theQuestion.question;
				static bool read_only = false;
				//ImGui::InputTextMultiline("##source", myQuestionText.c_str, IM_ARRAYSIZE(myQuestionText.c_str), ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput | (read_only ? ImGuiInputTextFlags_ReadOnly : 0));
				ImGui::TextColored(ImVec4(0,255,0,200),myQuestionText.c_str());
			//}

			ImGui::Text("Please Drag and Drog Yes or Not into ANSWER");

			bool bAnswerDone = false;
			ImGui::Button("YES", size100);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Drag&Drop YES");
				if (ImGui::IsItemActive()) {
					ImGui::SetTooltip("Drop me at Answer Button");
					bDragAndDropY = true;
				}
			}


			ImGui::SameLine();

			ImGui::Button("NO", size100);
			if (ImGui::IsItemHovered()) {
				ImGui::SetTooltip("Drag&Drop NO");
				if (ImGui::IsItemActive()) {
					bDragAndDropN = true;
				}
			}

			ofSetColor(ofColor::white);
			if(bDragAndDropN)ofDrawBitmapStringHighlight("NO", ofPoint(ofGetMouseX(), ofGetMouseY()));
			if(bDragAndDropY)ofDrawBitmapStringHighlight("YES", ofPoint(ofGetMouseX(), ofGetMouseY()));

			ImGui::Separator();
			ImGui::Separator();

			ImGui::Button("ANSWER", size200);
			if (ImGui::IsMouseReleased(0) && ImGui::IsItemHoveredRect()) {
				if (bDragAndDropY || bDragAndDropN) {

					if (bDragAndDropN) {
						bAnswerDone = true;
						answersQuestions.push_back(point2MyWeb->myQuestions[idCurrentQuestion].theQuestion.dataTokenNo);
					}
					if (bDragAndDropY) {
						bAnswerDone = true;
						answersQuestions.push_back(point2MyWeb->myQuestions[idCurrentQuestion].theQuestion.dataTokenYes);
					}

					bDragAndDropN = false;
					bDragAndDropY = false;

				}
			}

			//Answer Done, then play animation and change status to Visualization Mode
			if (bAnswerDone) {
				myFlowStatus = showingViz;
				//play start our viz animation
				point2MyWeb->myQuestions[idCurrentQuestion].startAnimAnswer();
				myTimeBeforePhoto = ofGetElapsedTimef() + timeBeforeTakePhoto;
			}
		}


	}

	//---------------------------
	if (myFlowStatus == showingViz) {
		float progress = ofMap(myTimeBeforePhoto - ofGetElapsedTimef(), 5, 0, 5, 0);
		string progressText = "Let's take a photo in ["+ofToString(progress, 0)+" seconds]";
		ImGui::TextColored(ImVec4(0,255,0,200),progressText.c_str());

		//One this animation is done there will be an event that will push us to the 
		//next flow status --> showingResultWithCam 

		//TODO send After WebCam ScreenShoot // Then increase to Next Question.
		//meanWhile
		if (myTimeBeforePhoto - ofGetElapsedTimef() < 0) {
			ofLogVerbose() << "Save a Picture here";

			//TODO this inside a thread. look for an addon
			//ofImage mySavedResult;
			//mySavedResult.grabScreen(0,0, ofGetWidth(), ofGetHeight());
			imgCam.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
			//ofSaveFrame(true);
			string nameImage = ofToString(idCurrentQuestion, 0);
			//imgCam.saveThreaded("/ImagesResult/"+nameImage+"out.jpg", OF_IMAGE_QUALITY_MEDIUM);
			imgCam.saveThreaded(nameImage + "out.jpg", OF_IMAGE_QUALITY_MEDIUM);

			myFlowStatus = showingResultWithCam;
		}
	}

	//---------------------------
	if (myFlowStatus == showingResultWithCam) {


		if (idCurrentQuestion < point2MyWeb->myQuestions.size() - 1) {
				idCurrentQuestion++;
				myFlowStatus = showingQuestions;
		}
		else if (idCurrentQuestion == point2MyWeb->myQuestions.size() - 1) {

			if (ImGui::Button("Thanks!\n"
				"Restart?##Questionaire", size200)) {
				myFlowStatus = showingReady2start;
				resetQuestionaire();
			}
		}
	}

	if (bShowingOptionsGui) {
		if (ImGui::CollapsingHeader("GUI options")) {
			if (ImGui::Button("Camera settings")) {
				myCam.videoSettings();
			}
			if (ImGui::CollapsingHeader("Fine Tunning GUI Items Locations")) {

				bool bModifs = false;
				ImGui::PushItemWidth(50);
				if (ImGui::SliderInt("Camera X", &myDrawFineTunning.guiCameraPosX, -200, 200))bModifs = true;
				if (ImGui::SliderInt("Camera Y", &myDrawFineTunning.guiCameraPosY, -200, 200))bModifs = true;
				if (ImGui::SliderInt("Question X", &myDrawFineTunning.guiQuestionPosX, -400, 400))bModifs = true;
				if (ImGui::SliderInt("Question Y", &myDrawFineTunning.guiQuestionPosY, -200, 200))bModifs = true;
				if (ImGui::SliderInt("Labels Tokens X", &myDrawFineTunning.guiInfoTokensPosX, -200, 200))bModifs = true;
				if (ImGui::SliderInt("Labels Tokens Y", &myDrawFineTunning.guiInfoTokensPosY, -200, 200))bModifs = true;
				if (ImGui::SliderInt("Bars Tokens X", &myDrawFineTunning.guiTokensBarsX, -200, 200))bModifs = true;
				if (ImGui::SliderInt("Bars Tokens Y", &myDrawFineTunning.guiTokensBarsY, -200, 200))bModifs = true;

				if (ImGui::SliderInt("Id's Tokens X", &myDrawFineTunning.guiInfoTokensIdsPosX, -200, 200))bModifs = true;
				ImGui::PopItemWidth();
				//There should be a more elegant way to.
				if (bModifs) {
					for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
						point2MyWeb->myQuestions[i].updateFineTunningGuiDraw(myDrawFineTunning);
					}
				}
			}
		}
	}


	ImGui::End();
	gui.end();
}

//--------------------------------------------
void FrontEndApp::drawVisualizationsTokens(int _x, int _y) {

	//Let's draw just active question

	int marginX = 100;
	int marginY = 100;

	for (int i = 0; i < point2MyWeb->myQuestions.size(); i++) {
		if (idCurrentQuestion == i) {
			point2MyWeb->myQuestions[i].draw(_x+ marginX, _y+ marginY);
		}
	}
}