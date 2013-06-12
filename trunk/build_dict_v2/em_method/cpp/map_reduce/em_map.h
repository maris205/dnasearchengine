#include <map>
#include <string>
using namespace std;

namespace mapreduce {
    map <string,double> word_dict;
    map <string,double> word_dict_new;
    int GetProb(string & strLine);
}
