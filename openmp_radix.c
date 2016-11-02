#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <omp.h>

#define DIGITS_AMOUNT 	10    /* number of all possible keys (bucket's size) */
int tenPowers[10] = {
	1,		10,		100,
	1000,		10000,		100000,
	1000000,	10000000,	100000000,
	1000000000,
};

int p(int exp)
{
	return tenPowers[exp];
}

void radixsort_serial(int *input_array,int input_array_size,int max_digits_size)
{
	int digit;
	int f,i,j;
	double start_time;

	//start_time=omp_get_wtime();

	int *tmp=(int*)calloc(input_array_size,sizeof(int));

	int shared_buckets[100][DIGITS_AMOUNT];
	for(j=0;j<max_digits_size;j++)
		for (f=0;f<DIGITS_AMOUNT;f++)
		{
			shared_buckets[j][f]=0;
		}

	for(i=0;i<input_array_size;i++){
		for(j=0;j<max_digits_size;j++){
			digit=p(j);
			f=input_array[i]/digit%DIGITS_AMOUNT;
			shared_buckets[j][f]++;
		}
	}

	for(j=0;j<max_digits_size;j++){
		digit=p(j);
		for(i=input_array_size;i>=0;i--){
			int unit=input_array[i]/digit%DIGITS_AMOUNT;
			int pos=--shared_buckets[j][unit];
			tmp[pos]=input_array[i];
		}

		for(i=0;i<input_array_size;i++)
			input_array[i]=tmp[i];
	}
}

int main(int argc,char **argv){
	int i,*input,num_of_values=1000,max_value=0,tmp_value=0;
	int value_length=5,max_digits_size=0;
	double start_time;
	char str[10]={0};
	int debug=0;
	char layout[80];

	if(argc>=2){
		num_of_values=strtoul(argv[1], NULL, 10);
		if (num_of_values < 0 || num_of_values > 2000)
			num_of_values = 1000;
	}
	if (argc >= 3) {
		value_length = atoi(argv[2]);
		if (value_length < 0 || value_length > 10 )
			value_length = 5;
	}
	/*
	if (argc >= 4) {
		int tmp_debug;
		if ((tmp_debug=atoi(argv[3]))>0) {
			debug=tmp_debug;
		}
	}*/
	input=(int *)calloc(num_of_values,sizeof(int));
	for(i=0;i<value_length;i++)
		str[i]='9';
	srand(time(NULL));
	for(i=0;i<num_of_values;i++){
		input[i]=rand()%strtoul(str,NULL,10)+1;
		if(max_value<input[i])
			max_value=input[i];
	}
	tmp_value=max_value;
	while((tmp_value/=10)>0)
		max_digits_size++;
	for (i=0; i<num_of_values; i++)
			printf(layout, input[i]);
	radixsort_serial(input, num_of_values, max_digits_size);
	for (i=0; i<num_of_values; i++)
			printf(layout, input[i]);
}
