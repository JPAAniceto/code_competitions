#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_DIGITS_N 16

long int solve(char* test_case, int size);
int get_string_size(char * str);
long int string_to_lint(char* str, int size);


int main(int argc, char **argv){

    int nr_test_cases;
    char test_case[MAX_DIGITS_N];
    
    scanf("%d",&nr_test_cases);

    // Iterate test cases
    long int solutions[nr_test_cases+1];
    char test_case_buff[MAX_DIGITS_N];

    for (int i =1 ; i <=nr_test_cases; i++){
        long int tst_case;
        long int solution ;
        scanf("%ld",&tst_case);
        snprintf(test_case,sizeof(test_case) ,"%ld", tst_case);
        solution = (long int)(solve(test_case, get_string_size(test_case)));
        printf("Case #%d: %ld %ld\n", i,solution, tst_case - solution );
        fflush(stdout);
    }


    return 0;
}


long int solve(char* test_case, int size){
    long int solution= 0;

    // printf("%s : %d\n", test_case,size);
    
    for(int i = size-1 ;i>=0;i--)
    {
        if(test_case[i] == '4')
        {
            solution += 3 * pow(10,size-(i+1));
        }
        else{
            solution += (test_case[i] - '0') * pow(10,size-(i+1));
        }
    }

    return solution;
}

// String Utils Functions

int get_string_size(char * str){
    int size = 0;
    while(*str != '\0' && *str != '\n')
    {
        str++;
        size++;
    }
    return size;
}

long int string_to_lint(char* str, int size)
{
    long int result=0;
    int index=size-1;

    while(index >= 0)
    {
        int exponent = (index+1) - size;
        long int multiplier = pow(10 , abs(exponent));
        result += multiplier*(str[index]-'0');
        index--;
    }

    return result;
}