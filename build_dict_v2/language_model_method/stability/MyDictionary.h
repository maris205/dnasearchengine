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
	CMyDictionary(); // 构造函数
	~CMyDictionary();//// 构析函数
	int Initial(string strFileName);//初始化
	int Uninitial();//卸载
	float GetFreq(string w);	// 成员函数：获取词语的频度值
private:
	map <string,float> m_mapWord2Prob;
};