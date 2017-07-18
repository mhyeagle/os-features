#include <iostream>
#include <string>

#include <unistd.h>

#include "source_a.h"

using namespace std;

typedef int (*PTR_FUNC)();

int main() {
    SourceA test_a;
//    int num = test_a.func();
//    cout << "object's num: " << num << endl;
    PTR_FUNC p_func;
    auto p_func_1 = SourceA::func;
    int num1 = (*p_func)();
    cout << "num return by p_func(): " << num1 << endl;
}
