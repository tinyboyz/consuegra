#pragma once

#include <string>
using namespace std;

#pragma pack(1)

typedef struct _tagApplicant
{
	char szName[32];
	char szPhone[32];
	char szEmail[64];
	char szDate[32];
	char szPosition[64];
} Applicant;

#pragma pack()


class CAnalyzeCV
{
public:
	CAnalyzeCV(void);
	virtual ~CAnalyzeCV(void);

	bool Analyze(string path, Applicant *pApplicant, unsigned short &usAppNum);
};
