#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define K_DEBUG false

void clrscr();
void setupLogWithMessage(char* message);
int* replaceEvenWithZero (int arr[]);
char* primeOrFactorial(int number);
const char* longToString(long num);
int UABIndexSum(int arr[]);
bool evenSquare(int n);
int countVowels(char* s);

int main(int argc, char** argv) {
    int choice=0;
    bool proceed = true;
//handle the ascii value comparison to make sure that the user is entering a number instead of a string character!
    while (proceed)
    {
        printf("\nEnter the program index you want to test\n\n");
        printf("1. primeOrFactorial(n)\n");
        printf("2. UABIndexSum(arr)\n");
        printf("3. replaceEvenWithZero (arr)\n");
        printf("4. evenSquare(n)\n");
        printf("5. countVowels(s)\n");
        printf("6. EXIT\n\n\n");

        scanf("%d",&choice);

        if(choice == 1) {
            //logic for prime factorial program.
            // clrscr();
            int number;
            int result = 0;
            printf("Enter the number to check prime or factorial \n");
            result = scanf("%d",&number);

            while(result == 0 ) {
                //will only jump inside a loop when the previous entry is invalid
                printf("Enter a valid number to check prime or factorial \n");
                result = scanf("%d",&number);
            }
            printf("%s", primeOrFactorial(number));
        } else if(choice == 2) {
            // clrscr();

            int n=0;

            for(int i=0;;i++) {
                if(n<=0){
                    //keep on asking for size until user enters a valid length i.e, n>0.
                    int result = 0;
                    printf("Enter the size of the array element\n");
                    result = scanf("%d",&n);

                    while(result == 0 ) {
                        //will only jump inside a loop when the previous entry is invalid
                        printf("Enter a valid number for setting size of the array element \n");
                        result = scanf("%d",&n);
                    }
                }
                else{
                    //size is satified therefore break the loop.
                    break;
                }
            }

            // to get the size of an array dynamically at runtime use (sizeof(arr) / sizeof(arr[0]))
            int arr[n+1];
            for(int i=0;i<n;i++) {
                //below code logic is for string formatting according to the last digit of the index
                char *placeholder;
                placeholder ="th";
                if(i !=0) {
                    if (i > 10 && i < 20) {
                        placeholder = "th";
                    } else if(i%10 == 1){
                        placeholder = "st";
                    } else if(i%10 == 2){
                        placeholder = "nd";
                    } else if(i%10 ==3){
                        placeholder = "rd";
                    }
                }
                printf("Please enter the element at %d%s Index \n",i, placeholder);
                scanf("%d",&arr[i]);
                if(arr[i] < 0) {
                    printf("The element entered is less than zero\n");
                    --i;
                }
            }

            //adding a -ve element at the last to determine the total size of
            arr[n] = -1;
            printf("The sum of elements of array for UABIndexSum condition is %d",UABIndexSum(arr));
        } else if(choice == 3) {
        // logic for replacing even array element with 0
            // clrscr();
            // printf("Enter the size of the array \n");

            int n=0;

            for(int i=0;;i++) {
                if(n<=0){
                    //keep on asking for size until user enters a valid length i.e, n>0.
                    int result = 0;
                    printf("Enter the size of the array element\n");
                    result = scanf("%d",&n);

                    while(result == 0 ) {
                        //will only jump inside a loop when the previous entry is invalid
                        printf("Enter a valid number for setting size of the array element \n");
                        result = scanf("%d",&n);
                    }
                }
                else{
                    //size is satified therefore break the loop.
                    break;
                }
            }

            // to get the size of an array dynamically at runtime use (sizeof(arr) / sizeof(arr[0]))
            int arr[n+1];
            for(int i=0;i<n;i++) {
                //below code logic is for string formatting according to the last digit of the index
                char *placeholder;
                placeholder ="th";
                if(i !=0) {
                    if (i > 10 && i < 20) {
                        placeholder = "th";
                    } else if(i%10 == 1){
                        placeholder = "st";
                    } else if(i%10 == 2){
                        placeholder = "nd";
                    } else if(i%10 ==3){
                        placeholder = "rd";
                    }
                }
                printf("Please enter the element at %d%s Index \n",i, placeholder);
                scanf("%d",&arr[i]);
                if(arr[i] < 0) {
                    printf("The element entered is less than zero\n");
                    --i;
                }
            }

            //adding a -ve element at the last to determine the total size of
            arr[n] = -1;
            int* myArray = replaceEvenWithZero(arr);
            printf("[");
            for(int i=0;i<n;i++) {
                if(i==n-1) {
                    printf("%d",myArray[i]);
                }else {
                    printf("%d,\t",myArray[i]);
                }
            }
            printf("]");
        } else if(choice ==4) {
            // clrscr();
            int number;
            int result = 0;
            printf("Enter the number to even square or not \n");
            result = scanf("%d",&number);

            while(result == 0 ) {
                //will only jump inside a loop when the previous entry is invalid
                printf("Enter a valid number to check prime or factorial \n");
                result = scanf("%d",&number);
            }
            bool resultBool  = evenSquare(number);
            if(resultBool) {
                printf("True");
            }else {
                printf("False");
            }
        } else if(choice == 5) {/*
            printf("Enter the string to count the number of vowels:\n");
            char str[100];

            // Clear input buffer before reading input (if necessary) - This part obtained from SOF
            fflush(stdin);

            // Use fgets to read the entire line, including spaces
            if (fgets(str, sizeof(str), stdin) != NULL) {
                // Remove the newline character added by fgets, if present
                size_t len = strlen(str);
                if (len > 0 && str[len - 1] == '\n') {
                    str[len - 1] = '\0';
                }

                // Now count the vowels
                int result = countVowels(str);
                printf("%d\n", result);
                printf("Press Return/Enter to continue\n");
            } else {
                printf("Error reading input.\n");
            }*/
            char str[100];
            printf("Enter the string to count the number of vowels:\n");

        
            while (getchar() != '\n');  

            if (fgets(str, sizeof(str), stdin) != NULL) {
                // Remove the newline character added by fgets, if present
                size_t len = strlen(str);
                if (len > 0 && str[len - 1] == '\n') {
                    str[len - 1] = '\0';
                }

                // Now count the vowels
                int result = countVowels(str);
                printf("%d\n", result);
                printf("Press Enter/Return to continue\n");
                //above code logic is copied from github for removing special character and white spaces from input buffer before actual user input is read!
            } else {
                printf("Error reading input.\n");
            }
        } else if(choice == 6) {
            break;
        }

        // Clear the input buffer
        while (getchar() != '\n');

        printf("\n\nPress 'N' or 'n' to exit, any other key & followed by pressing Enter to continue: ");
        char assertedKey = getchar();
        if (assertedKey == 'N' || assertedKey == 'n') {
            proceed = false;
        } else {
            proceed = true;
        }

        while (getchar() != '\n');
    }
    return 0;
}

