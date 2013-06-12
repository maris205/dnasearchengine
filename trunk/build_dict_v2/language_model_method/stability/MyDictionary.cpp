//#include "StdAfx.h"
#include "MyDictionary.h"

// # define MaxWordLength 8  // ���ʳ�Ϊ8���ֽڣ���4�����֣�
//extern int MaxWordLength; // ���ʳ����û���.ini�ļ���ָ��
CMyDictionary::CMyDictionary() // ���캯��
{
}
CMyDictionary::~CMyDictionary()//// ��������
{
}
int CMyDictionary::Uninitial()
{
	return 0;
}
int CMyDictionary::Initial(string strFileName)
{
	ifstream ifInFile(strFileName.c_str());
	if (!ifInFile)
	{
		cout<<"file open error!"<<endl;
		return -1;
	}
	string strLine="";
	string strWord="";
	string strProb="";
	float fProb=0;
    int nTabPos=0;
	while(getline(ifInFile,strLine))
	{
        if ((nTabPos=strLine.find("\t")) != string::npos)
        {
            strWord=strLine.substr(0,nTabPos);
            strProb=strLine.substr(nTabPos+1);
		    fProb=atof(strProb.c_str());
		    m_mapWord2Prob[strWord]=fProb;
		   // cout<<"word"<<strWord<<" prob "<<m_mapWord2Prob[strWord]<<endl;
        }
        else
        {
            cout<<"dict file read error"<<endl;
            return -2;
        }
	}
	ifInFile.close();
	return 0;
}

float CMyDictionary::GetFreq(string strWord)
{
	if(m_mapWord2Prob.find(strWord)!=m_mapWord2Prob.end())
	{
		return m_mapWord2Prob[strWord];
	}
	else
	{
		return 100;
	}
}
