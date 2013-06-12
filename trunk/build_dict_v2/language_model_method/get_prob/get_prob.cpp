//get the probility a sequence according to n-gram model
// set ngram_order first, here is 9
#include <stdio.h>
#include "Ngram.h"
#include <vector>
#include <fstream>
using namespace std;

/*function: get the probility of a sequence
input: strText, the input sequence
input: voc,vocabuary
input: lm,language model
output: fProbility ,the probility of sequence
return: 0,right, else, false
*/
int GetSequenceProb(string & strText,float & fProbility,Vocab & voc,Ngram & lm)
{
    string strWord="";
    fProbility=0;
    int nLength=strText.length();
    int nIdx=0;
    int nIdx1=0;
    VocabIndex wid1;
    VocabIndex wid2;

    for (nIdx=0;nIdx<nLength;nIdx++)
    {   
        strWord=strText.substr(nIdx,1);
        wid1 = voc.getIndex(strWord.c_str());
       // cout<<strWord<<" ID "<<wid1<<endl;

        VocabIndex * context=new VocabIndex[nIdx+1];
        for (nIdx1=0;nIdx1<nIdx;nIdx1++)
        {
            strWord=strText.substr(nIdx-nIdx1-1,1);
            wid2 = voc.getIndex(strWord.c_str());
            context[nIdx1]=wid2;
          //  cout<<wid2<<" ";
           
        }
        context[nIdx]=Vocab_None;
        
        //printf(" %d\n", context[nIdx]);
        //cout<<"p()"<<lm.wordProb(wid1,context)<<endl;
        fProbility=fProbility+lm.wordProb(wid1,context);
        //cout<<"current prob"<<fProbility<<endl;
		delete [] context;
    }

	return 0;
}
int main(int argc, char *argv[])
{
   
    if (3 != argc)
    {
        cout<<"please input language model filename and dict filename"<<endl;
        exit(0);
    }

	int ngram_order = 9;//n of n-gram
    Vocab voc;
    Ngram lm( voc, ngram_order );//define language model
    
    {
        const char * lm_filename = argv[1];//language model file
        File lmFile( lm_filename, "r" );
        lm.read(lmFile);//initial language model
        lmFile.close();
    }
    string strText="AAAAAAAAAA";
	float fProbility=0;


    string strFileName=argv[2];//dict file
    ifstream ifInFile(strFileName.c_str());
    string strLine="";
    while(getline(ifInFile,strLine))
    {
        GetSequenceProb(strLine,fProbility,voc,lm);
        cout<<strLine<<"\t"<<fProbility<<endl;
    }
    return 0;
}

