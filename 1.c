#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>

int execute(char** subcommand);
void signal_handler(int signum);

int main()
{
	char command[100];
	char *subcommand[20];
	int position;

	while(1)
	{
		printf("E07>> ");

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

		if(execute(subcommand)==0) break;
	}
	return 0;
}

int execute(char** subcommand)
{
        if(strcmp(subcommand[0],"cd")==0)
        {
                if(subcommand[1]==NULL) printf("No argument\n");
		else if(chdir(subcommand[1])) fprintf(stderr,"\n");
                else chdir(subcommand[1]);
		return 0;
        }
        else
        {
                pid_t pid = fork();
                if(pid==0)
                {
                        execvp(subcommand[0], subcommand);
                        return 0;
                }
                else if(pid<0)
                {
                        printf("ERROR\n");
                        return 1;
                }
                else
                {
                        if(strcmp(subcommand[2],"&")==0);
                        else
                        {
                                int status;
                                waitpid(pid,&status,0);
                        }
                        return 1;
                }
	}
}

void signal_handler(int signum)
{
	fprintf(stderr,"\nE07>> ");
}
