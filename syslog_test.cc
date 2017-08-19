#include <iostream>
#include <string>

#include <syslog.h>

using namespace std;


int main() {
    syslog(LOG_WARNING, "this is a warning syslog test.\n");

    return 0;
}
