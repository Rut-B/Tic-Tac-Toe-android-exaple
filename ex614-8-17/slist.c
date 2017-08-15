#include "slist.h"
int numberFilter;
int mask[MAX_IP_LEN];
int ipFilter[MAX_IP_LEN];
//******************************************
int checkPremision(int server ){
	int i=0;
	for (;i<numberFilter;i++)
	{
		if((server&mask[i])==ipFilter[i])//according to ip in the list if the ip in forbidden subnet  
		return 0;
	}
return 1;	
}
//******************************************
void printError(char * errorNumber,int fd){
	FILE * f=fopen(errorNumber,"r");
	char buffer[MAX_BUF];
	if(f==NULL)
	{
		perror("fopen failed\n");
		exit(1);
	}
	
	int nbytes;
	while((nbytes = fscanf(f,buffer,MAX_BUF-1))!=EOF)
	{
		nbytes=write(fd,buffer,MAX_BUF-1);
	}
	fclose(f);
}
//********************************************
int pow(int x,int y){
int i=0;
int number=1;
for(i=0;i<y;i++)
   number=number*x;
return number;

}
//******************************************
void* handler(void* arg){
	
    char buffer[MAX_BUF];
    struct hostent *serverForClient;
    struct sockaddr_in serv_addr;
    int clientSocket,nbytes;
    char tmpArg[MAX_BUF];
    char method[128];
    int portno=80;
	
    int *fd=(int*)arg;//fd socket of client	
    bzero(buffer,MAX_BUF);	
    nbytes = read(*fd,buffer,MAX_BUF-1);//read from client socket to buffer
    if (nbytes < 0){
         printError(INTERNAL_ERROR,*fd);
        }
    strcpy(tmpArg,buffer);
    if((strcmp(strtok(tmpArg,"/")),"GET")!=0)
    	printError(NON_IMPLEMENT,*fd);
	
    strtok(NULL," ");
    strcpy(method,strtok(NULL,"\r\n"));
	
    if((strcmp(method,"HTTP/1.0")!=0)&&(strcmp(method,"HTTP/1.1")!=0))//if the version is 1.0 or 1.1
    	printError(BED_REQUEST,*fd);
		
    strtok(NULL,":");
    strcpy(method,strtok(NULL,"\r\n"));//get host

    if((serverForClient=gethostbyname(method))==NULL)
     printError(NOT_FOUND,*fd);
 
    if(!checkPremision((int)(serverForClient->h_addr)));//if this int
		printError(FORBIDDEB,*fd);
		
    if ((clientSocket = socket(PF_INET, SOCK_STREAM,0))<0){//now server like client-
    	printError(INTERNAL_ERROR,*fd);
    	}
    	bzero((char *) &serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(portno);
	if (connect(clientSocket,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
	printError(INTERNAL_ERROR,*fd);
	}
	if((nbytes = write(clientSocket, buffer, MAX_BUF)) < 0) {//write to 
		printError(INTERNAL_ERROR,*fd);
	}
	bzero(buffer,MAX_BUF);
	nbytes=0;
	while((nbytes = read(clientSocket,buffer,MAX_BUF-1))>0)
	{
		nbytes=write(*fd, buffer, MAX_BUF);
	}
	if (nbytes <0)
	{
		printError(INTERNAL_ERROR,*fd);
	}
    close(clientSocket);
}

//*********************************************int validFilter(char* filterPath){
 int validFilter(char* filterPath){
	int mask_i, ip_filter_i,partFilter,ipBinar=0,numberMask,numberLoop=0,n=0;
	FILE*  fd;
	char subnet_i[MAX_IP_LEN];

	if((fd=fopen(filterPath,"r"))==NULL)
	{
	  return 0;
	}

	while(fscanf(fd,"%s",subnet_i)!=EOF)
	 {
	     char * tempFilter=(char*)malloc(sizeof(char)*strlen(subnet_i));
	     strcpy(tempFilter,subnet_i);
	     char* point=strtok(tempFilter,"./");
	     while(point!=NULL)
	       {
	             partFilter=ToInt(point);
	             if(partFilter>255 || partFilter<0)
	             {
		            exit(1);
		            free(tempFilter);
	             }
	             if(numberLoop<4)
	              {
	              ipBinar=ipBinar<<8;
	              ipBinar+=partFilter;
	              }
	              point=strtok(NULL,"./\n");
	              numberLoop++;
	       }
	       strcpy(tempFilter,subnet_i);
	       point=strtok(tempFilter,"/");
	       point=strtok(NULL,"\n");
	       if(point==NULL)
	       {
	         	 return 0;
                free(tempFilter);
	       }
	       numberMask=ToInt(point);
           if(numberMask>32 || numberMask<0)
	       {
	       	return 0;
	        free(tempFilter);
	       }
	       mask_i = pow(2,numberMask)-1;
	       mask_i=mask_i<<(32-numberMask);
	       ip_filter_i=ipBinar&mask_i;
	       mask[n]=mask_i;
           ipFilter[n]=ip_filter_i;
	       n++;
	       ipBinar=0;
	       numberLoop=0;
	       printf("mask_i = %x ip_filter_i= %x \n",mask_i,ip_filter_i);
	       free(tempFilter);
    }

 numberFilter=n;
 fclose(fd);
 return 1;

}

//***************************************************
int ToInt(char* str)
{
	int mult = 1;
	int re = 0;
	int len = strlen(str);
	for (int i = len - 1; i >= 0; i--)
	{     
		if (!isdigit(str[i]))
	    return	-1;
		re = re + ((int)str[i] - 48)*mult;
		mult = mult * 10;
	}
	return re;
}

	


