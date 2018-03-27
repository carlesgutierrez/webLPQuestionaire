#pragma once

#include "ofMain.h"
#include "QuestionRestFul.h"
#include "ofxJSONRPC.h"
#include "ofxJSON.h"

#include "SQLiteCpp.h"
#include "DbQuestions.h"


class webServicesManager
{
public:
	webServicesManager();
	~webServicesManager();
	void setup();
	void update();
	void draw();

public: 

	//Add question new
	void doPost(ofx::JSONRPC::MethodArgs & args);

	//get All questions saved
	void doGet(ofx::JSONRPC::MethodArgs & args);
	
	//update an specific question
	void doPatch(ofx::JSONRPC::MethodArgs & args);

	//remove an specific question
	void doDelete(ofx::JSONRPC::MethodArgs & args);

	// myQuestions would not be neceary if we use slite db.
	// This piece of text might be modified by multiple client threads.
	// Thus we must use a mutex to protect it during multi-threaded access.
	vector<QuestionRestFul> myQuestions;

private:

	//internal fucntions
	bool updateQuestionData(int auxIdQuestion, string newQuestion);
	bool deleteQuestionData(int auxIdQuestion);
	ofxJSONElement getMyQuestionsData();

	/// \brief The server that handles the JSONRPC requests.
	ofx::HTTP::JSONRPCServer server;

	DbQuestions myDB;
	bool bVectorDataBaseMode = true;//set false to use Sqlite ( WIP )

private:

	// We use a mutex to protect any variables that can be
	// modified by multiple clients.  In our case, userText must be protected.
	// We mark the mutex as mutable so that it can be used in const functions.
	mutable std::mutex mutex;

};

