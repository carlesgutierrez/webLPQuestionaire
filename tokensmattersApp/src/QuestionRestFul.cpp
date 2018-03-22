#include "QuestionRestFul.h"


//--------------------------------------------
QuestionRestFul::QuestionRestFul()
{
	string dataTokenBase_text = "{\"incomeTax\":0, \"publicHealth\" : 0, \"entrepreneurship\" : 0, \"immigration\" : 0 }";
	theQuestion.dataTokenYes.parse(dataTokenBase_text);
	theQuestion.dataTokenNo.parse(dataTokenBase_text);
	cout << "QuestionRestFul Constructor" << endl;
	cout << theQuestion.dataTokenNo << endl;
}

//--------------------------------------------
QuestionRestFul::~QuestionRestFul()
{
}

void QuestionRestFul::setup()
{
}




