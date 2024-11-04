#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void traverse_fun(const char *dirPath);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 0;
    }

    const char *dirPath = argv[1];

    // Start going thru the path
    traverse_fun(dirPath);

    return 0;
}

void traverse_fun(const char *dirPath) {
    DIR *dir;
    struct dirent *ent;

    // Try to open the directory first 
    if ((dir = opendir(dirPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // Skip the current and parent directories
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;

            // Construct the full path of the current file/directory
            char fullPath[1024];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, ent->d_name);

            printf("%s\n", fullPath);

            // Check is a directory
            struct stat pathStat;
            stat(fullPath, &pathStat);
            if (S_ISDIR(pathStat.st_mode)) {
                //calling same function(recursion) with subfolder path
                traverse_fun(fullPath);
            }
        }
        closedir(dir);
    } else {
        // Could not open directory due to some reason(prolly invalid path)
        printf("Could not open directory: %s\n", dirPath);
    }
}
