#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;
map <string,double> word_dict;
map <string,double> word_dict_new;
const int MAX_WORD_LENGTH = 12;
const int LETTER_LENGTH = 1;

vector<string> SplitString(const string & str, const char* seperator)
{
    vector<string> result;
    string::size_type prev_pos=0;
    string::size_type pos=0;
    while ((pos = str.find(seperator, prev_pos)) != string::npos)
    {
        if (prev_pos < pos)
        {
            result.push_back(str.substr(prev_pos, pos-prev_pos));
        }
        prev_pos = pos + strlen(seperator);
    }
    if (prev_pos < str.size())
    {
      result.push_back(str.substr(prev_pos));
    }
    return result;
}

void PrintVector(vector<double> & vectSum)
{
    vector <double>::iterator vectIt;
    for (vectIt=vectSum.begin();vectIt!=vectSum.end();vectIt++)
    {
        cout<<*vectIt<<endl;
    }
}
void PrintMap(map<string,double> & map_dict_new)
{
    map <string,double>::iterator mapIt;
    for(mapIt=map_dict_new.begin();mapIt!=map_dict_new.end();mapIt++)
    {
        cout<<mapIt->first<<"\t"<<mapIt->second<<endl;
    }
}

int GetProb(string & strLine)
{
    vector <double> s_left;
    vector <double> s_right;
    int nLength = strLine.length();
    int nPos = 0;
    int nIdex = 0;
    string strWord = "";
    int nWordLength = 0;
    int nMaxWordLength = 0;
    double fProb = 0;
    double fIncrease = 0;
    // map <string,float> word_dict_new;

    //get s_left
    for (nPos=0;nPos<nLength+LETTER_LENGTH;nPos=nPos+LETTER_LENGTH)
    {
        if ( 0 == nPos )
        {
            s_left.push_back(1);
            continue;
        }

        if ( nPos < MAX_WORD_LENGTH )
        {
            nMaxWordLength = nPos;
        }
        else
        {
            nMaxWordLength = MAX_WORD_LENGTH;//词的最大长度
        }

        fProb = 0;
        for (nWordLength=LETTER_LENGTH;nWordLength<nMaxWordLength+LETTER_LENGTH;nWordLength=nWordLength+LETTER_LENGTH)
        {
            strWord = strLine.substr(nPos-nWordLength,nWordLength);
            if (word_dict.find(strWord) != word_dict.end())
            {
                fProb = fProb + word_dict[strWord]*s_left[(nPos-nWordLength)/LETTER_LENGTH];
            }
            else
            {
                return -1;
            }
            //cout<<strWord<<endl;
        }
        s_left.push_back(fProb);
    }
    //PrintVector(s_left);

    //get s_right
    for (nPos=nLength;nPos>=0;nPos=nPos-LETTER_LENGTH)
    {
        if (nPos == nLength)
        {
            s_right.push_back(1);
            continue;
        }

        if ( (nLength - nPos) < MAX_WORD_LENGTH)
        {
            nMaxWordLength = nLength - nPos;
        }
        else
        {
            nMaxWordLength = MAX_WORD_LENGTH;
        }

        fProb = 0;
        for (nWordLength=LETTER_LENGTH;nWordLength<nMaxWordLength+LETTER_LENGTH;nWordLength=nWordLength+LETTER_LENGTH)
        {
            strWord = strLine.substr(nPos,nWordLength);
            if (word_dict.find(strWord) != word_dict.end())
            {
                fProb = fProb + word_dict[strWord]*s_right[(nLength-nPos-nWordLength)/LETTER_LENGTH];
                fIncrease = s_left[nPos/LETTER_LENGTH]*word_dict[strWord]*s_right[(nLength-nPos-nWordLength)/LETTER_LENGTH]/s_left.back();
                if ( fIncrease < 1)
                {
                    word_dict_new[strWord] = word_dict_new[strWord] + fIncrease;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return -1;
            }
            //cout<<strWord<<endl;
        }
        s_right.push_back(fProb);
    }
    //PrintVector(s_right);
    //PrintMap(word_dict_new);

    return 0;
}

int main(int argc, char * argv[])
{
    if ( 3 != argc)
    {
        cout<<"please input initial dict and data file name"<<endl;
        exit(0);
    }
    string str_data_file_name = argv[2];
    ifstream ifInFile(str_data_file_name.c_str());

    //load dict
    string dict_file_name = argv[1];//initial prob for every words
    ifstream dict_file(dict_file_name.c_str());
    string strLine = "";
    //map <string,float> word_dict;
    string strKey = "";
    double fValue = 0;

    while(getline(dict_file,strLine))
    {
        vector <string> words =  SplitString(strLine, "\t");
        strKey = words[0];
        fValue = atof(words[1].c_str());
        word_dict[strKey] = fValue;
    }
    cout<<word_dict["的"]<<endl;
    //caculte the prob
    strLine = "所有的一切都好像失去了色彩的";
    int nRet = 0;
    int nLineNum = 0;
    while(getline(ifInFile,strLine))
    {
        nRet = GetProb(strLine);
        if (nRet == 0)
        {
            nLineNum++;
        }
        if ( (nLineNum%100) == 0)
        {
            cout<<"line number "<<nLineNum<<endl;
        }
    }
    cout<<"line number "<< nLineNum<<endl;
    map<string,double>::iterator mapIt;
    for (mapIt=word_dict_new.begin();mapIt!=word_dict_new.end();mapIt++)
    {
        word_dict_new[mapIt->first] = word_dict_new[mapIt->first]/nLineNum;
    }
    PrintMap(word_dict_new);
    return 0;
}
