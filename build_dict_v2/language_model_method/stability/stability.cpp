// stability.cpp 
//get the problity of segmentation
/****************************************
input
output
********************************************/
//#include "stdafx.h"
#include "MPWordSeg.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;


//split string
vector<string> SplitString(const std::string &str, const char *separator)
{
    vector<string> result;
    string::size_type prev_pos=0;
    string::size_type pos=0;
    while ((pos = str.find(separator, prev_pos)) != string::npos)
    {
            if (prev_pos < pos) 
            {
                    result.push_back(str.substr(prev_pos, pos-prev_pos));
            }
            prev_pos = pos + strlen(separator);
    }
    if (prev_pos < str.size()) 
    {
        result.push_back(str.substr(prev_pos));
    }
    return result;
}

int GetStability(string & strText,CMPWordSeg & oMySeg,float & fAverageStability)
{
    fAverageStability=0;

	int nMaxLength=9;  //reduce the first letter successively,total reduce 9 letter 
	string strSeparator="/  ";

	string strSubText="";
    string strSegment="";

	int nIdx=0;
    int nSegPos=0;
    int nLeftSegPos=0;
    int nSamePosNum=0;
    float fStability=0;    

	vector <string> vectSeg;
	vector <string>::iterator itVect;

	vector <int> vectOriSeg;//store the segment positon
    vector <int>::iterator itIntVect;
    
    strSegment=oMySeg.SegmentHzStrMP(strText);
    //cout<<strSegment<<endl; 
	vectSeg=SplitString(strSegment,strSeparator.c_str());
	nSegPos=-1;
	for(itVect=vectSeg.begin();itVect!=vectSeg.end();itVect++)
	{
		nSegPos=nSegPos+(*itVect).length();
		vectOriSeg.push_back(nSegPos);
		//cout<<nSegPos<<" ";
	}
   // cout<<endl;
        
    for (nIdx=1;nIdx<nMaxLength;nIdx++)
     //for (nIdx=1;nIdx<2;nIdx++) 
	{
		strSubText=strText.substr(nIdx);
        strSegment=oMySeg.SegmentHzStrMP(strSubText);
		//cout<<strSegment<<endl;

		vectSeg.clear();
		nSegPos=nIdx-1;
		vectSeg=SplitString(strSegment,strSeparator.c_str());
        nSamePosNum=0;
        
		for(itVect=vectSeg.begin();itVect!=vectSeg.end();itVect++)
		{
			nSegPos=nSegPos+(*itVect).length();
            if(find(vectOriSeg.begin(),vectOriSeg.end(),nSegPos) != vectOriSeg.end())
            {
                if (itVect!=vectSeg.begin())
                {
                    if (find(vectOriSeg.begin(),vectOriSeg.end(),nLeftSegPos) != vectOriSeg.end())
                    {
                        //the front segmentation should also same
                        nSamePosNum++;
                    }
                }    
            }
            nLeftSegPos=nSegPos;
			//cout<<nSegPos<<" ";
		}
		//cout<<endl;

        //caculate the same percentage
        fStability=(float)nSamePosNum/(vectSeg.size()-1);//-1 is not consider the first words
        fAverageStability=fAverageStability+fStability;
        //cout<<"stability "<<fStability<<endl;
    }

    fAverageStability=fAverageStability/(nMaxLength-1);
	return 0;
}
int main(int argc, char* argv[])
{
	if (3 != argc )
	{
		cout<<"please input dict file and test data filename"<<endl;
		exit(0);
	}

	char * szDataFile=argv[2];
	string strDictFileName=argv[1];
	CMPWordSeg oMySeg;
	oMySeg.Initial(strDictFileName);//initial segmentation
	string strText="";
	strText="CCCTAAACCCTAAACCCTAAACCTCTGAATCCTTAATCCCTAAATCCCTAAATCTTTAAATCCTACATC";
	float fAverageStability=0;
	
	ifstream inInDataFile(szDataFile);

	while(getline(inInDataFile,strText))
	{
        fAverageStability=0;
		GetStability(strText,oMySeg,fAverageStability);
	    cout<<fAverageStability<<endl;
	}
	//printf("Hello World!\n");
	return 0;
}
