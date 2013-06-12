#include <string>
#include <iostream>
#include <fstream>
#include "MyDictionary.h"
using namespace std;

const string Separator="/  "; // �ʽ���
const int MaxWordLength=9;// ���ʳ�Ϊ8���ֽڣ���4�����֣�
 
class CMPWordSeg
{
public:
	CMPWordSeg(); // ���캯��
	~CMPWordSeg();//// ��������
	int Initial(string strFileName);//��ʼ��
	int Uninitial();//ж��

	string SegmentHzStrMP(string s1); // �����ʷ��ִʺ���

private:
	struct Candidate 
	{
	short offset, length;  // ��ѡ�������봮�е���㣬����
	short goodPrev;  // ���ǰ���ʵ����
	float fee, sumFee; // ��ѡ�ʵķ��ã�·���ϵ��ۼƷ���
	} Candidates[1000];// �ٶ����1000����ѡ��

	CMyDictionary m_oDict;//
	short getTmpWords(string &s); // ��ȡ���к�ѡ�ʵĺ����������ʷ��ִʳ������
	void getPrev(short i); // �����ѡ�ʵ����ǰ���ʵĺ���
};
