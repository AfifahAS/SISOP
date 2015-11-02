#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int prima=0;

void *Hitung_Prima(void *n)
{
	int counter=0,i,j;
	int *a=(int *)n;
	for(i=2;i<*a;i++)
	{
		for(j=1;j<=i;j++) if(i%j==0) counter++;
		if(counter==2)
		{
			printf("%d ",i);
			prima++;
		}
		counter=0;
	}
	printf("\n");
}

void main()
{
	int N;
	scanf("%d",&N);
	pthread_t Bilangan_Prima;
	pthread_create(&Bilangan_Prima, NULL, Hitung_Prima, (void *)&N);
	pthread_join(Bilangan_Prima, NULL);
	printf("Jumlah bilangan prima kurang dari %d adalah %d\n",N,prima);
}
