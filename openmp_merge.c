//openmp merge排序
//问题：好像最大的改进就是翻了一倍？需要继续实验

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define RMAX 1000
void Generate_list(int a[], int n);
void Print_list(int a[], int n);
void Merge_sort(int a[],int b[],int n);
void Merge_sort_p(int a[],int b[],int n);
void Merge_sort_split(int a[],int begin,int end,int b[]);
void Merge_sort_split_p(int a[],int begin,int end,int b[]);
void Merge(int a[],int begin,int middle,int end,int b[]);
void Copy(int b[],int begin,int end,int a[]);

int thread_count;

int main(int argc,char* argv[])
{
	double start,finish;
	int* a;
	int* temp;
	int* a_copy;
	int n;
	int i;
	//thread_count=strtol(argv[1],NULL,10);
	thread_count=strtol(argv[1],NULL,10);
	printf("please enter n:\n");
	scanf("%d",&n);
	//printf("thread:%d n:%d\n",thread_count,n);
	a=(int*)malloc(n*sizeof(int));
	temp=(int*)malloc(n*sizeof(int));
	a_copy=(int*)malloc(n*sizeof(int));

	Generate_list(a,n);
	for (i = 0; i < n; i++)
		{
			a_copy[i] = a[i];
		}

	//Print_list(a,n);


	start=omp_get_wtime();
	Merge_sort(a,temp,n);
	finish=omp_get_wtime();
	//Print_list(a,n);
	printf("serial time cost:%e seconds\n",finish-start);
	
	start=omp_get_wtime();
	Merge_sort_p(a_copy,temp,n);
	finish=omp_get_wtime();
	//Print_list(a_copy,n);
	printf("parallel time cost:%e seconds\n",finish-start);

	//Print_list(a,n);
	//printf("time cost:%e seconds\n",finish-start);
	return 0;
}

void Merge_sort(int a[],int b[],int n){
	Merge_sort_split(a,0,n,b);
}

void Merge_sort_split(int a[],int begin,int end,int b[]){
	int middle=(begin+end)/2;
	if(end-begin<2) return;
	Merge_sort_split(a,begin,middle,b);
	Merge_sort_split(a,middle,end,b);
	Merge(a,begin,middle,end,b);
	Copy(b,begin,end,a);
}

void Merge_sort_p(int a[],int b[],int n){
	Merge_sort_split_p(a,0,n,b);
}

void Merge_sort_split_p(int a[],int begin,int end,int b[]){
	int middle=(end+begin)/2;
	if(end-begin<2) return;
#pragma omp parallel num_threads(thread_count)
	{
#pragma omp sections
		{
#pragma omp section
			Merge_sort_split(a,begin,middle,b);
#pragma omp section
			Merge_sort_split(a,middle,end,b);
		}
	}
	Merge(a,begin,middle,end,b);
	Copy(b,begin,end,a);
}

void Merge(int a[],int begin,int middle,int end,int b[])
{
	int i=begin,j=middle;
	int k;
	for(k=begin;k<end;k++)
	{
		if(i<middle&&(j>=end||a[i]<=a[j])){
			b[k]=a[i];
			i++;
		}
		else{
			b[k]=a[j];
			j++;
		}
	}
}

void Copy(int b[],int begin,int end,int a[]){
	int k;
	for(k=begin;k<end;k++)
		a[k]=b[k];
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