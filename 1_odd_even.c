#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int* a;

int read_data();
void odd_even_serial(int a[],int n);
void odd_even_parallel(int a[],int n);
void print_data(int a[],int n);
int thread_count=8;

int main(int argc,char* argv[])

{
	double start,finish;
	//int* a_copy;
	int n;
	
	n=read_data();
	start=omp_get_wtime();
	odd_even_serial(a,n);
	finish=omp_get_wtime();

	printf("serial time cost:%e seconds\n",finish-start);
	//print_data(a,100);

	n=read_data();
	//print_data(a,100);
	start=omp_get_wtime();
	odd_even_parallel(a,n);
	finish=omp_get_wtime();

	//print_data(a,100);
	printf("parallel time cost:%e seconds\n",finish-start);

	//Print_list(a,n);

	//printf("time cost:%e seconds\n",finish-start);
	return 0;
}


void odd_even_serial(int a[], int n) {
   int phase, i, tmp;
   for (phase = 0; phase < n; phase++) {
      if (phase % 2 == 0)
         for (i = 1; i < n; i += 2) {
            if (a[i-1] > a[i]) {
               tmp = a[i-1];
               a[i-1] = a[i];
               a[i] = tmp;
            }
         }
      else
         for (i = 1; i < n-1; i += 2) {
            if (a[i] > a[i+1]) {
               tmp = a[i+1];
               a[i+1] = a[i];
               a[i] = tmp;
            }
         }
   }
} 

void odd_even_parallel(int a[], int n) {
   int phase, i, tmp;
   for (phase = 0; phase < n; phase++) {
      if (phase % 2 == 0)
#        pragma omp parallel for num_threads(thread_count) \
            default(none) shared(a, n) private(i, tmp)
         for (i = 1; i < n; i += 2) {
            if (a[i-1] > a[i]) {
               tmp = a[i-1];
               a[i-1] = a[i];
               a[i] = tmp;
            }
         }
      else
#        pragma omp parallel for num_threads(thread_count) \
            default(none) shared(a, n) private(i, tmp)
         for (i = 1; i < n-1; i += 2) {
            if (a[i] > a[i+1]) {
               tmp = a[i+1];
               a[i+1] = a[i];
               a[i] = tmp;
            }
         }
   }
}  /* Odd_even */


int read_data()
{
	FILE* f;
	int n,i;
	f=fopen("test_20_16384.txt","r");
	if(f==NULL){
		printf("Data file not found.\n");
		return (-1);
	}
	fscanf(f,"%d",&n);
	printf("size of array:%d\n",n);
	a=(int*)malloc(n*sizeof(int));

	for(i=0;i<n;i++){
		fscanf(f,"%d",&a[i]);
//		printf("%d ",a[i]);
	}
	return n;
}


void print_data(int a[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}
