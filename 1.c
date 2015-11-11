#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>

int execute(char** subcommand,int position);
void signal_handler();
char computername[100];
char directory[100];

int main()
{
	char command[100];
	char *subcommand[20];
	int position=0;

	while(1)
	{
		gethostname(computername,100);
		getcwd(directory,100);

		printf("%s@%s:~%s$ ",getenv("LOGNAME"),computername,directory);

		signal(SIGINT,signal_handler);
                signal(SIGTSTP,signal_handler);

		if(fgets(command,100,stdin)==NULL)
		{
			printf("\n");
			break;
		}

		if(command[strlen(command)-1]=='\n') command[strlen(command)-1]='\0';

		subcommand[position]=strtok(command," ");
		for(position=1;position<20;position++)
		{
			subcommand[position] = strtok(NULL," ");
			if(subcommand[position]==NULL) break;
		}

		if(execute(subcommand,position)==0) break;
	}
	return 0;
}

int execute(char** subcommand,int position)
{
        if(strcmp(subcommand[0],"cd")==0)
        {
                if(subcommand[1]==NULL) fprintf(stderr,"cd: No argument\n");
		else
		{
			if(chdir(subcommand[1])!=0) fprintf(stderr,"cd: No such file or directory\n");
		}
		return 1;
        }
        else
        {
		int bg=0;
		if(strcmp(subcommand[position-1],"&")==0) bg=1;
                pid_t pid = fork();
                if(pid==0)
                {
			if(bg==1) subcommand[position-1]='\0';
			execvp(subcommand[0], subcommand);
                        return 1;
                }
                else if(pid<0)
                {
                        printf("ERROR\n");
                        return 0;
                }
                else
                {
			if(bg==1);
			else
			{
	                        int status;
        	                waitpid(pid,&status,0);
			}
                	return 1;
                }
	}
}

void signal_handler()
{
	fprintf(stderr,"\n%s@%s:~%s$ ",getenv("LOGNAME"),computername,directory);
}
