#include "source_a.h"

SourceA::SourceA() {
    p_source__ = new int(10);
}

SourceA::~SourceA() {
    if (p_source__ != NULL) {
        delete p_source__;
        p_source__ = NULL;
    }
}

int SourceA::func_1() {
    return *p_source__;
}

int SourceA::func() {
    return 1024;
}
