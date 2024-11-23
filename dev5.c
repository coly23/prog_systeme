#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>



int N;             // Nombre de threads
sem_t* bloquer;     // Tableau de semaphores pour sychroniser les threads

void* fonction(void* arg)
{
	int id_thread = *(int*)arg;
	while(1)
	{
		sem_wait(&bloquer[id_thread]);
		
		printf("je suis le thread %d\n", id_thread + 1);
		
		sleep(1);
		
		sem_post(&bloquer[(id_thread + 1) % N]);
		
		
	    	
	}
	pthread_exit(NULL);
}



int main() 
{	
	pthread_t tab[N];
    	int resultat;	
    	
    	printf("Entrez le nombre de threads : ");
    	scanf("%d", &N);
    	
    	if(N <= 0)
    	{
    		printf(" le nombre de threads doit etre superieur à 0.\n");
    		return 1;
    	}
    	
    	bloquer = malloc(N* sizeof(sem_t));
    	
    	if(bloquer == NULL)
    	{
    		printf("Erreur d'allocation memoire.\n");
    		exit(1);
   	}
    	
    	
    	for(int i = 0; i < N; i++)	
    	{
    		resultat = sem_init(&bloquer[i], 0, (i == 0) ? 1 : 0);    //le premier thread est debloqué
    		if(resultat == -1)
    		{
    			perror("Erreur d'initialisation de la semaphore.\n");
    			free (bloquer);
    			return 1;
    		}
    	}
    	
    	int ids_thread[N];
	for(int i = 0; i < N; i++)
	{
	    	ids_thread[i] = i;          //stocker l'identifiant du thread
	    	resultat = pthread_create (&tab[i], NULL, fonction, &ids_thread[i]);
    		if(resultat == -1)
    		{
    			perror("Erreur de lancement du thread.\n");
    			free(bloquer);
    			return 0;
    		}
	    	
	}
    	
    		
    	for(int i = 0; i < N; i++)
    		pthread_join(tab[i], NULL);
    		
    	for(int i = 0; i < N; i++)
    		sem_destroy(&bloquer[i]);
    	free (bloquer);
    		
    	return 0;
}