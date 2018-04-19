#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>   
#include <sys/wait.h>  
void sig_handler(int sig){
	if(sig==SIGALRM)
	{
		exit(0);
	}
}
void split(char arr[][9], char *str, const char *del) {
	int i=0;
	char *s = strtok(str, del);
	while(s != NULL) {
     		strcpy(arr[i++], s);
     		s = strtok(NULL, del);
 	}
}
int chartoint(char arr[]){
	int ans=0;
	int len=strlen(arr);
	for(int a=0;a<len;a++){
		ans*=10;
		ans+=(int)arr[a]-48;
	}
	return ans;
}
/*int stop=0;
void sig_handler(int sig){
	stop=1;
}*/
int main(int argc, char *argv[]){
	/*if(strcmp(argv[2],"FCFS")==0){
		printf("The policy is FCFS.\n");
	}
	else if(strcmp(argv[2],"RR")==0){}
		printf("The policy is RR.\n");
	}
	else{
		printf("Wrong policy.\n");
		return -1;
	}*/
	FILE *fp;
	char temp[255];
	fp=fopen(argv[1],"r");
	char Arrival_time[9][3];
	char Command[9][255];
	char Dul_cmd[9][255];
	char token[9][6][9];
	char Duration[9][3];
	int i=0;
	char *p;
	char delim[]="\t";
	char delim2[]=" ";
	if(fp==NULL){
		printf("File open failed!\n");
	}
	while(fgets(temp,300,fp)){
		//printf("Job %d:",i+1);
		strcpy(Arrival_time[i],strtok(temp,delim));
		//printf("Arrival time: %s\t",Arrival_time[i]);
		strcpy(Command[i],strtok(NULL,delim));
		//printf("Command: %s\t",Command[i]);
		for(int a=0;a<9;a++){
                	strcpy(Dul_cmd[a],Command[a]);
	        }
		strcpy(Duration[i],strtok(NULL,"\n"));
		//printf("Duration: %s",Duration[i]);
		int times=1;
		p=Command[i];
		while(*p!='\0'){
			if(*p==' '){
				times++;
			}
			p++;
		}
		split(token[i],Dul_cmd[i],delim2);
		/*for(int a=0;a<times;a++){
			if(token[i][a]!=NULL){
				printf("Token %d: %s\n",a+1,token[i][a]);
			}
		}*/
		i=i+1;
	}
	int job;
	int dur_time=0;
	for(int a=0;a<6;a++){
		job=fork();
		if(job!=0){
			wait(NULL);
			dur_time+=chartoint(Duration[a]);
		}
	    else{
			alarm(chartoint(Duration[a]));
			signal(SIGALRM,sig_handler);
			printf("%d sec: Job %d\n",dur_time,a+1);
			if(strcmp(token[a][0],"./timer")==0){
				printf("Command %d: %s\n",a+1,Command[a]);
				execlp(token[a][0],token[a][1],NULL);
			}
			else if(strcmp(token[a][0],"./while1")==0){
				printf("Command %d: %s\n",a+1,Command[a]);
				execlp(token[a][0],"",NULL);
			}
			else{
				printf("Command %d: %s\n",a+1,Command[a]);
				printf("%s %s %s\n",token[a][0],token[a][1],token[a][2]);
				execlp("ls","-R","/",NULL);
			}
			
        }
		//kill(job,SIGTERM);
	}
	/*int at;
	int jobnum=1;
	int time=0;
	//signal(SIGINT,sig_handler);
	for(int b=0;b<6;b++){
		printf("%d sec: Job %d run\n",time,jobnum);
		for(int a=0;a<chartoint(Duration[jobnum-1]);a++){
			sleep(1);
			time++;
		}
		jobnum++;
	}*/
	fclose(fp);
	return 0;
}
