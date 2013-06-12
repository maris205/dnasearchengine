#include <string>


namespace mapreduce {

public:
    virtual void Setup();
    virtual void Reduce(ReduceInput* input);

private:
    std::string m_str;
};
