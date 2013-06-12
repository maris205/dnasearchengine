#include <string>
#include <iostream>
#include <fstream>
#include "MyDictionary.h"
using namespace std;

const string Separator="/  "; // 词界标记
const int MaxWordLength=9;// 最大词长为8个字节（即4个汉字）
 
class CMPWordSeg
{
public:
	CMPWordSeg(); // 构造函数
	~CMPWordSeg();//// 构析函数
	int Initial(string strFileName);//初始化
	int Uninitial();//卸载

	string SegmentHzStrMP(string s1); // 最大概率法分词函数

private:
	struct Candidate 
	{
	short offset, length;  // 候选词在输入串中的起点，长度
	short goodPrev;  // 最佳前趋词的序号
	float fee, sumFee; // 候选词的费用，路径上的累计费用
	} Candidates[1000];// 假定最多1000个候选词

	CMyDictionary m_oDict;//
	short getTmpWords(string &s); // 获取所有候选词的函数，最大概率法分词程序调用
	void getPrev(short i); // 计算候选词的最佳前趋词的函数
};
