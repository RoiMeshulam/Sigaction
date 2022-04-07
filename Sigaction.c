#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> /* O_ constants */
#include <sys/mman.h> /* mmap */

void sig5(int signum){
    printf("Signal: Invalid memory reference\n");
    fflush(stdout);
    printf("Raised 5 different signals\n");
    exit(1);
}

void sig4(int signum){
    printf("Signal: Abort signal\n");
    signal (SIGSEGV, sig5);
    //raised by accesing a memory we cannot
    int *a;
    *a = 0;
    fflush(stdout);
}

void sig3(int signum){
    printf("Signal: USER DEFINED 1\n");
    signal (SIGABRT, sig4);
    //raised by abort() command
    abort();
    fflush(stdout);
}

void sig2(int signum){
    printf("Signal: Floating-point exception\n");
    signal (SIGUSR1, sig3);
    //raised by raise() command
    raise(SIGUSR1);
    fflush(stdout);
}

void sig1(int signum){
    printf("Signal: Child coudlnt be stopped or terminated\n");
    signal (SIGFPE, sig2);
    int i =0;
    int k = 7;
    int t;
    //raised by deviding by 0
    t = k/i;
    fflush(stdout);
}

int main(){
    int status;
    signal (SIGCHLD, sig1);
    //raised by a child that was terminated
    if (!(fork())) {
        exit(1);
    }
    wait(&status);
    return 0;
}