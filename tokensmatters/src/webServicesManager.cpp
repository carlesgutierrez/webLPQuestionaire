#include "webServicesManager.h"


//--------------------------------------------
webServicesManager::webServicesManager()
{
}

//--------------------------------------------
webServicesManager::~webServicesManager()
{
}

//--------------------------------------------
void webServicesManager::setup()
{
	// Load test text.
	ipsum = ofBufferFromFile("media/ipsum.txt").getText();


	ofx::HTTP::JSONRPCServerSettings settings;
	//settings.setHost("DocumentRoot/index.html"); //localhost/localprojects/index.html --> not work. This addon is an HTTP server it self. 
	settings.setPort(8197);//8197 //8998(default) //80 or 8080 if its the same as APACH, make  this crash

						   // Initialize the server.
	server.setup(settings);


	// Register RPC methods.
	server.registerMethod("get-questions-server",
		"Returns all questions",
		this,
		&webServicesManager::doGet);

	server.registerMethod("update-questionId-server",
		"Returns thta question if extist.",
		this,
		&webServicesManager::doPatch);
	

	server.registerMethod("set-question-server",
		"Add a new question",
		this,
		&webServicesManager::doPost);

	server.registerMethod("delete-question-server",
		"Add a new question",
		this,
		&webServicesManager::doDelete);

	// Start the server.
	server.start();

	// Launch a browser with the address of the server.
	ofLaunchBrowser(server.getURL());

	//Sqlite
	std::string exampleDB = ofToDataPath("tokensmatters.sqlite", true);
	myDB.setupDB(exampleDB, "question", "tokensNo", "tokensYes");
}


void webServicesManager::draw()
{
	ofDrawBitmapStringHighlight(userText, ofPoint(14, 18));
}



//--------------------------------------------
void webServicesManager::doPost(ofx::JSONRPC::MethodArgs & args)
{
	if (ofGetLogLevel() == OF_LOG_VERBOSE) {
		cout << "All args to doPost are" << args.params << endl;
		for (int i = 0; i < args.params.size(); i++) {
			//TOcheck param 0 Null
			cout << "Arg[" + ofToString(i, 0) + "]=" << args.params[i] << endl;
		}
	}

	//1rs Add Question to vector
	QuestionRestFul myAuxQuest;

	if (args.params.size() == 2) {
		myAuxQuest.theQuestion.id = myQuestions.size()+1;
		myAuxQuest.theQuestion.question = args.params[1].asString();
		myAuxQuest.simulateTokensValues();// Simulate my content
		//myAuxQuest.question.answer = ofToInt(args.params[2].asString()); //Do not crash if there is nothing. That's good.
		myQuestions.push_back(myAuxQuest);
		

		//Trying sqlite test // Fails something here
		DbQuestions myDB;
		myDB.insertQuestionData(myAuxQuest);
	}
	//TODO Later update it into mySql item

	ofLogVerbose("webServicesManager::doPost") << args.params.asString();
}

//--------------------------------------------
void webServicesManager::doGet(ofx::JSONRPC::MethodArgs & args)
{
	// Set the result equal to the substring.
	args.result = getMyQuestionsData();

	ofLogVerbose("webServicesManager::getQuestions") << args.result;//.asString()
}

//--------------------------------------------
void webServicesManager::doPatch(ofx::JSONRPC::MethodArgs & args)
{
	if (ofGetLogLevel() == OF_LOG_VERBOSE) {
		cout << "Update Question Id" << args.params << endl;
		for (int i = 0; i < args.params.size(); i++) {
			cout << "Arg[" + ofToString(i, 0) + "]=" << args.params[i] << endl;
		}
	}

	// Set the result equal to the substring.
	int auxIdQuestion = ofToInt(args.params[0].asString());//without this cast to String this break this function
	string newQuestion = args.params[1].asString();

	bool bUpdated = updateQuestionData(auxIdQuestion, newQuestion);
	if (bUpdated) ofLogVerbose("Question[" + ofToString(auxIdQuestion, 0) + "] updated");
}

//--------------------------------------------
void webServicesManager::doDelete(ofx::JSONRPC::MethodArgs& args)
{
	int id2Delete = ofToInt(args.params.asString());
	ofLogVerbose("id[" + ofToString(id2Delete, 0) + "] to Delete");
	bool bUpdated = deleteQuestionData(id2Delete);
	if (bUpdated) ofLogVerbose("Question[" + ofToString(id2Delete, 0) + "] deleted");
}


//------------------------------------------------------
bool webServicesManager::updateQuestionData(int auxIdQuestion,string newQuestion) {
	bool bFoundQuestion = false;
	for (int i = 0; i < myQuestions.size(); i++) {
		if (myQuestions[i].theQuestion.id == auxIdQuestion) {
			bFoundQuestion = true;
			myQuestions[i].theQuestion.question = newQuestion;
		}
	}

	return bFoundQuestion;
}

//------------------------------------------------------
bool webServicesManager::deleteQuestionData(int auxIdQuestion) {
	bool bFoundQuestion = false;
	for (int i = 0; i < myQuestions.size(); i++) {
		if (myQuestions[i].theQuestion.id == auxIdQuestion) {
			bFoundQuestion = true;
			myQuestions.erase(myQuestions.begin() +i);
		}
	}

	return bFoundQuestion;
}


//------------------------------------------------------
ofxJSONElement webServicesManager::getMyQuestionsData()
{

	ofxJSONElement thatSavedQuestions;

	for (int i = 0; i < myQuestions.size(); i++) {
		thatSavedQuestions[i]["id"] = ofToString(myQuestions[i].theQuestion.id, 0);
		thatSavedQuestions[i]["question"] = myQuestions[i].theQuestion.question;
	}

	return thatSavedQuestions;
}
