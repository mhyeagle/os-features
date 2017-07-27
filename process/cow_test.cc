#include <iostream>

#include <unistd.h>

using namespace std;

int main() {
    const int num = 2000000;
    pid_t pid;
    unsigned long * p_long = new unsigned long[num];
    for(int i = 0; i < num; i++) {
        *(p_long + i) = i;
    }

    pid = fork();
    if (pid < 0) {
        cout << "fork error." << endl;
        return -1;
    } else if (pid == 0) {
        cout << *(p_long + 100) << endl;
        cout << *(p_long + 1000) << endl;
        cout << *(p_long + num/2) << endl;
        cout << *(p_long + num) << endl;
        sleep(100);
    } else {
        sleep(-1);
    }

    return 0;
}
