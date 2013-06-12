//max probility segment algorithm test

//#include "stdafx.h"
#include "MPWordSeg.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	string strFileName="dict.txt";
	CMPWordSeg oMySeg;
	oMySeg.Initial(strFileName);
	string strText="CCCTAAACCCTAAACCCTAAACCTCTGAATCCTTAATCCCTAAATCCCTAAATCTTTAAATCCTACATC";
	cout<<"original sequence: " <<strText<<endl;
    cout<<"segment result: "<<oMySeg.SegmentHzStrMP(strText)<<endl;

	return 0;
}

