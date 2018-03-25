#include "QuestionRestFul.h"


//--------------------------------------------
QuestionRestFul::QuestionRestFul()
{
	//Creating model that tokens user interaction will use dinamically
	string incomeTaxValue;
	string publicHealthValue;
	string entrepreneurshipValue;
	string immigrationValue;

	incomeTaxValue = ofToString(0, 0);
	publicHealthValue = ofToString(0, 0);
	entrepreneurshipValue = ofToString(0, 0);
	immigrationValue = ofToString(0, 0);

	string dataTokenDefault =
		"{\"incomeTax\":" + incomeTaxValue +
		", \"publicHealth\" : " + publicHealthValue +
		", \"entrepreneurship\" : " + entrepreneurshipValue +
		", \"immigration\" : " + immigrationValue + " }";
	theQuestion.dataTokenYes.parse(dataTokenDefault);
	theQuestion.dataTokenNo.parse(dataTokenDefault);
}

//--------------------------------------------
QuestionRestFul::~QuestionRestFul()
{
}

//--------------------------------------------
void QuestionRestFul::setup()
{
	simulateTokensValues();
}


//--------------------------------------------
void QuestionRestFul::draw()
{

}



//--------------------------------------------
void QuestionRestFul::simulateTokensValues()
{
	////Creating model that tokens user interaction will use dinamically
	//string incomeTaxValue;
	//string publicHealthValue;
	//string entrepreneurshipValue;
	//string immigrationValue;

	int incomeTaxValue;
	int immigrationValue;
	int entrepreneurshipValue;
	int publicHealthValue;

	incomeTaxValue = (int)ofRandom(-5, 5);
	publicHealthValue = (int)ofRandom(-5, 5);
	entrepreneurshipValue = (int)ofRandom(-5, 5);
	immigrationValue = (int)ofRandom(-5, 5);

	theQuestion.dataTokenYes["incomeTax"] = incomeTaxValue;
	theQuestion.dataTokenYes["publicHealth"] = publicHealthValue;
	theQuestion.dataTokenYes["entrepreneurship"] = entrepreneurshipValue;
	theQuestion.dataTokenYes["immigration"] = immigrationValue;

	cout << theQuestion.dataTokenYes << endl;


	incomeTaxValue = (int)ofRandom(-5, 5);
	publicHealthValue = (int)ofRandom(-5, 5);
	entrepreneurshipValue = (int)ofRandom(-5, 5);
	immigrationValue = (int)ofRandom(-5, 5);

	theQuestion.dataTokenNo["incomeTax"] = incomeTaxValue;
	theQuestion.dataTokenNo["publicHealth"] = publicHealthValue;
	theQuestion.dataTokenNo["entrepreneurship"] = entrepreneurshipValue;
	theQuestion.dataTokenNo["immigration"] = immigrationValue;

	cout << theQuestion.dataTokenNo << endl;
	//string dataTokenYes_text =
	//	"{\"incomeTax\":" + incomeTaxValue +
	//	", \"publicHealth\" : " + publicHealthValue +
	//	", \"entrepreneurship\" : " + entrepreneurshipValue +
	//	", \"immigration\" : " + immigrationValue + " }";
	//theQuestion.dataTokenYes.parse(dataTokenYes_text);

	//incomeTaxValue = ofToString((int)ofRandom(-5, 5), 0);
	//publicHealthValue = ofToString((int)ofRandom(-5, 5), 0);
	//entrepreneurshipValue = ofToString((int)ofRandom(-5, 5), 0);
	//immigrationValue = ofToString((int)ofRandom(-5, 5), 0);

	//string dataTokenNo_text =
	//	"{\"incomeTax\":" + incomeTaxValue +
	//	", \"publicHealth\" : " + publicHealthValue +
	//	", \"entrepreneurship\" : " + entrepreneurshipValue +
	//	", \"immigration\" : " + immigrationValue + " }";	theQuestion.dataTokenNo.parse(dataTokenNo_text);

	//cout << "Default Tokens at Question Constructor" << endl;
	//cout << theQuestion.dataTokenNo << endl;
}



