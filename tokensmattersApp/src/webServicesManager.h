#pragma once

#include "ofMain.h"
#include "QuestionRestFul.h"
#include "ofxJSONRPC.h"
#include "ofxJSON.h"


class webServicesManager
{
public:
	webServicesManager();
	~webServicesManager();
	void setup();
	void update();
	void draw();
public: 

	vector<QuestionRestFul> myQuestions;

	// Registered methods.
	void getQuestions(ofx::JSONRPC::MethodArgs& args);
	void setText(ofx::JSONRPC::MethodArgs& args);

	/// \brief The server that handles the JSONRPC requests.
	ofx::HTTP::JSONRPCServer server;

	/// \brief Get a snippet of random text in a thread-safe way.
	/// \returns The snippet of random text.
	ofxJSONElement getMyQuestions();

	/// \brief Get the user text in a thread-safe way.
	/// \returns The user text.
	std::string getUserText() const;

	/// \brief Set the user text in a thread-safe way.
	/// \param text the user text to set.
	void setUserText(const std::string& text);

public: 

	//will return id question created
	void doPost(string _quest, dataToken _tokensYes, dataToken _tokensNo);

	//will return dataQuestion
	void doRead(int _id);
	
	//Will return Boolean
	void doPatch(string _quest, int _id, dataToken _tokensYes, dataToken _tokensNo);//update 

	//Will return Boolean
	void doDelete(int _id);

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

