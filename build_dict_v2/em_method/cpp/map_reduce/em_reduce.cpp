#include <fstream>
#include <stdlib.h>
using namespace std;

namespace mapreduce {


void VpathReducer::Reduce(ReduceInput* input) {
    double fSum = 0;
    double fValue = 0;
    while (!input->done())
    {
        fValue = atof(input->value().as_string().c_str());
        fSum = fSum + fValue;
        input->Next();
    }
    Output(input->primary_key().as_string() +  "\t" + FloatToString(fSum));
}
}  // namespace mapreduce
