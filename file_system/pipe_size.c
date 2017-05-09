#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main() {
    int tube[2];
    char c = 'c';
    
    printf("create tube\n");
    printf("theoretical max pipe size: %d\n", PIPE_BUF);

    if (pipe(tube) != 0) {
        perror("pipe");
        exit(1);
    }

    printf("write to pipe, one char per time\n");
    for( int i = 0; ;++i) {
        printf("write number: %d char to pipe\n", i+1);
        if (write(tube[1], &c, 1) != 1) {
            perror("write");
            exit(1);
        }
    }

    return 0;
}
