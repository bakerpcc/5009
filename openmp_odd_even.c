//openmp odd_even排序
//由于范围定在1-1000，所以如果输入是1000以上，比如我试验到20000，后面每个数字会有比较多重复的地方
//当输入比较小的时候，使用thread反而会比不使用要慢。但实验到1000以上的时候，就会快过串行排序了。
//当输入=20000的时候，使用openmp时间是串行排序的1/2

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define RMAX 1000
void Generate_list(int a[], int n);
void Print_list(int a[], int n);
void odd_even_sort(int a[],int n);
void odd_even_sort_p(int a[],int n);
int thread_count;

int main(int argc,char* argv[])
{
double start,finish;
int* a;
int n;
thread_count=strtol(argv[1],NULL,10);
printf("please enter n:\n");
scanf("%d",&n);
printf("thread:%d n:%d\n",thread_count,n);
a=(int*)malloc(n*sizeof(int));
Generate_list(a,n);
//Print_list(a,n);


start=omp_get_wtime();
odd_even_sort(a,n);
finish=omp_get_wtime();

/*
start=omp_get_wtime();
odd_even_sort_p(a,n);
finish=omp_get_wtime();
*/

Print_list(a,n);
printf("time cost:%e seconds\n",finish-start);
return 0;
}

void Generate_list(int a[], int n) {
   int i;
   srand(1);
   for (i = 0; i < n; i++)
      a[i] = rand() % RMAX;
}  /* Generate_list */

void Print_list(int a[], int n) {
   int i;

   for (i = 0; i < n; i++)
      printf("%d ", a[i]);
   printf("\n\n");
}  /* Print_list */

void odd_even_sort(int a[],int n)
{
	int phase, i, temp;

   for (phase = 0; phase < n; phase++) 
      if (phase % 2 == 0) { /* Even phase */
//#	 pragma omp parallel for num_threads(thread_count)\
		default(none) shared(a,n) private(i,temp)
         for (i = 1; i < n; i += 2) 
            if (a[i-1] > a[i]) {
               temp = a[i];
               a[i] = a[i-1];
               a[i-1] = temp;
            }
      } else { /* Odd phase */
//#	 pragma omp parallel for num_threads(thread_count)\
		default(none) shared(a,n) private(i,temp) 
         for (i = 1; i < n-1; i += 2)
            if (a[i] > a[i+1]) {
               temp = a[i];
               a[i] = a[i+1];
               a[i+1] = temp;
            }
      }
}

void odd_even_sort_p(int a[],int n)
{
	int phase, i, temp;

   for (phase = 0; phase < n; phase++) 
      if (phase % 2 == 0) { /* Even phase */
#	 pragma omp parallel for num_threads(thread_count)\
		default(none) shared(a,n) private(i,temp)
         for (i = 1; i < n; i += 2) 
            if (a[i-1] > a[i]) {
               temp = a[i];
               a[i] = a[i-1];
               a[i-1] = temp;
            }
      } else { /* Odd phase */
#	 pragma omp parallel for num_threads(thread_count)\
		default(none) shared(a,n) private(i,temp) 
         for (i = 1; i < n-1; i += 2)
            if (a[i] > a[i+1]) {
               temp = a[i];
               a[i] = a[i+1];
               a[i+1] = temp;
            }
      }
}