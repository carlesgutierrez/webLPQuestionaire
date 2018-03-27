#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "QuestionRestFul.h"
#include "SQLiteCpp.h"


class DbQuestions
{
public:
	DbQuestions();
	~DbQuestions();
	void setup();
	void setupDB(string filedataBase, string mainTable, string tokenYesTable, string tokenNoTable);
	void insertQuestionData(QuestionRestFul myAuxQuest);
	bool updateQuestionData(QuestionRestFul myAuxQuest);
	bool deleteQuestionData(QuestionRestFul myAuxQuest);
	ofxJSONElement getMyQuestionsDataJsonFormat();

public: 


	string dbCreateQuestionTable = "CREATE TABLE question(id INTEGER PRIMARY KEY, value TEXT, idTokenYes INTEGER, idTokenNo INTEGER)";
	string dbCreateTokenYesTable = "CREATE TABLE tokensYes(id INTEGER PRIMARY KEY, param1 INTEGER, param2 INTEGER, param3 INTEGER, param4 INTEGER, param5 INTEGER)";
	string dbCreateTokenNoTable = "CREATE TABLE tokensNo(id INTEGER PRIMARY KEY, param1 INTEGER, param2 INTEGER, param3 INTEGER, param4 INTEGER, param5 INTEGER)";
	//CREATE TABLE `tokensNo` ( `id` INTEGER, `param1` INTEGER, `param2` INTEGER, `param3` INTEGER, `param4` INTEGER, `param5` INTEGER, PRIMARY KEY(`id`) )
};

