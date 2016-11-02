#include<stdio.h>
#include<string.h>
#include<omp.h>

int partition1(int s[],int l,int r)
{
	int i,j,x;
	if(l<r)
	{
		i=l;
		j=r;
		x=s[i];
		while(i<j){
			while(i<j&&s[j]>x)
				j--;
			if(i<j)
				s[i++]=s[j];
			while(i<j&&s[i]<x)
				i++;
			if(i<j)
				s[j--]=s[i];
		}
		s[i]=x;
	}
	return i;
}

void quick_sort1(int s[],int l,int r)
{
	int p;
	if(l<r){
		p=partition1(s,l,r);
		#pragma omp parallel 
		{
			#pragma omp sections nowait
			{
				#pragma omp section //section
				quick_sort1(s,l,p-1);
				#pragma omp section //section
				quick_sort1(s,p+1,r);
			}
		}
	}
}


void print_2(int x[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d ",x[i]);
	}
	printf("\n");
}

int main()
{
	int a[10]={7,5,12,6,9,123,969,22,1233,13};
    int l = 0;  
    int r = 9;  
    quick_sort1(a,l,r);  
	print_2(a,10);
	return 0;
}
