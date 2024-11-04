#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{

    if (argc < 1)
        return 0;

    //argv[0] is the program name
    const char *fileName1 = argv[1];
    const char *fileName2 = argv[2];



    if(strcmp(fileName1,fileName2)!=0) {
        // FILE *file_ptr;
        // char ch;
        // // Opening file in reading mode
        // file_ptr = fopen(fileName1, "r");
        //
        // if (NULL == file_ptr) {
        //     printf("file can't be opened \n");
        //     return EXIT_FAILURE;
        // }
        //
        // while ((ch = fgetc(file_ptr)) != EOF) {
        //     printf("%c", ch);
        // }


        char * buffer = 0;
        long length;
        FILE * f = fopen (fileName1, "rb");

        if (f)
        {
            fseek (f, 0, SEEK_END);
            length = ftell (f);
            fseek (f, 0, SEEK_SET);
            buffer = malloc (length+1);
            if (buffer)
            {
                fread (buffer, 1, length, f);
                buffer[length] = '\0';
            }
            fclose (f);
        }

        if (buffer) {
            // Write content to fileName2
            FILE *fp2 = fopen(fileName2, "a+");
            if (!fp2) {
                printf("Unable to open output file: %s\n", fileName2);
                free(buffer);  // Free allocated memory before exiting
                return EXIT_FAILURE;
            }
            
            // Write the buffer to the output file
            fprintf(fp2, "\n%s\n", buffer);

            fclose(fp2);
            free(buffer);  // Free the buffer after use
        } else {
            printf("Failed to read from file: %s\n", fileName1);
        }

    } else {
        printf("Error: same file name.\n");
    }

    return 0;
}
