/*
 * Posix shared memory is easy to use in Linux 2.6, in this program, we shared a memory
 * between parent and child process, stored several objects of struct namelist in it. We
 * store number of items in ptr[0].
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FILE_MODE (S_IRUSR | S_IWUSR)

const char shmfile[] = "/tmp";
const int size = 100;

struct namelist {
    int id;
    char name[20];
};

int main(void) {
    int fd, pid, status;
    int *ptr;
    struct stat stat;

    //create a Posix shared memory
    int flags = O_RDWR | O_CREAT;
    fd = shm_open(shmfile, flags, FILE_MODE);
    if (fd < 0) {
        printf("shm_open failed, errmsy = %s errno = %d", strerror(errno), errno);
        return 0;
    }
    
    ftruncate(fd, size);
    ptr = (int*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    pid = fork();
    if (pid == 0) {
        printf("Child %d: start\n", getpid());

        fd = shm_open(shmfile, flags, FILE_MODE);
        fstat(fd, &stat);
        ptr = (int*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd);
        struct namelist tmp;
    
        //store total num in ptr[0];
        *ptr = 3;
    
        ptr++;
        namelist *cur = (namelist*)ptr;
    
        //store items
        tmp.id = 1;
        strcpy(tmp.name, "Nellson");
        *cur++ = tmp;
        tmp.id = 3;
        strcpy(tmp.name, "Robbie");
        *cur++ = tmp;
    
        exit(0);
    } else { //parent process
        sleep(1);
        struct namelist tmp;

        int total = *ptr;
        printf("\nThere is %d item in the shm\n", total);

        ptr++;
        namelist *cur = (namelist*)ptr;

        for(int i = 0; i < total; i++) {
            tmp = *cur;
            printf("%d: %s\n", tmp.id, tmp.name);
            cur++;
        }

        printf("\n");
        waitpid(pid, &status, 0);
    }

    //remove a Posix shared memory from system
    printf("Parent %d get child status: %d\n", getpid(), status);
    

    return 0;
}
