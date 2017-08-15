#include<stdio.h>
#include<stdlib.h>
#include"threadpool.h"
//*********************************************************
threadpool* create_threadpool(int num_threads_in_pool){
	int i=0;
	if(num_threads_in_pool<=0||num_threads_in_pool>MAXT_IN_POOL||num_threads_in_pool<0)
	{
		perror("The number of threads is illegale!\n");
		exit(NULL);
	}

	threadpool*newPool=(threadpool*)malloc(sizeof(threadpool));//create pool
	if (newPool == NULL) {
		perror("error:malloc\n");
		exit(NULL);
	}

	newPool->num_threads=num_threads_in_pool;
	newPool->qsize=0;
	newPool->qhead=NULL;
	newPool->qtail=NULL;
	newPool->shutdown=0;
	newPool->dont_accept=0;
	newPool->threads=(pthread_t*)malloc(sizeof(pthread_t)*num_threads_in_pool);
	if (newPool->threads == NULL) {
		perror("error:malloc\n");
		exit(NULL);
	}

	if(pthread_mutex_init(&(newPool->qlock), NULL)){
		perror("erroe:pthread_mutex_init\n");
		exit(NULL);
	}
	if(pthread_cond_init(&(newPool->q_empty), NULL)){
		perror("erroe:pthread_cond_init\n");
		exit(NULL);
	}
	if(pthread_cond_init(&(newPool->q_not_empty), NULL)){
		perror("erroe:pthread_cond_init\n");
		exit(NULL);
	}
	for(;i<num_threads_in_pool;i++){
		if(pthread_create(&(newPool->threads[i]),NULL,do_work,newPool))
		{
			perror("erroe:pthread_create\n");
			exit(NULL);
		}
	}

	return newPool;
}
//******************************************************************
void dispatch(threadpool* from_me, dispatch_fn dispatch_to_here, void *arg){//add job
	int res;
	if(from_me==NULL){
		perror("ERROR! from me is NULL");
		return;
	}
	work_t*newJob=malloc(sizeof(work_t));
	if(newJob==NULL){
		perror("erroe:malloc");
		return;
	}
	if(from_me->dont_accept){
		free(newJob);
		return;
	}
	newJob->arg=arg;
	newJob->routine=dispatch_to_here;
	newJob->next=NULL;
	res=pthread_mutex_lock(&(from_me->qlock));
	if(res)
	{ 
		perror("erroe:pthread_mutex_lock");
		free(newJob);
		return;
	}
	if(from_me->qsize==0)
	{
		from_me->qtail=newJob;
		from_me->qhead=newJob;
	}
	else
		from_me->qtail->next=newJob;

	from_me->qtail=newJob;
	from_me->qsize++;
	res=pthread_cond_signal(&(from_me->q_not_empty));
	if(res)
	{ 
		perror("erroe:pthread_cond_signal");
		free(newJob);
		return;
	}
	res=pthread_mutex_unlock(&(from_me->qlock));

	if(res)
	{ 
		perror("erroe:pthread_mutex_unlock");
		free(newJob);
		return;
	}

}
//**********************************************
void* do_work(void* p){//function to thread
	int res;
	threadpool*pool=(threadpool*)p;
	work_t*myJob;
	while(1){
		if(pool->shutdown)
		{
			pthread_exit(NULL);
		}
		pthread_mutex_lock(&(pool->qlock));
		while (pool->qsize==0)
		{
			if(pool->shutdown)
			{
				pthread_mutex_unlock(&(pool->qlock));
				pthread_exit(NULL);
			}


			pthread_cond_wait(&(pool->q_not_empty),&(pool->qlock));
		}



		myJob=pool->qhead;
		pool->qsize--;
		pool->qhead=pool->qhead->next;
		if((pool->qsize==0)&&(pool->dont_accept))
		{
			pthread_cond_signal(&(pool->q_empty));
		}
		res=pthread_mutex_unlock(&(pool->qlock));
		if(res)
		{ 
			perror("erroe:pthread_mutex_unlock");
			free(myJob);
			return;
		}
		myJob->routine(myJob->arg); 
		free(myJob);
	}

}
//*************************************
void destroy_threadpool(threadpool* destroyme){//destroy pool
	int i=0;
	if(destroyme==NULL){
		perror("the destroyme is NULL");
		return;
	}
	destroyme->dont_accept=1;
	pthread_mutex_lock(&(destroyme->qlock));
	while(destroyme->qsize)
		pthread_cond_wait(&(destroyme->q_empty),&(destroyme->qlock));

	destroyme->shutdown=1;
	pthread_cond_broadcast(&(destroyme->q_not_empty));
	pthread_cond_broadcast(&(destroyme->q_empty));
	pthread_mutex_unlock(&(destroyme->qlock));
	for(;i<destroyme->num_threads;i++) {
		pthread_join(destroyme->threads[i],NULL);
	}
	pthread_cond_destroy(&(destroyme->q_empty));
	pthread_cond_destroy(&(destroyme->q_not_empty));
	pthread_mutex_destroy(&(destroyme->qlock));
	free(destroyme->threads);
	free(destroyme);
}




