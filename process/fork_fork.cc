#include <unistd.h>
#include <sys/wait.h>

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
    pid_t pid;
    if ((pid = fork()) < 0) {
        cerr << "fork error." << endl;
    } else if (pid == 0) {
        if ((pid = fork()) < 0) {
            cerr << "fork error, in child process. " << endl;
        } else if (pid > 0) {
            exit(0);
        } else {
            sleep(1);
            cout << "***my parent process id: " << getppid() << endl;
            exit(0);
        }
    }

    if (waitpid(pid, NULL, 0) != pid)
        cerr << "waitpid error." << endl;
    else 
        cout << "wait first process success." << endl;

    exit(0);

}
