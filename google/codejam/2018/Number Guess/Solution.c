#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



int guess(int min, int max, int nr_guesses);

int main(){

    int nr_test_cases;
    // do
    // {
    scanf("%d",&nr_test_cases);
    // if(nr_test_cases==0){
    //     break;
    // }
    for (int i =0 ; i <nr_test_cases; i++){
        int nr_guesses;
        int min=0, max =0;
        scanf("%d %d",&min,&max);
        scanf("%d",&nr_guesses);
        guess(min+1,max,nr_guesses);
    }
    nr_test_cases--;
    // }while(nr_test_cases>0);
    return 0;
}

int guess(int min, int max, int nr_guesses){
    
    if(nr_guesses==0)
    {
        return 0;
    }
    
    int try = (int)((min+max)/2);
    printf("%d\n", try);
    fflush(stdout);
    
    char response[32];
    scanf("%s", response);
    
    if(strcmp(response,"CORRECT") == 0)
    {
        return 0;
    }
    else if (strcmp(response,"TOO_SMALL") == 0){
        guess(try + 1,max,nr_guesses-1);
    }
    else if (strcmp(response,"TOO_BIG") == 0){
        guess(min,try-1,nr_guesses-1);
    }
    else{
        return 0;
    }
    return 0;
}