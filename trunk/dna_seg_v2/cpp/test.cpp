//max probility segment algorithm test

#include "dna_segment.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	string dict_file_name = "dict.txt";
	DNASegment my_seg;
	my_seg.InitialDict(dict_file_name);
	string sequence = "CCCTAAACCCTAAACCCTAAACCTCTGAATCCTTAATCCCTAAATCCCTAAATCTTTAAATCCTACATC";
	cout<<"original sequence: " <<sequence<<endl;
    cout<<"segment result: "<<my_seg.MpSeg(sequence)<<endl;

	return 0;
}

