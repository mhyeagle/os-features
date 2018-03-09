#include <iostream>
#include <signal.h>
#include <pthread.h>

using namespace std;

pthread_key_t key;

struct test_data {
    int i;
    float k;
};

void* thread_func1(void* arg) {
    struct test_data t1;
    t1.i = 10;
    t1.k = 1.1;
    pthread_setspecific(key, &t1);
    struct test_data * tp = (struct test_data*)pthread_getspecific(key);
    cout << "thread1 specific addr: " << tp << endl;
    cout << "tp->i: " << tp->i << endl;
    cout << "tp->k: " << tp->k << endl;
}

void* thread_func2(void* arg) {
    int tmp = 20;
    pthread_setspecific(key, &tmp);
    int* tp = (int*)pthread_getspecific(key);
    cout << "thread2 specific addr: " << tp << endl;
    cout << "tmp: " << *tp << endl;
}

int main() {
    pthread_t t1, t2;
    pthread_key_create(&key, NULL);
    pthread_create(&t1, NULL, thread_func1, NULL);
    pthread_create(&t2, NULL, thread_func2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_key_delete(key);

    return 0;
}
