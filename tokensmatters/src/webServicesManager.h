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

	//will return id question created
	void doPost(ofx::JSONRPC::MethodArgs & args);

	//get
	void doGet(ofx::JSONRPC::MethodArgs & args);
	
	//update
	void doPatch(ofx::JSONRPC::MethodArgs & args);

	//remove
	void doDelete(ofx::JSONRPC::MethodArgs & args);

	//only for develop
	vector<QuestionRestFul> myQuestions;

private:


	// Registered methods.
	void updateQuestionId(ofx::JSONRPC::MethodArgs & args);
	bool updateQuestionData(int auxIdQuestion, string newQuestion);
	bool deleteQuestionData(int auxIdQuestion);
	void getQuestions(ofx::JSONRPC::MethodArgs& args);

	/// \brief The server that handles the JSONRPC requests.
	ofx::HTTP::JSONRPCServer server;

	/// \brief Get a snippet of random text in a thread-safe way.
	/// \returns The snippet of random text.
	ofxJSONElement getMyQuestionsData();

	DbQuestions myDB;
	bool bVectorDataBaseMode = true;

private:
	// A custom logging channel to mirror all log messages to the web clients.
	// WebSocketLoggerChannel::SharedPtr loggerChannel;

	// This piece of text might be modified by multiple client threads.
	// Thus we must use a mutex to protect it during multi-threaded access.
	std::string ipsum;

	// This piece of text might be modified by multiple client threads.
	// Thus we must use a mutex to protect it during multi-threaded access.
	std::string userText;

	// We use a mutex to protect any variables that can be
	// modified by multiple clients.  In our case, userText must be protected.
	// We mark the mutex as mutable so that it can be used in const functions.
	mutable std::mutex mutex;

};

