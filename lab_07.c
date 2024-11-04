#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        exit(1);
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening file");
        exit(1);
    }

    FILE *log_file = fopen("output.log", "a");
    if (!log_file) {
        perror("Error opening log file");
        fclose(input_file);
        exit(1);
    }

    char command[256];
    while (fgets(command, sizeof(command), input_file)) {
        command[strcspn(command, "\n")] = 0;  
        
        time_t start_time = time(NULL);

        pid_t pid = fork();
        if (pid == 0) {  
            char *args[] = {"/bin/sh", "-c", command, NULL};  
            execv(args[0], args);
            perror("execv failed");
            exit(1);
        } else if (pid > 0) {  
            int status;
            wait(&status);  

            
            time_t end_time = time(NULL);
        fprintf(log_file, "%s\t%s\t%s", command, ctime(&start_time), ctime(&end_time));
        } else {
            perror("fork failed");
        }
    }

    fclose(input_file);
    fclose(log_file);

    return 0;
}
