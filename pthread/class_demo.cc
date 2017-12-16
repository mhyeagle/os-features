#include <unistd.h>
#include "class_demo.h"

void * Demo::thread_func(void * arg) {
    Demo * demo = (Demo *)arg;
    demo->process_func(); 
}

void Demo::process_func() {
    for (int i = 0; i < 5; ++i) {
        num__++;
    }
    sleep(2);
}

int Demo::value() const {
    return num__;
}
