#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    FILE* f1 = fopen("/usr/include/aio.h", "r");
    printf("f1 file descriptor: %d\n", f1->_fileno);

    FILE* f2 = fopen("/usr/include/elf.h", "r");
    printf("f2 file descriptor: %d\n", f2->_fileno);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("sockfd number: %d\n", sockfd);

    return 0;
}
