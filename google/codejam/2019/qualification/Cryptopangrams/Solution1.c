#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_DIGITS_N 16

void solve(long int * values, int nr_values, long int n, char * solution);
long int prime_in_list (long int prime, long int* prime_list, int nr_primes);
void get_pair_of_primes (long int product_prime, long int * prime_list, int nr_primes, int* pair);
int in_list(long int * list , int size ,long int num);
void sort_list(long int * list, int size);


int main(int argc, char **argv){
    // Reading input file name
    if(argc<=1){
        fprintf(stderr, "%s\n", "Not enough args");
        exit(0);
    }

    FILE *f;
    f = fopen(argv[1], "r");

    int nr_test_cases;

    

    fscanf(f,"%d",&nr_test_cases);
    fflush(stdin);
    printf("Nr test cases : %d\n", nr_test_cases);
    fflush(stdout);
    // Iterate test cases
    long int n=0;
    int nr_values=0;

    for (int i =1 ; i <=nr_test_cases; i++){
        fscanf(f,"%ld",&n);
        fflush(stdin);
        fscanf(f,"%d",&nr_values);
        fflush(stdin);

        
        long int * values = (long int *)malloc(nr_values * sizeof(long int));
        for(int j=0 ; j<nr_values;j++){
            fscanf(f,"%ld",&values[j]);
            fflush(stdin);

        }
        printf("Last Value %ld\n", values[nr_values-1]);
        fflush(stdout);
        char* solution = (char*)malloc(nr_values * sizeof(char) +1);
        memset(solution, '\0', nr_values +1);

        solve(values, nr_values, n, solution);
        free(values);
        printf("Case #%d: %s\n", i,solution);
        fflush(stdout);
        free(solution);

    }

    fclose(f);

    return 0;
}


void solve(long int *  values, int nr_values, long int n, char * solution){

    /* -------- Step 1 we must calculate all primes within the n limit ---------- */
    int check_prime;
    long int *prime_list = (long int*)malloc(sizeof(long int));
    long int count = 1;

    prime_list[0]=2;

    for(long int i=3; i<=n; i++)
    {
        check_prime = 1;
        for(long int j=2; j<=i/2; j++)
        {
            if(i%j == 0)
            {
                check_prime = 0;
                break;
            }
        }
        if(check_prime){
            prime_list = (long int*)realloc(prime_list,  (count+1) * sizeof(long int));
            prime_list[count]=i;
            count++;
        }
    }

    /* ------ Step 2 find all primes used in cryptogram -------*/
    
    // letter[0] = A etc..
    long int *letters = (long int*)malloc(26*sizeof(long int));
    int letter_index=0;

    // We know that A is within the limit [0, count] primes in prime list
    // We also know that B is within the limit [A_index + 1 , count] primes in prime list
    for(long int i = 0; i<count-1;i++)
    {
        for (long int j=i+1;j<count;j++){
            long int prime_index= prime_in_list (prime_list[j]*prime_list[i], values , nr_values);
            if(prime_index > -1){

                // prime equivalent of letters[letter_index]
                
                if (prime_in_list(prime_list[i],letters,26) == -1){
                    letters[letter_index] = prime_list[i];
                    letter_index++;
                    if(letter_index>25){
                        break;
                    }
                }
                
                if (prime_in_list(prime_list[j],letters,26) == -1){
                    letters[letter_index] = prime_list[j];
                    letter_index++;
                }
                
            }
            if(letter_index>25){
                break;
            }
        }

    }
    // for(int i=0;i<26;i++)
    //     printf("%ld\n", letters[i]);
    // printf("---------------------------\n");
    sort_list(letters,26);
    // for(int i=0;i<26;i++)
    //     printf("%ld\n", letters[i]);

    /* ------------ Step 3 , find string -------------*/

    int values_solutions[nr_values];
    int pair1[2]={0,0};
    int pair2[2]={0,0};

    get_pair_of_primes (values[0], letters, 26, pair1);
    int i = 0;
    for( i = 1; i<nr_values;i++){
        get_pair_of_primes (values[i], letters, 26, pair2);
        
        if (pair1[0] == pair2[0] || pair1[0] == pair2[1])
        {
            values_solutions[i-1]= pair1[1];
            pair1[0] = pair2[0];
            pair1[1] = pair2[1];
        }
        else 
        {
            values_solutions[i-1] = pair1[0];
            pair1[0] = pair2[0];
            pair1[1] = pair2[1];
        }

    }

    get_pair_of_primes (values[i-1], letters, 26, pair2);

    if (pair1[0] == pair2[0] || pair1[0] == pair2[1])
    {
        values_solutions[nr_values-1] = pair1[1];
    }

    else
    {
        values_solutions[nr_values-1] = pair1[0];
    }

    for (int i =0 ; i<nr_values; i++)
    {
        printf("%d\n", values_solutions[i]);
        fflush(stdout);
        solution[i] = 'A' + (int)values_solutions[i];
    }

    free(prime_list);
    free(letters);

}

// Returns the index of the prime if its in the list or -1 if not
long int prime_in_list (long int prime, long int* prime_list, int nr_primes){
    for (int index=0 ; index<nr_primes; index++)
    {
        if(prime_list[index]==prime)
        {
            return index;
        }
    }
    return -1;
}

// Returns the index of the pair of primes
void get_pair_of_primes (long int product_prime, long int * prime_list, int nr_primes, int* pair){
    for (int i = 0; i < nr_primes; ++i)
    {
        for (int j = i+1; j < nr_primes; ++j)
        {
            if(product_prime == prime_list[i] * prime_list[j]){
                pair[0] = i;
                pair[1] = j;
                return;
            }
        }
    }
}

// int in_list(long int * list , int size ,long int num){
//     for (int i = 0; i < size; ++i)
//     {
//         if(list[i] == num)
//             return 1;
//     }
//     return -1;
// }

void sort_list(long int * list, int size){
    for (int i=0 ;i<size; i++){
        for (int j = i+1; j < size; ++j)
        {
            if(list[i]>list[j]){
                long int tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }
}

// String Utils Functions

// int get_string_size(char * str){
//     int size = 0;
//     while(*str != '\0' && *str != '\n')
//     {
//         str++;
//         size++;
//     }
//     return size;
// }

// long int string_to_lint(char* str, int size)
// {
//     long int result=0;
//     int index=size-1;

//     while(index >= 0)
//     {
//         int exponent = (index+1) - size;
//         long int multiplier = pow(10 , abs(exponent));
//         result += multiplier*(str[index]-'0');
//         index--;
//     }

//     return result;
// }