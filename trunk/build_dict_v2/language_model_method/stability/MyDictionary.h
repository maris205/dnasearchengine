#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class CMyDictionary
{
public:
	CMyDictionary(); // ���캯��
	~CMyDictionary();//// ��������
	int Initial(string strFileName);//��ʼ��
	int Uninitial();//ж��
	float GetFreq(string w);	// ��Ա��������ȡ�����Ƶ��ֵ
private:
	map <string,float> m_mapWord2Prob;
};