char* primeOrFactorial(int number) {

    if(number<=1){
         return "Invalid Input";
    } else {
        bool isPrime = true;
        for(int i=2;i<number;i++){
            if(number%i==0){
                isPrime = false;
                break;
            }
        }
        if(isPrime) {
           return "Prime Number";
        } else {
            long factorial = 1;
            for(int i=1;i<number;i++){
                factorial*=i;
                // setupLogWithMessage(""+factorial);
            }
            //debig this code as im not sure about the return value after converting const to regex
            // setupLogWithMessage(""+(number*factorial));
           return (char*) longToString((long) (number*factorial));
        }
    }
    return 0l;
}


int UABIndexSum(int arr[]) {
    // logic for getting the sum of index sum where index  = same as the number in that index stored
    int i=0;
    int sum =0;
    while(arr[i]!=-1) {
        if(arr[i]==i) {
            sum+=i;
            // setupLogWithMessage("index "+i);
            // setupLogWithMessage("sum till index "+sum);
        }
        i++;
    }
    return sum;
}


    void clrscr(){
        //code called for clearing the console screen.
        system("cls||clear");
        // printf("\033[H\033[2J");
        // printf("\033[36m");
    }

bool evenSquare(int n) {
    if(n%2==0) {
        int sqrt_num = sqrt(n);
        return (sqrt_num * sqrt_num == n);
    } else {
        return false;
    }
}

const char* longToString(long num) {
    // Convert long to string and return the stirng that is dinamically allocated.
    char* str = malloc(20);
    if (str == NULL) {
        return NULL;
    }
    snprintf(str, 20, "%ld", num);
    return str;
}

void setupLogWithMessage(char* message) {
    if(K_DEBUG) {
        //if debug is enabled the code will bug out. KEEP IT DISABLED
        printf("\n");
        printf("----------------------------------------------------");
        printf("\n");
        printf("DEBUG:- %s", message);
        printf("\n");
        printf("----------------------------------------------------");
        printf("\n");
    }
}

int* replaceEvenWithZero (int arr[]) {
    int i=0;
    while(arr[i]!=-1) {
        if((arr[i] % 2) == 0) {
           arr[i] =0;
        }
        i++;
    }

    return arr;
}

int countVowels(char* s) {
    int i = 0;
    char* ptr = s;

    while (*ptr != '\0') {

        if (*ptr == 'a' || *ptr == 'e' || *ptr == 'i' || *ptr == 'o' || *ptr == 'u' ||
            *ptr == 'A' || *ptr == 'E' || *ptr == 'I' || *ptr == 'O' || *ptr == 'U') {
            i++;
            }
        // setupLogWithMessage(ptr);
        ptr++;
    }
    return i;  // Return the total count of vowels
}