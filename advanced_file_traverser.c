/*
Name: Karan Raju
BlazerId:kraju
Project #: Assignment 02
To compile: 
    1. Make sure that you have both the files(makefile and .c) in the same folder
    2. Install makefile extension for github code space (Extension code: ms-vscode.makefile-tools)
    3. run the following code into the terminal without quotes "make"
    4. run the following code into the terminal without quotes "gcc -o traverse advanced_file_traverser.o"

To run: 
    1. ./traverse
    2. ./traverse -S
    3. ./traverse -f "pattern" -r /path_to_folder
    etc..

Note: Progran will exit without a warning if there is no result. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct file_entry {
    char *name;
    off_t size;  
    int is_dir;
};

typedef int (*compare_func_t)(const void *, const void *);

void traverse_directory(const char *dir_name, int show_size, off_t min_size, const char *pattern, compare_func_t cmp);
int compare_size_asc(const void *a, const void *b);
int compare_size_desc(const void *a, const void *b);
void list_directory(const char *dir_name, int show_size, off_t min_size, const char *pattern, compare_func_t cmp, int depth);
void display_file(const struct file_entry *entry, int show_size, int depth);

int main(int argc, char *argv[]) {
    int show_size = 0, reverse = 0;
    off_t min_size = 0;
    char *pattern = NULL;
    char *start_dir = ".";  
    compare_func_t cmp = NULL;  // Default sorting

    int opt;
    while ((opt = getopt(argc, argv, "Ss:f:r")) != -1) {
        switch (opt) {
            case 'S':
                show_size = 1;  
                cmp = compare_size_asc;  // sorting by size
                break;
            case 's':
                min_size = atoi(optarg);  // filtering by size min -> max
                break;
            case 'f':
                pattern = optarg;  // Filter by any pattern inputted by the user
                break;
            case 'r':
                reverse = 1;  
                cmp = compare_size_desc;  // Enable reverse sorting
                break;
            default:
                fprintf(stderr, "Usage: %s [-S] [-s size] [-f pattern] [-r] [directory]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        start_dir = argv[optind]; 
    }

    traverse_directory(start_dir, show_size, min_size, pattern, cmp);
    return 0;
}

void traverse_directory(const char *dir_name, int show_size, off_t min_size, const char *pattern, compare_func_t cmp) {
    list_directory(dir_name, show_size, min_size, pattern, cmp, 0);
}

void list_directory(const char *dir_name, int show_size, off_t min_size, const char *pattern, compare_func_t cmp, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    struct file_entry *files = NULL;
    int file_count = 0;

    if ((dir = opendir(dir_name)) == NULL) {
        perror("opendir() error");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (lstat(path, &file_stat) == -1) {
            perror("lstat() error");
            continue;
        }

        if (S_ISREG(file_stat.st_mode)) {  // Only apply filter to regular files and ignore directories
            if (file_stat.st_size >= min_size && (!pattern || strstr(entry->d_name, pattern))) {
                files = realloc(files, sizeof(struct file_entry) * (file_count + 1));
                files[file_count].name = strdup(entry->d_name);
                files[file_count].size = file_stat.st_size;
                files[file_count].is_dir = 0;
                file_count++;
            }
        }
    }

    if (cmp != NULL) {  // Sort the files if sorting function is provided
        qsort(files, file_count, sizeof(struct file_entry), cmp);
    }

    printf("%s:\n", dir_name);

    for (int i = 0; i < file_count; i++) {
        display_file(&files[i], show_size, depth);
        free(files[i].name);
    }

    free(files);
    closedir(dir);
}

int compare_size_asc(const void *a, const void *b) {
    const struct file_entry *fa = a;
    const struct file_entry *fb = b;
    return (fa->size - fb->size);  
}

int compare_size_desc(const void *a, const void *b) {
    const struct file_entry *fa = a;
    const struct file_entry *fb = b;
    return (fb->size - fa->size);  
}

void display_file(const struct file_entry *entry, int show_size, int depth) {
    for (int i = 0; i < depth; i++)
        printf("\t");  
    if (show_size) {
        printf("%s (%ld bytes)\n", entry->name, entry->size);
    } else {
        printf("%s\n", entry->name);
    }
}
