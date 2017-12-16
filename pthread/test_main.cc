#include <iostream>
#include <string>

#include <unistd.h>

#include "class_demo.h"

using namespace std;

int main() {
    Demo test1;
    pthread_t pid1;
    pthread_create(&pid1, NULL, Demo::thread_func, &test1);
    pthread_join(pid1, NULL);

    cout << "demo class num__: " << test1.value() << endl;

    return 0;
}
