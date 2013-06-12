//#include "StdAfx.h"
#include "math.h" // 包含log函数的定义
#include "MPWordSeg.h"

// 以下是最大概率法分词程序

CMPWordSeg::CMPWordSeg()
{}
CMPWordSeg::~CMPWordSeg()
{}

int CMPWordSeg::Initial(string strFileName)
{
	m_oDict.Initial(strFileName);
	return 0;
}
int CMPWordSeg::Uninitial()
{
	return 0;
}
short CMPWordSeg::getTmpWords(string &s)
{ // 从输入串中挑选可能是词的单位作为最大概率法分词的候选词
	short i=0;
	short j=0;
	short len=0;
	short restlen=0;
	short n=s.length();
	float freq=0;
	string w;

	for(j=0;j<n;j+=1) 
	{
		for(len=1;len<=MaxWordLength;len+=1) 
		{
			restlen=n-j; 
			if (len<=restlen) // 如果剩余词长度不够长，跳出循环
			{
				w=s.substr(j,len);
			}
			else
			{
				break;
			}

			freq=m_oDict.GetFreq(w); // 如果在数据库中将wfreq字段设为双精度型数字，则返回0值
			//cout<<"word"<<w<<" freq "<<freq<<endl;
			if(len>1 && freq==100)
			{
				continue;
			}
			if(freq==100) 
			{
				freq=-100;//cost max
			}
			Candidates[i].offset=j;
			Candidates[i].length=len;
			//Candidates[i].fee = (float)(-log((double)(freq+1)/CorpusSize));
			Candidates[i].fee = -freq;
			Candidates[i].sumFee=0.0F;// 置初值
			i++;
		}
	}
	return i;
}

void CMPWordSeg::getPrev(short i)
{ // 计算每一个候选词的最佳前趋词，以及当前词的最小累计费用
	if(Candidates[i].offset==0) 
	{
		Candidates[i].goodPrev=-1;
		Candidates[i].sumFee=Candidates[i].fee;
		return;
	}
	
	short j,minID=-1;
	
	for(j=i-1;j>=0;j--) 
	{ //向左查找所有候选词，得到前驱词集合，从中挑选最佳前趋词
		if(Candidates[j].offset+Candidates[j].length==Candidates[i].offset) 
		{
			if(minID==-1 || Candidates[j].sumFee<=Candidates[minID].sumFee)
				minID=j;
		}
		if(Candidates[i].offset-Candidates[j].offset>=MaxWordLength) // 向左查找候选词最远不超过4个汉字
		{
			break;
		}
	}
	
	Candidates[i].goodPrev=minID;
	Candidates[i].sumFee=Candidates[i].fee+Candidates[minID].sumFee;
	return;
}

string CMPWordSeg::SegmentHzStrMP(string s1)
{//最大概率法分词程序，处理一个字符串
	int len=s1.length();
	short n=getTmpWords(s1);
	short minID=-1;
	short i;

	for(i=0;i<n;i++) 
	{
		getPrev(i);
		if(Candidates[i].offset+Candidates[i].length==len) 
		{ // 如果当前词是s1中最后一个可能的候选词
			if(minID==-1||Candidates[i].sumFee<Candidates[minID].sumFee) // 如果这个末尾候选词的累计费用最小
			{
				minID=i; // 把当前词的序号赋给minID，这就是最小费用路径的终点词的序号
						 // 这就是最后分词结果最右边的那个词的序号
			}
		}
	}

	string s2=""; // s2是输出结果
	for(i=minID;i>=0;i=Candidates[i].goodPrev) // 从右向左取词候选词
	{
		s2=s1.substr(Candidates[i].offset,Candidates[i].length)+Separator+s2; 
	}

	return s2;
}
