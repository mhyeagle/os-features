#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* f1 = fopen("/usr/include/aio.h", "r");
    printf("f1 file descriptor: %d\n", f1->_fileno);

    FILE* f2 = fopen("/usr/include/elf.h", "r");
    printf("f2 file descriptor: %d\n", f2->_fileno);

    return 0;
}
