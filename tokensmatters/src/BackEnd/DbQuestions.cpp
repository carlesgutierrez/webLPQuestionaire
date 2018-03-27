#include "DbQuestions.h"

//--------------------------------------------
DbQuestions::DbQuestions(){
	
}

//--------------------------------------------
DbQuestions::~DbQuestions()
{
}

//--------------------------------------------
void DbQuestions::setup(){


}

//---------------------------------------------
void DbQuestions::setupDB(string dataBaseName, string mainTable, string tokenYesTable, string tokenNoTable) {
	try
	{
		//SQL stuff
		//SQLite::Statement mQuery; ///< Database prepared SQL query
		SQLite::Database db(dataBaseName);

		// Test if the 'question' table exists
		bool mainTableExists = db.tableExists(mainTable);

		if (mainTableExists)
		{
			ofLogNotice() << "Main table did exist!";
		}
		else
		{
			ofLogNotice() << "Main table question did NOT exist! Then we create it";
			db.exec(dbCreateQuestionTable);
			//CREATE TABLE "question" (`id` INTEGER, `value` TEXT, `idTokenYes` INTEGER, `idTokenNo` INTEGER, PRIMARY KEY(`id`))
		}

		//token*Yes*Table
		bool tokenYesTableExists = db.tableExists(tokenYesTable);

		if (mainTableExists)
		{
			ofLogNotice() << "tokenYesTable did exist!";
		}
		else
		{
			ofLogNotice() << "tokenYesTable did NOT exist!";
			db.exec(dbCreateTokenYesTable);
		}

		//token*No*Table
		bool tokenNoTableExists = db.tableExists(tokenNoTable);

		if (mainTableExists)
		{
			ofLogNotice() << "tokenNoTable did exist!";
		}
		else
		{
			ofLogNotice() << "tokenNoTable did NOT exist!";
			db.exec(dbCreateTokenNoTable);
		}

	}
	catch (std::exception& e)
	{
		ofLogError() << "SQLite exception: " << e.what();
	}
}



//--------------------------------------------
void DbQuestions::insertQuestionData(QuestionRestFul myAuxQuest)
{

	string myQuestion2Add = myAuxQuest.theQuestion.question;

	/// Example Database
	std::string exampleDB = ofToDataPath("tokensmatters.sqlite", true);

	try
	{
		// Open a database file in create/write mode
		SQLite::Database db(exampleDB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

		ofLogNotice() << "SQLite database file '" << db.getFilename() << "' opened successfully";

		//db.exec("DROP TABLE IF EXISTS test");
		//db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

		// first row
		int nb = db.exec("INSERT INTO question VALUES (NULL, \"+myQuestion2Add+\")");
		ofLogNotice() << "SELECT * FROM question :";
	}
	catch (std::exception& e)
	{
		ofLogError() << "SQLite exception: " << e.what();
	}

	//TODO check how to manage this with MySql to save all
		
	//update it into mySql item
	//int nb = db.exec("INSERT INTO question VALUES (NULL, \"test\")");
	
	//ofLogVerbose("DbQuestions::doPost") << args.params.asString();
}

//------------------------------------------------------
bool DbQuestions::updateQuestionData(QuestionRestFul myAuxQuest) {

	int auxIdQuestion = myAuxQuest.theQuestion.id;
	string newQuestion = myAuxQuest.theQuestion.question;
	bool bFoundQuestion = false;

	//if (bVectorDataBaseMode) {
	//	for (int i = 0; i < myQuestions.size(); i++) {
	//		if (myQuestions[i].theQuestion.id == auxIdQuestion) {
	//			bFoundQuestion = true;
	//			myQuestions[i].theQuestion.question = newQuestion;
	//		}
	//	}
	//}
	//else {
	//	//todo
	//}
	return bFoundQuestion;
}

//------------------------------------------------------
bool DbQuestions::deleteQuestionData(QuestionRestFul myAuxQuest) {
	bool bFoundQuestion = false;
	int auxIdQuestion = myAuxQuest.theQuestion.id;
	//if (bVectorDataBaseMode) {
	//	for (int i = 0; i < myQuestions.size(); i++) {
	//		if (myQuestions[i].theQuestion.id == auxIdQuestion) {
	//			bFoundQuestion = true;
	//			myQuestions.erase(myQuestions.begin() + i);
	//		}
	//	}
	//}
	//else {
	//	//Db TodO
	//}

	return bFoundQuestion;
}


//------------------------------------------------------
ofxJSONElement DbQuestions::getMyQuestionsDataJsonFormat()
{

	ofxJSONElement thatSavedQuestions;

	//if (bVectorDataBaseMode) {
	//	for (int i = 0; i < myQuestions.size(); i++) {
	//		thatSavedQuestions[i]["id"] = ofToString(myQuestions[i].theQuestion.id, 0);
	//		thatSavedQuestions[i]["question"] = myQuestions[i].theQuestion.question;
	//	}
	//}
	//else {
	//	//TODO DB Sqlite
	//}
	return thatSavedQuestions;
}

