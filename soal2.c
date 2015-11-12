#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int prima=0;
int array[10000];
int array2[10000];
int indeks=0;

void *Hitung_Prima(void *i)
{
	int j;
	indeks++;
	array[indeks]=*(int *)i;
	array2[indeks]=0;
	for(j=1;j<=array[indeks];j++) if(array[indeks]%j==0) array2[indeks]++;
	if(array2[indeks]==2) prima++;
}

void main()
{
	int N,i;
	scanf("%d",&N);
	pthread_t Bilangan_Prima;
	for(i=0;i<N;i++)
	{
		pthread_create(&Bilangan_Prima, NULL, Hitung_Prima, (void *)&i);
	}
	for(i=0;i<N;i++)
	{
		pthread_join(Bilangan_Prima, NULL);
	}
	printf("Jumlah bilangan prima kurang dari %d adalah %d\n",N,prima);
}
