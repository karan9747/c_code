#include <stdio.h>
#include <stdbool.h>


int main(int argc, char** argv){
    printf("Enter the number to check prime or not \n");
    bool isPrime;
    int number;
    scanf("%d",&number);

    if(number == 1 ){
            printf("The number - %d is a composite number",number);
    } else if(number<1){
            printf("The number - %d is not a prime number",number);
    } else if(number == 2){
            printf("The number - %d is a prime number",number);
    } else {
        isPrime = true;
        for(int i=2;i<number;i++){
            if(number%i==0){
                isPrime = false;
                break;
            } 
        }
        if(isPrime){
            printf("The number - %d is a prime number",number);
        } else {
            printf("The number - %d is not a prime number",number);
        }
    }
    return 0;
}