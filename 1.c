#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char command[100];
	char program[100];
	char *subcommand;
	char *perintah[100];
	char *path = "/bin";
	int i = 0, pid = fork();

	while(1)
	{
		printf("EO7 >> ");
		scanf("%[^\n]",command);

		if(strcmp(command,"exit")==0) return 0;

		subcommand = strtok(command," ");
		while(subcommand!=NULL)
		{
			perintah[i] = subcommand;
			subcommand = strtok(NULL," ");
			i++;
		}

		strcpy(program,path);
		strcat(program,perintah[0]);

		for(i=0;i<strlen(program);i++) if(program[i]=='\n') program[i]='\0';

		if(pid==0) execvp(program,perintah);
		else wait(NULL);

		return 0;
	}
}
