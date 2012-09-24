#include "AnalyzeCV.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ExcelFormat.h"
#include "RexInterface.h"

using namespace std;
using namespace ExcelFormat;



#define MAX_APPLICANT	256				// maximum applicant number


CAnalyzeCV::CAnalyzeCV(void)
{
}


CAnalyzeCV::~CAnalyzeCV(void)
{
}


bool CAnalyzeCV::Analyze(string path, Applicant *pApplicant, unsigned short &usAppNum)
{
	ifstream ifs(path.c_str(),ios::binary);
	if (!ifs.is_open())
	{
		cerr << path << " can not open!" << endl;
		return false;
	}

	// get length of file:
	ifs.seekg (0, std::ios::end);
	long length = ifs.tellg();
	ifs.seekg (0, std::ios::beg);

	// allocate memory:
	char *pBuffer = (char *)malloc(length);
	if (!pBuffer)
	{
		return false;
	}

	// read data as a block:
	ifs.read(pBuffer,length);

	const int ncOk= REXI_DefErr::eNoErr;
	REXI_Search rexs; 
	REXI_DefErr err;
	bool bEosFound= false;
	int nMatchLen = 0;
	const char *pHead;
	const char *pCur;

	// search name

	// search phone
	err= rexs.SetRegexp("(13[0-9]|15[0|3|6|7|8|9]|18[8|9])[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]"); assert(err.eErrCode==ncOk);
	pHead = pCur = pBuffer;
	if (rexs.Find(pCur,nMatchLen,bEosFound))
	{
		strncpy(pApplicant[usAppNum].szPhone, pBuffer + (((pCur-pHead)-nMatchLen)), nMatchLen);
		cout << pApplicant[usAppNum].szPhone << endl;
	}

	// search email
	bEosFound= false;
	nMatchLen = 0;
	err= rexs.SetRegexp("[a-zA-Z0-9_\.]+@[a-zA-Z0-9-]+[\.a-zA-Z]+"); assert(err.eErrCode==ncOk);
	pHead = pCur = pBuffer;
	if (rexs.Find(pCur,nMatchLen,bEosFound))
	{
		strncpy(pApplicant[usAppNum].szEmail, pBuffer + (((pCur-pHead)-nMatchLen)), nMatchLen);
		cout << pApplicant[usAppNum].szEmail << endl;
	}

	if (pBuffer)
	{
		free(pBuffer);
		pBuffer = NULL;
	}

	usAppNum++;

	return true;
}