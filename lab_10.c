#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

void log_execution(char *command, time_t start, time_t end) {
    FILE *logFile = fopen("output.log", "a");
    if (logFile == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }
    fprintf(logFile, "%s\t%s\t%s", command, ctime(&start), ctime(&end));
    fclose(logFile);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening command file");
        return EXIT_FAILURE;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character from the line if present
        line[strcspn(line, "\n")] = 0;

        time_t start, end;
        time(&start);  // Record start time before forking

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            char out_filename[20], err_filename[20];
            snprintf(out_filename, sizeof(out_filename), "%d.out", getpid());
            snprintf(err_filename, sizeof(err_filename), "%d.err", getpid());

            int out_fd = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            int err_fd = open(err_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (out_fd == -1 || err_fd == -1) {
                perror("Error opening output files");
                exit(EXIT_FAILURE);
            }

            dup2(out_fd, STDOUT_FILENO);
            dup2(err_fd, STDERR_FILENO);

            close(out_fd);
            close(err_fd);

            // Split the command and arguments
            char *args[10];
            int i = 0;
            args[i] = strtok(line, " ");
            while (args[i] != NULL) {
                args[++i] = strtok(NULL, " ");
            }

            execvp(args[0], args);
            perror("execvp failed");
            exit(EXIT_FAILURE);

        } else if (pid > 0) {
            // Parent process
            wait(NULL); // Wait for the child process to finish
            time(&end); // Record end time

            log_execution(line, start, end);
        } else {
            perror("fork failed");
            return EXIT_FAILURE;
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}
