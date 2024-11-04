// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
//
// char getFirstChar(const char *str);
//
// int main(void)
// {
//     int n=0;
//
//     for(int i=0;;i++) {
//         if(n<=0){
//             //keep on asking for size until user enters a valid length i.e, n>0.
//             if(i>0){
//                 printf("Enter a valid size of the array element - \n");
//                 scanf("%d", &n);
//             }else{
//                 printf("Enter the size of the array element - \n");
//                 scanf("%d", &n);
//             }
//         }
//         else{
//             //size is satified therefore break the loop.
//             break;
//         }
//     }
//
//     char strings[n][100];
//     for(int i=0;i<n;i++) {
//         printf("Enter the string to sort at element at index %d:\n",i);
//         fflush(stdin);
//         // while (getchar() != '\n');
//
//         scanf("%[^\n]%*c", strings[i]);
//         // scanf("%s", strings[i]);
//     }
//
//     printf("Array of strings sorted before sorting is \n\n");
//     for(int i=0;i<n;i++) {
//         printf("%s\n", strings[i]);
//     }
//
//     //logic to sort the best
//     int currentLoc;
//     char* tempVar;
//
//     for(int i=0; i<n; i++) {
//         currentLoc = i;
//
//         while(currentLoc > 0 && getFirstChar(strings[currentLoc-1])>getFirstChar(strings[currentLoc])){
//             strcpy(tempVar, strings[currentLoc]);  // Copy currentLoc string to temp
//             strcpy(strings[currentLoc], strings[currentLoc - 1]);  // Move currentLoc-1 string to currentLoc
//             strcpy(strings[currentLoc - 1], tempVar);  // Copy temp (original currentLoc) to currentLoc-1
//             currentLoc--;
//         }
//     }
//
//     printf("Array of strings sorted after sorting is \n\n");
//     for(int i=0;i<n;i++) {
//         printf("%s\n", strings[i]);
//     }
//
//     return 0;
// }
//
// char getFirstChar(const char *str) {
//     while (*str != '\0') {
//         if (!isspace((unsigned char)*str)) {  // Check if the character is not a whitespace
//             return *str;
//         }
//         str++;
//     }
//     return '\0';
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char getFirstChar(const char *str);
void readStrings(char **strings, int n);
void sortStrings(char **strings, int n);
void displayStrings(char **strings, int n);

int main(void)
{
    int n = 0;

    
    while (n <= 0) {
        printf("Enter a valid size of the array element - \n");
        scanf("%d", &n);
    }

    
    char **strings = (char **)malloc(n * sizeof(char *));

    // Read the strings from the user
    readStrings(strings, n);

  
    printf("\nArray of strings before sorting:\n");
    displayStrings(strings, n);

  
    sortStrings(strings, n);

 
    printf("\nArray of strings after sorting:\n");
    displayStrings(strings, n);

    
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}

// Function to get the first non-whitespace character of a string
char getFirstChar(const char *str) {
    while (*str != '\0') {
        if (!isspace((unsigned char)*str)) {
            return *str;  
        }
        str++;
    }
    return '\0'; 
}

// Function to read strings from the users.
void readStrings(char **strings, int n) {
    char buffer[100];
    for (int i = 0; i < n; i++) {
        printf("Enter the string at element %d:\n", i);
        fflush(stdin);
        fgets(buffer, 100, stdin);  


        buffer[strcspn(buffer, "\n")] = '\0';

      
        strings[i] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (strings[i] == NULL) {
            printf("Memory allocation failed for string %d!\n", i);
            exit(1);  
        }

        // copy the input string to newely allocated memory
        strcpy(strings[i], buffer);
    }
}

// Function to sort strings using insertion sorting.
void sortStrings(char **strings, int n) {
    int currentLoc;
    char *tempVar;

    for (int i = 1; i < n; i++) {
        currentLoc = i;
        // Compare strings based on the first non-whitespace character
        while (currentLoc > 0 && getFirstChar(strings[currentLoc - 1]) > getFirstChar(strings[currentLoc])) {
            // swaping the strings
            tempVar = strings[currentLoc];
            strings[currentLoc] = strings[currentLoc - 1];
            strings[currentLoc - 1] = tempVar;
            currentLoc--;
        }
    }
}

// Function to display the array of strings - called in the very last.
void displayStrings(char **strings, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
    }
}
