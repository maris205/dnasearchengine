/**************************************************
divide the original sequence by space
for example "ATCCG" will be divided into "A T C C G"
this new format is suitable for srilm 
******************************************/
#include <iostream>
#include <string>
#include <fstream>
#include "stdlib.h"
using namespace std;
int main(int argc,char * argv[])
{
    if ( 2 != argc )
    {
        cout<<"please input filename"<<endl;
        exit(0);
    }
    string strFileName=argv[1];
    ifstream ifInFile(strFileName.c_str());
    string strLine="";
    string strSegment="";
    int nIdx=0;
    int nOneLineLength=0;
    int nMaxLength=300;//we write some lines of .fasta format into one line, set this value as nMaxLength
    string strOneLine="";
    
    while(getline(ifInFile,strLine))
    {
        if(0 != strLine.find(">"))
        {
        strSegment="";//clear the string
        if (strLine.length()>0)//if no word in one line
        {
            for (nIdx=0;nIdx<strLine.length()-1;nIdx++)
            {
                if (strLine[nIdx]=='A' || strLine[nIdx]=='T'
                    || strLine[nIdx]=='C' || strLine[nIdx]=='G' )
                {
                    strSegment=strSegment+strLine[nIdx]+" ";
                }
            }
            if (strLine[nIdx]=='A' || strLine[nIdx]=='T'
                || strLine[nIdx]=='C' || strLine[nIdx]=='G' )
            {
                strSegment=strSegment+strLine[nIdx];//avoid adding space in the end
            }
        }
         nOneLineLength++;
         if (0==(nOneLineLength%nMaxLength))
         {
             strOneLine=strOneLine+strSegment;
             cout<<strOneLine<<endl;
             strOneLine="";//clear line
         }
         else
         {
             strOneLine=strOneLine+strSegment+" ";
         }
        
    }
    }
    
    if (0!=(nOneLineLength%nMaxLength))
    {
        cout<<strOneLine<<endl;
    }
    
}
