#ifndef SOURCE_A_H__
#define SOURCE_A_H__

#include <iostream>

class SourceA {
public:
    SourceA();
    ~SourceA();

    static int func();
    int func_1();
private:
    int * p_source__;
};


#endif //SOURCE_A_H__
