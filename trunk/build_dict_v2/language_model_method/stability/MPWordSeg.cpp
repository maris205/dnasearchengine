//#include "StdAfx.h"
#include "math.h" // ����log�����Ķ���
#include "MPWordSeg.h"

// �����������ʷ��ִʳ���

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
{ // �����봮����ѡ�����Ǵʵĵ�λ��Ϊ�����ʷ��ִʵĺ�ѡ��
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
			if (len<=restlen) // ���ʣ��ʳ��Ȳ�����������ѭ��
			{
				w=s.substr(j,len);
			}
			else
			{
				break;
			}

			freq=m_oDict.GetFreq(w); // ��������ݿ��н�wfreq�ֶ���Ϊ˫���������֣��򷵻�0ֵ
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
			Candidates[i].sumFee=0.0F;// �ó�ֵ
			i++;
		}
	}
	return i;
}

void CMPWordSeg::getPrev(short i)
{ // ����ÿһ����ѡ�ʵ����ǰ���ʣ��Լ���ǰ�ʵ���С�ۼƷ���
	if(Candidates[i].offset==0) 
	{
		Candidates[i].goodPrev=-1;
		Candidates[i].sumFee=Candidates[i].fee;
		return;
	}
	
	short j,minID=-1;
	
	for(j=i-1;j>=0;j--) 
	{ //����������к�ѡ�ʣ��õ�ǰ���ʼ��ϣ�������ѡ���ǰ����
		if(Candidates[j].offset+Candidates[j].length==Candidates[i].offset) 
		{
			if(minID==-1 || Candidates[j].sumFee<=Candidates[minID].sumFee)
				minID=j;
		}
		if(Candidates[i].offset-Candidates[j].offset>=MaxWordLength) // ������Һ�ѡ����Զ������4������
		{
			break;
		}
	}
	
	Candidates[i].goodPrev=minID;
	Candidates[i].sumFee=Candidates[i].fee+Candidates[minID].sumFee;
	return;
}

string CMPWordSeg::SegmentHzStrMP(string s1)
{//�����ʷ��ִʳ��򣬴���һ���ַ���
	int len=s1.length();
	short n=getTmpWords(s1);
	short minID=-1;
	short i;

	for(i=0;i<n;i++) 
	{
		getPrev(i);
		if(Candidates[i].offset+Candidates[i].length==len) 
		{ // �����ǰ����s1�����һ�����ܵĺ�ѡ��
			if(minID==-1||Candidates[i].sumFee<Candidates[minID].sumFee) // ������ĩβ��ѡ�ʵ��ۼƷ�����С
			{
				minID=i; // �ѵ�ǰ�ʵ���Ÿ���minID���������С����·�����յ�ʵ����
						 // ��������ִʽ�����ұߵ��Ǹ��ʵ����
			}
		}
	}

	string s2=""; // s2��������
	for(i=minID;i>=0;i=Candidates[i].goodPrev) // ��������ȡ�ʺ�ѡ��
	{
		s2=s1.substr(Candidates[i].offset,Candidates[i].length)+Separator+s2; 
	}

	return s2;
}
