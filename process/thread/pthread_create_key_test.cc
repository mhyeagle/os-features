#include <iostream>
#include <string>

#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_key_t key;

struct MyStruct {
    int num;
    float f;
    MyStruct() : num(0), f(0.0) {
    }
};

void * thread_func1(void * arg) {
    MyStruct s1;
    s1.num = 10;
    s1.f = 1.11;

    pthread_setspecific(key, &s1);

    cout << "s1 address: " << &s1 << endl;
    MyStruct * s_addr = (MyStruct *)pthread_getspecific(key);
    cout << "get address: " << s_addr << endl;
    cout << "s1.num: " << s_addr->num << endl;
    cout << "s1.f: " << s_addr->f << endl;
}

void * thread_func2(void * arg) {
    MyStruct s2;
    s2.num = 20;
    s2.f = 2.22;

    pthread_setspecific(key, &s2);

    cout << "s2 address: " << &s2 << endl;
    MyStruct * s_addr = (MyStruct *)pthread_getspecific(key);
    cout << "get address: " << s_addr << endl;
    cout << "s2.num: " << s_addr->num << endl;
    cout << "s2.f: " << s_addr->f << endl;
}

int main() {
    pthread_t t1, t2;
    pthread_key_create(&key, NULL);

    pthread_create(&t1, NULL, &thread_func1, NULL);
    pthread_create(&t2, NULL, &thread_func2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_key_delete(key);

    return 0;
}
