#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct copy
{
	struct copy *in, *out;
} copy;

void *jalan1 (void **args)
{
	copy *file=(copy *)*args;
	char line[100];
	while(fgets(line, 100, (*file)->in) != NULL)
	{
		fputs(line, (*file)->out);
	}

}

int main()
{
	pthread_t t1, t2;
	copy *step1, step2;
	step1->in = fopen("file.txt", "r");
	step2->out = fopen("file.txt", "r+");
	pthread_create(&t1, NULL, jalan1, (void *)&step1);

}

/*
void copycontent(FILE **in, FILE **out)
{
	printf("masuk\n");
	char line[100];
	while(fgets(line,100,*in) != NULL)
	{
		puts(line);
		fputs(line,*out);
	}
}

int main()
{
	FILE *in, *out, *out2;
	in = fopen("file.txt", "r");
	out = fopen("salinan1.txt", "r+");
	copycontent(&in, &out);

	out = fopen("salinan1.txt", "r+");
	out2 = fopen("salinan2.txt", "r+");
	copycontent(&out, &out2);

	fclose(in);
	fclose(out);
	
	return 0;
}*/
