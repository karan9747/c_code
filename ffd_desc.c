/*
Name:karan raju
BlazerId: kraju
Project #: Homework 03
To compile: make -f makefile2
To run: 
———./ffd_desc <directory_name>. 
OR
———./ffd_desc  -u <UserName> <directory_name>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <fcntl.h>

void printFileInfo(const char *filepath, const char *filename, const char *username) {
    struct stat file_stat;
    if (stat(filepath, &file_stat) != 0) {
        perror("Error getting file info");
        exit(1);
    }

    // If username filtering is enabled, check the file's owner
    if (username) {
        struct passwd *pw = getpwuid(file_stat.st_uid);
        if (!pw || strcmp(pw->pw_name, username) != 0) {
            exit(0);  // Exit child if file owner doesn't match the specified username
        }
    }

    printf("File: %s | Size: %lld bytes", filename, (long long)file_stat.st_size);

    // Count words only if it's a .txt file
    if (strstr(filename, ".txt")) {
        FILE *file = fopen(filepath, "r");
        if (!file) {
            perror("Error opening file");
            exit(1);
        }

        int words = 0;
        char ch, prev_ch = ' ';
        while ((ch = fgetc(file)) != EOF) {
            if ((ch == ' ' || ch == '\n' || ch == '\t') && prev_ch != ' ' && prev_ch != '\n' && prev_ch != '\t') {
                words++;
            }
            prev_ch = ch;
        }
        fclose(file);
        printf(" | Words: %d", words);
    }

    // If username is specified, display it
    if (username) {
        struct passwd *pw = getpwuid(file_stat.st_uid);
        printf(" | Owner: %s", pw->pw_name);
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    const char *directory = NULL;
    const char *username = NULL;

    // Parse command-line arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-u username] <directory_name>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-u") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: %s [-u username] <directory_name>\n", argv[0]);
            return 1;
        }
        username = argv[2];
        directory = argv[3];
    } else {
        directory = argv[1];
    }

    // Validate the directory exists
    struct stat dir_stat;
    if (stat(directory, &dir_stat) != 0 || !S_ISDIR(dir_stat.st_mode)) {
        fprintf(stderr, "Error: Directory not found.\n");
        return 1;
    }

    // Open the directory
    DIR *dir = opendir(directory);
    if (!dir) {
        perror("Error opening directory");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (entry->d_name[0] == '.')
            continue;

        // Construct the full path to the file
        char filepath[1024];
        snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

        // Check if it's a regular file
        struct stat file_stat;
        if (stat(filepath, &file_stat) != 0 || !S_ISREG(file_stat.st_mode))
            continue;

        // Fork a new process for each file
        pid_t pid = fork();
        if (pid == 0) {
            // In child process
            printFileInfo(filepath, entry->d_name, username);
            exit(0);
        } else if (pid < 0) {
            perror("Error: Failed to create process");
        }
    }

    // Wait for all child processes
    while (wait(NULL) > 0);

    closedir(dir);
    return 0;
}
