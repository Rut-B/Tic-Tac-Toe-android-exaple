#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <netdb.h>
//#include<math.h>
#define MAX_BUF 256
#define POOL_SIZE 2
#define MAX_NUM_REQUEST 3
#define FILTER 4
#define INTERNAL_ERROR "500.txt"
#define BED_REQUEST "400.txt"
#define NON_IMPLEMENT "501.txt"
#define NOT_FOUND "404.txt"
#define FORBIDDEB "403.txt"
#define MAX_IP_LEN 128
int pow(int x,int y);
int checkPremision(int server );
void printError(char * errorNumber,int fd);
void* handler(void* arg);
int validFilter(char* filterPath);
int ToInt(char* str);
