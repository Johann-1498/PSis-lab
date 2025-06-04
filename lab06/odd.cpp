/* File:    odd_even.c
 *
 * Purpose: Use odd-even transposition sort to sort a list of ints.
 *
 * Compile: gcc -g -Wall -o odd_even odd_even.c
 * Run:     odd_even <n> <g|i>
 *             n:   number of elements in list
 *            'g':  generate list using a random number generator
 *            'i':  user input list
 *
 * Input:   list (optional)
 * Output:  sorted list
 *
 */
#include <stdio.h>
#include <stdlib.h>

/* Keys in the random list in the range 0 <= key < RMAX */
const int RMAX = 100;

void Get_args(int argc, char* argv[], int* n_p, char* g_i_p);
void Generate_list(int a[], int n);
void Print_list(int a[], int n, const char* title);
void Usage(const char* prog_name);
void Read_list(int a[], int n);
void Odd_even_sort(int a[], int n);

/*-----------------------------------------------------------------*/
/* Function:  main
 * Purpose:   Get command line arguments, generate or read list,
 *            sort the list, and print the sorted list.
 * In args:   argc, argv
 * Out args:  none
 */   


int main(int argc, char* argv[]) {
   /* Declare variables */
   int  n;
   char g_i;
   int* a;

   /* Get command line arguments */
   Get_args(argc, argv, &n, &g_i);
   a = (int*) malloc(n*sizeof(int));
   /* Generate or read list based on command line argument
    * 'g' for generate, 'i' for input.
    * If 'g', generate a random list of integers.
    * If 'i', read integers from standard input.
   */
   if (g_i == 'g') {
      Generate_list(a, n);
      Print_list(a, n, "Before sort");
   } else {
      Read_list(a, n);
   }

   Odd_even_sort(a, n);

   Print_list(a, n, "After sort");
   
   free(a);
   return 0;
}  /* main */
/*-----------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Summary of how to run program
 * In args:   prog_name
 * Out args:  none
 */
void Usage(const char* prog_name) {
   /* Print usage message

    */

   fprintf(stderr, "usage:   %s <n> <g|i>\n", prog_name);
   fprintf(stderr, "   n:   number of elements in list\n");
   fprintf(stderr, "  'g':  generate list using a random number generator\n");
   fprintf(stderr, "  'i':  user input list\n");
}  /* Usage */
/*-----------------------------------------------------------------
 * Function:  Get_args
 * Purpose:   Get and check command line arguments
 * In args:   argc, argv
 * Out args:  n_p, g_i_p
 */
void Get_args(int argc, char* argv[], int* n_p, char* g_i_p) {
   /* Check command line arguments */
   if (argc != 3 ) {
      Usage(argv[0]);
      exit(0);
   }
   /* Check that n is a positive integer and g_i is 'g' or 'i' */
   *n_p = atoi(argv[1]);
   *g_i_p = argv[2][0];

   /* Validate n and g_i */
   if (*n_p <= 0 || (*g_i_p != 'g' && *g_i_p != 'i') ) {
      Usage(argv[0]);
      exit(0);
   }
}  /* Get_args */


/*-----------------------------------------------------------------
 * Function:  Generate_list
 * Purpose:   Use random number generator to generate list elements
 * In args:   n
 * Out args:  a
 */
void Generate_list(int a[], int n) {
   
   /* Generate a list of n random integers in the range 0 to RMAX-1 */
   int i;
   srand(0);
   for (i = 0; i < n; i++)
      a[i] = rand() % RMAX;
}  /* Generate_list */

/*-----------------------------------------------------------------
 * Function:  Print_list
 * Purpose:   Print the elements in the list
 * In args:   a, n
 */
void Print_list(int a[], int n, const char* title) {
   
   /* Print the elements of the list with a title */
   int i;
   printf("%s:\n", title);
   for (i = 0; i < n; i++)
      printf("%d ", a[i]);
   printf("\n\n");
}  /* Print_list */


/*-----------------------------------------------------------------
 * Function:  Read_list
 * Purpose:   Read elements of list from stdin
 * In args:   n
 * Out args:  a
 */
void Read_list(int a[], int n) {
   
   /* Read n integers from standard input into the array a */
   int i;
   printf("Please enter the elements of the list\n");
   for (i = 0; i < n; i++)
      scanf("%d", &a[i]);
}  /* Read_list */

/*-----------------------------------------------------------------
 * Function:     Odd_even_sort
 * Purpose:      Sort list using odd-even transposition sort
 * In args:      n
 * In/out args:  a
 */
void Odd_even_sort(
      int  a[]  /* in/out */, 
      int  n    /* in     */) {
   /*
   
      * Sort the list a using odd-even transposition sort.
      * The algorithm works by repeatedly performing two phases:
      * 1. In the even phase, compare and swap adjacent elements at even indices.
      * 2. In the odd phase, compare and swap adjacent elements at odd indices.
      * This process is repeated until the list is sorted.
   */
   int phase, i, temp;

   for (phase = 0; phase < n; phase++) 
      if (phase % 2 == 0) { /* Even phase */
         for (i = 1; i < n; i += 2) 
            if (a[i-1] > a[i]) {
               temp = a[i];
               a[i] = a[i-1];
               a[i-1] = temp;
            }
      } else { /* Odd phase */
         for (i = 1; i < n-1; i += 2)
            if (a[i] > a[i+1]) {
               temp = a[i];
               a[i] = a[i+1];
               a[i+1] = temp;
            }
      }
}  /* Odd_even_sort */