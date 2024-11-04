#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
     
    for(int i=0;;i++) {
        if(n<=0){
            //keep on asking for size until user enters a valid length i.e, n>0.
            if(i>0){
                printf("Enter a valid size of the array element - \n");
                scanf("%d", &n);
            }else{
                printf("Enter the size of the array element - \n");
                scanf("%d", &n); 
            }  
        }
        else{
            //size is satified therefore break the loop.
            break;
        }
    }

    // to get the size of an array dynamically at runtime use (sizeof(arr) / sizeof(arr[0]))
    int arr[n];
    for(int i=0;i<n;i++){
        //below code logic is for string formatting according to the last digit of the index
         char *placeholder;
        placeholder ="th";
        if(i !=0){
            if(i%10 == 1){
                placeholder = "st";
            } else if(i%10 == 2){
                placeholder = "nd";
            } else if(i%10 ==3){
                placeholder = "rd";
            }
        }
        printf("Please enter the element at %d%s Index \n",i, placeholder);
        scanf("%d",&arr[i]);
    }

    //printing the values of array before sorting...
    printf("Array before sorting\n");
    for(int i=0;i<n;i++){
        printf("%d\t",arr[i]);
    }

    //sorting logic
    int tempVar, currentLoc;
    for(int i=1;i<n;i++){
        currentLoc = i;

        while(currentLoc > 0 && arr[currentLoc-1]>arr[currentLoc]){
            tempVar = arr[currentLoc];
            arr[currentLoc] = arr[currentLoc-1];
            arr[currentLoc-1] = tempVar;
            currentLoc--;
        }
       
           
    }

    printf("\n\nArray after sorting\n");
    for(int i=0;i<n;i++){
        printf("%d\t",arr[i]);
    }
    printf("\n");
    return 0;
}
