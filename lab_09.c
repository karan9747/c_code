/* Simple program to illustrate the use of fork-exec-wait pattern.
* This version uses execvp and command-line arguments to create a new process.
* To Compile: gcc -Wall forkexecvp.c
* To Run: ./a.out <command> [args]
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigchld_handler(int signo) {
    int status;
    waitpid(-1, &status, WNOHANG);  // Clean up child process

    if (WIFEXITED(status)) {
        printf("Child process exited with status = %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child process terminated by signal %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("Child process stopped by signal %d\n", WSTOPSIG(status));
    }
}

int main(int argc, char **argv) {
    pid_t pid;

    if (argc < 2) {
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    pid = fork();
    if (pid == 0) { /* this is the child process */
        // Child process responds to SIGINT and SIGTSTP
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);

        execvp(argv[1], &argv[1]);
        printf("If you see this statement then execvp failed ;-(\n");
        perror("execvp");
        exit(-1);
    } else if (pid > 0) { /* this is the parent process */
        // Parent process ignores SIGINT and SIGTSTP
        signal(SIGINT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);

        // Handle SIGCHLD for child process status
        signal(SIGCHLD, sigchld_handler);

        // Wait for SIGQUIT (Ctrl+\) to terminate the parent
        printf("Parent waiting. Type Ctrl+\\ to quit.\n");
        while (1) {
            pause();  // Wait for signals
        }
    } else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
    }

    return 0;
}
