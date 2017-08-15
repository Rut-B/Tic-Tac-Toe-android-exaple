#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ctype.h>
#include <time.h>
#include<unistd.h>
#include<string.h>
#define RFC1123FMT "%a, %d %b %Y %H:%M:%S GMT"
#define MAX_LEN_TIME 100
#define MAX_URL 120
#define MIN_LEN 8
#define NON_H 0
#define IS_H 1
#define NON_T -1
#define COMMAND_USAGE 1
#define INPUT_ERROR 2
#define MAX_BUF 1024
#define DAYS 0
#define HOURS 1
#define MIN 2

//client to server ex6
//***************************validation
void validationFun(int argc, char**argv, int* header, char* D_time, char* Url, char* path, char* port);
void error_input();
int is_time(char* timeString, char* T_String, char* newTime);
int valid_url(char* Url, char*S_url, char *port);
int validParameter(char* shand_R_Url);
int ToInt(char* str);
char* getTime(int day, int hour, int min);
char*getRequest(int* header,char* D_time,char* Url,char* path,char* port);

//***************************

void main(int argc,char** argv){
	int numberPort;
	int nbytes=0,nbytesRed=0;
	int header;
	char* D_time=malloc(sizeof(char)*MAX_LEN_TIME);
	char* Url=malloc(sizeof(char)*MAX_URL);
	char* path=malloc(sizeof(char)*MAX_URL);
	char* port=malloc(sizeof(char)*MAX_URL);
	char request[MAX_BUF];;
	char buf[MAX_BUF];
	int clientSocket;
	struct hostent * server;
	struct sockaddr_in serv_addr;

	validationFun(argc,argv,&header,D_time,Url,path,port);


	//create socket
	if ((clientSocket = socket(PF_INET, SOCK_STREAM,0))<0){
		perror("socket");
		exit(1);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	//get ip DNS-request.
	numberPort=ToInt(port);
	serv_addr.sin_port = htons(numberPort);

	server = gethostbyname(Url);
	if (server == NULL) {
		perror("ERROR, no such host\n");
		exit(0);
	}

	//connect to server.

	serv_addr.sin_addr.s_addr = ((struct in_addr*)(server->h_addr))->s_addr;

	if (connect(clientSocket,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("connect");
		exit(1);
	}

	strcpy(request,getRequest(&header,D_time,Url,path,port));
	printf("HTTP request =\n%s\nLEN = %d\n", request, (int)strlen(request));

	if((nbytes = write(clientSocket, request, MAX_BUF)) < 0) {
		perror("write");
		exit(1);
	}
	bzero(buf,MAX_BUF);
	nbytes=0;
	while((nbytes = read(clientSocket,buf,MAX_BUF-1))>0)
	{
		nbytesRed+=nbytes;
		printf("%s",buf);
	}
	if (nbytes <0)
	{
		perror("ERROR reading from socket");
		exit(1);
	}

	printf("\nTotal received response bytes: %d\n",(int)nbytesRed);

	free(D_time);
	free(Url);
	free(path);
	free(port);
	close(clientSocket);

}

//************************************************validation 
void validationFun(int argc, char**argv, int* header, char* D_time, char* Url, char* path, char* port) {


	int i = 0, valid_com = 0;
	int place_url = -1;
	*header = NON_H;
	strcpy(D_time, "");
	strcpy(path, "");
	strcpy(Url, "");
	strcpy(port ,"80");

	if (argc > 5 || argc < 2)
		error_input();

	for (i = 1; i < argc; i++)
	{      
		if (place_url == -1)
			strcpy(Url, argv[i]);

		if(valid_url(Url, path, port))
		{
			place_url = i;
			valid_com++;
		}
		else

			if (!(strcmp(argv[i], "-h")) && (*(header) == NON_H))
			{
				*header = IS_H;
				valid_com++;

			}

			else 
				if ((i+1< argc)&&(!strcmp(D_time, "")) && (is_time(argv[i], argv[i + 1], D_time)))
				{
					valid_com++;
					valid_com++;
					i++;

				}


	}
	if ((valid_com != argc - 1)||(place_url == -1))
		error_input();

}

//**********************************************************
int is_time(char* timeString, char* T_String, char*newTime) {

	int flag = 0;
	int i = 0, j = 0;
	int day, hour, min;
	char* res = malloc(sizeof(char)*MAX_LEN_TIME);
	char* helper = malloc(sizeof(char)*MAX_LEN_TIME);

	strcpy(helper, T_String);

	if ((timeString[0] == '-') && (timeString[1] == 'd')&&(strlen(timeString)==2))
		flag = 1;

	if (!flag)
		error_input();

	res = strtok(helper, ":");
	while (1) {

		if (res == NULL)
			break;
		j = 0;

		while (res[j] != '\0')
		{
			if (!isdigit(res[j]))
				error_input();

			j++;
		}

		if (i == DAYS)
			day = ToInt(res);

		if (i == HOURS)
			hour = ToInt(res);

		if (i == MIN)
			min = ToInt(res);
		i++;
		res = strtok(NULL, ":");

	}

	if (i != 3)
		error_input();

	strcpy(newTime, getTime(day, hour, min));
	return 1;
}

//************************************************

char* getTime(int day, int hour, int min) {
	time_t now;
	char *timebuf;
	timebuf = malloc(sizeof(char) * 128);
	struct sockaddr_in serverAddr;
	now = time(NULL);
	now = now - (day * 24 * 3600 + hour * 3600 + min * 60);
	strftime(timebuf, 128, RFC1123FMT, gmtime(&now));
	return timebuf;
}


//************************************************
int ToInt(char* str)
{
	int mult = 1;
	int re = 0;
	int len = strlen(str);
	for (int i = len - 1; i >= 0; i--)
	{       if (!isdigit(str[i]))
		error_input();
	re = re + ((int)str[i] - 48)*mult;
	mult = mult * 10;
	}
	return re;
}

//*************************************************
int valid_url(char* Url, char*path, char *port) {

	int flag = 0;

	char* pointer;
	if (strlen(Url) < MIN_LEN)
		return 0;

	if ((Url[0] == 'h') && (Url[1] == 't') && (Url[2] == 't') && (Url[3] == 'p') && (Url[4] == ':') && (Url[5] == '/') && (Url[6] == '/')&& (Url[7] == 'w') && (Url[8] == 'w')&& (Url[9] == 'w'))
		flag = 1;

	if (!flag)
		return 0;

	char * hand_R_Url = (char *)malloc(sizeof(char)*MAX_URL);

	strcpy(hand_R_Url,strchr(Url, 'w'));

	if(!validParameter(hand_R_Url))
		return 0;



	if(strchr(hand_R_Url, ':'))//there is another port
	{
		strcpy(Url,strtok(hand_R_Url, ":"));



		if((pointer=strtok(NULL, "/"))!=NULL)
			strcpy(port,pointer);
		if((pointer=strtok(NULL, ""))!=NULL)
			strcpy(path,pointer);
	}
	else
	{
		strcpy(Url,strtok(hand_R_Url, "/"));
		if((pointer=strtok(NULL, ""))!=NULL)
			strcpy(path,pointer);
	}
	free(hand_R_Url);
	return 1;
}

//************************************
int validParameter(char * hand_R_Url){
	int i;
	for(i=1;i<strlen(hand_R_Url);i++){
		if((hand_R_Url[i]==hand_R_Url[i-1])&&((hand_R_Url[i]==':')||(hand_R_Url[i]=='/')))
		{
			return 0;
		}

	}

	return 1;
}
//***********************************

void error_input() {
	
	perror("Usage: proxyServer <port> <pool-size> <max-number-of-request> <filter>\n"");
	exit(1);
}

//************************************************

char* getRequest(int* header,char* D_time,char* Url,char* path,char* port){

	char * Reqest=malloc(sizeof(char)*MAX_URL);
	if(!strcmp(port, "80"))//check if port is number;
		ToInt(port);


	if(*header==IS_H)
		strcat(Reqest,"HEAD / ");
	else
		strcat(Reqest,"GET / ");
	if(strcmp(path, ""))//check if port is number;
	{
		strcat(Reqest,path);
	}

	strcat(Reqest,"HTTP/1.0\r\n");
	strcat(Reqest,"Host: ");
	strcat(Reqest,Url);
	strcat(Reqest,"\r\n");
	strcat(Reqest,"Connection: close\r\n");

	if(strcmp(D_time, ""))//check if port is number;
	{strcat(Reqest,"If-Modified-Since: ");
	strcat(Reqest,D_time);
	strcat(Reqest,"\r\n");
	}
	strcat(Reqest,"\r\n");
	return Reqest;
}

//------------------------------------------

