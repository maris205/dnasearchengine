#ifndef DNA_SEGMENT_H
#define DNA_SEGMENT_H
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits.h>
using namespace std;

const string DELIMITER = "/ ";
const int MAX_WORD_LENGTH = 12;
const int LETTER_LENGTH = 1;

class DNASegment
{
public:
    DNASegment(void);
    ~DNASegment(void);
    int InitialDict(const string & dict_file_name);
    string MpSeg(const string & sequence);
private:
    map <string, float> m_word_dict;
};
#endif // DNA_SEGMENT_H
