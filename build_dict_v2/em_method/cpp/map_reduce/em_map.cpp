#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;


namespace mapreduce {
const int MAX_WORD_LENGTH = 12;
const int LETTER_LENGTH = 1;


int GetProb(string & strLine)
{
    vector <double> s_left;
    vector <double> s_right;
    int nLength = strLine.length();
    int nPos = 0;
    string strWord = "";
    int nWordLength = 0;
    int nMaxWordLength = 0;
    double fProb = 0;
    double fIncrease = 0;
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
    //PrintVector(s_left);
    return 0;
}

void Setup()
{
    //initial dict
    std::string local_dict_file = VPATH("./data/ngram.txt");
    std::string strLine = "";
     //load dict
    ifstream dict_file(local_dict_file.c_str());

    //map <string,float> word_dict;
    std::string strKey = "";
    double fValue = 0;

    while(getline(dict_file,strLine))
    {
        vector <string> words;
        SplitString(strLine, "\t", &words);
        strKey = words[0];
        fValue = atof(words[1].c_str());
        word_dict[strKey] = fValue;
    }


}
void Map(const MapInput &input) {
    m_record_counter->IncrementBy(1);
    word_dict_new.clear();
    string strLine = "";
    strLine = input.value().as_string();
    int nRet = GetProb(strLine);
    if (nRet != -1)
    {
        map<string,double>::iterator mapIt;
        for (mapIt=word_dict_new.begin();mapIt!=word_dict_new.end();mapIt++)
        {
            Output(mapIt->first, DoubleToString(mapIt->second));
        //word_dict_new[mapIt->first] = word_dict_new[mapIt->first]/nLineNum;
        }
    }
    //Output(strLine, "1");
    //Output(FloatToString(word_dict["的"]), "1");
}
}  // namespace mapreduce
