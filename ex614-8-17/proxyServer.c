#include <string.h>
#include "threadpool.h"
#define PORT 1
#include "slist.h"
//*******************************
int main(int argc,char** argv){
	int i=0;
	int sockfd, newsockfd;
        struct sockaddr_in serv_addr;
        int n;
	if(argc!=5)
	{
		perror("Usage: proxyServer <port> <pool-size> <max-number-of-request> <filter>\n");
		exit(1);
	}
	int port=ToInt(argv[PORT]);
	int pool_size=ToInt(argv[POOL_SIZE]);
	int number_of_request =ToInt(argv[MAX_NUM_REQUEST]);
	
	int flagValid=validFilter(argv[FILTER]);
	/*sockfd = socket(PF_INET,SOCK_STREAM,0);
	if (sockfd < 0)
	{
	perror("socket");
	exit(1);
	}
	if(flagValid==0)
		printError(INTERNAL_ERROR,sockfd);
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = 0;
	if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
	{
	perror("bind");
	exit(1);
	}

	listen(sockfd,1);//? if there is 1 listener

	threadpool* p=create_threadpool(pool_size);
	if(p==NULL){
	 perror("create_threadpool");
	}

	for(i=0;i<number_of_request;i++)	
	{
		newsockfd = accept(sockfd, NULL, NULL);
		if(newsockfd<0){
			perror("accept");
			destroy_threadpool(p);
			exit(1);
		}
		
		dispatch(p,(dispatch_fn)handler,(void*)(&newsockfd));
		
	}

        close(sockfd);
	destroy_threadpool(p);	
	*/
	
}






