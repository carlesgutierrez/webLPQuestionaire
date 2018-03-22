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
	server.registerMethod("get-questions",
		"Returns a random chunk of text to the client.",
		this,
		&webServicesManager::getQuestions);

	server.registerMethod("set-question",
		"Sets text from the user.",
		this,
		&webServicesManager::setText);

	// Start the server.
	server.start();

	// Launch a browser with the address of the server.
	ofLaunchBrowser(server.getURL());
}

void webServicesManager::draw()
{
	ofDrawBitmapStringHighlight(userText, ofPoint(14, 18));
}



//--------------------------------------------
void webServicesManager::doPost(string _quest, dataToken _tokensYes, dataToken _tokensNo)
{
}

//--------------------------------------------
void webServicesManager::doRead(int _id)
{
}

//--------------------------------------------
void webServicesManager::doPatch(string _quest, int _id, dataToken _tokensYes, dataToken _tokensNo)
{
}

//--------------------------------------------
void webServicesManager::doDelete(int _id)
{
}



void webServicesManager::getQuestions(ofx::JSONRPC::MethodArgs& args)
{
	// Set the result equal to the substring.
	args.result = getMyQuestions();
	//args.params = getMyQuestions();
	cout << "This is going to give back our questions" << endl;
	//cout << args.result << endl;
	ofLogVerbose("webServicesManager::getText") << args.result;//.asString()
}


void webServicesManager::setText(ofx::JSONRPC::MethodArgs& args)
{
	cout << "All args to setText are" << args.params << endl;
	for (int i = 0; i < args.params.size(); i++) {
		cout << "Arg[" + ofToString(i, 0) + "]=" << args.params[i] << endl;
	}

	//1rs Add Question to vector
	QuestionRestFul myAuxQuest;
	
	if (args.params.size() == 2) {
		myAuxQuest.theQuestion.id = ofToInt(args.params[0].asString());
		myAuxQuest.theQuestion.question = args.params[1].asString();
		//myAuxQuest.question.answer = ofToInt(args.params[2].asString()); //Do not crash if there is nothing. That's good.
		myQuestions.push_back(myAuxQuest);
	}
	//TODO Later update it into mySql item


	// Set the user text.
	setUserText(args.params.asString());
	ofLogVerbose("webServicesManager::setText") << args.params.asString();
}


ofxJSONElement webServicesManager::getMyQuestions()
{

	ofxJSONElement thatSavedQuestions;

	for (int i = 0; i < myQuestions.size(); i++) {
		thatSavedQuestions[i]["id"] = ofToString(myQuestions[i].theQuestion.id, 0);
		thatSavedQuestions[i]["question"] = myQuestions[i].theQuestion.question;
	}

	return thatSavedQuestions;

	//static const std::size_t LENGTH = 140;

	//std::unique_lock<std::mutex> lock(mutex);

	//// Generate a random start index.
	//std::size_t startIndex = (std::size_t)ofRandom(ipsum.length());

	//// Ensure that the length is valid.
	//std::size_t length = (startIndex + LENGTH) < ipsum.length() ? LENGTH : string::npos;

	//// return the result equal to the substring.
	//return ipsum.substr(startIndex, length);


}


std::string webServicesManager::getUserText() const
{
	std::unique_lock<std::mutex> lock(mutex);
	return userText;
}


void webServicesManager::setUserText(const std::string& text)
{
	std::unique_lock<std::mutex> lock(mutex);
	userText = text;
}
