#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_DIGITS_N 16

void main(int argc, char **argv){
    // Reading input file name
    if(argc<=1){
        fprintf(stderr, "%s\n", "Not enough args");
        exit(0);
    }

    FILE *f;
    f = fopen(argv[1], "r");

    char test_cases_buff[3];

    // Interpret First line
    fgets(test_cases_buff, 3 ,(FILE*)f);
    int nr_test_cases = test_cases_buff[0] - '0';
    printf("Nr test cases : %d\n", nr_test_cases);

    // Iterate test cases
    char solutions[nr_test_cases][MAX_DIGITS_N];
    char test_case_buff[MAX_DIGITS_N];

    for (int i =0 ; i <nr_test_cases; i++){
        memset(test_case_buff, '\0', MAX_DIGITS_N);
        fgets(test_case_buff, MAX_DIGITS_N ,(FILE*)f);
        solve(test_case_buff, str_length(test_case_buff),solutions[i]);
    }
}

int str_length (char* str){
    int size = 0;
    while(*str != '\0')
    {
        str++;
        size++;
    }
    return size;
}

void solve(char* test_case, int size, char* solution)
{
    float nr_plus = 0,nr_minus = 0;
    char test_case_tmp[size];
    copy_string(test_case,test_case_tmp_plus);
    copy_string(test_case,test_case_tmp_minus);
    for(int i = size; i>1;i--)
    {
        char* number = {test_case_tmp[i-1],test_case_tmp[i]};
        switch(check_even(number))
        {
            // EE
            case 0:
                break;
            // EO
            case 1:
                nr_plus++;
                nr_minus++;
                if(test_case_tmp[i] - '' == 9){
                    calculate_new_test_case_plus(new_result);
                }
                if(test_case_tmp[i] - '' > 0){
                    calculate_new_test_case_minus(new_result);
                }
                break;
            // OE
            case 2:
                break;
            // OO
            case 3:
                break;
        }
    }
}

int check_even(char* number)
{
    if((double)(number[1] - '') % 2 == 0)
    {
        if((double)(number[0] - '') % 2 == 0)
            return 0;
        else 
            return 1;
    }
    else 
    {
        if((double)(number[0] - '') % 2 == 0)
            return 2;
        else 
            return 3;
    }
}

int dist_to_even_plus(int nr)
{
    // int button_presses = 10-nr;
    // return (button_presses <= 5) ? button_presses : -(button_presses+1);
    return 10-nr;
}

int dist_to_even_minus(int nr)
{
    return nr+1;
}

void copy_string(char *src, char *dst){
    while(*src != '\0')
    {
        *dst = *src;
        src++;
        dst++; 
    }
}
