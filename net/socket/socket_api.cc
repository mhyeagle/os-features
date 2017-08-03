#include <iostream>
#include <string>

#include <unistd.h>

using namespace std;

int main() {
    char name[256];
    gethostname(name, sizeof(name));

    cout << "host name: " << name << endl;

    return 0;
}
