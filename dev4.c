#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define N 10  // Valeur maximale pour +N et -N

int valeur = 0;         
sem_t sem_thread1;      
sem_t sem_thread2;   

void* thread1(void* arg)
{
	sem_wait(&sem_thread1);  // Attendre son tour
    	for (int i = 1; i <= N; i++) 
        	printf("Thread 1: %d\n", i);
        	
    	sem_post(&sem_thread2);  // Libérer le sémaphore pour le thread 2	
    	
    	pthread_exit(NULL);
}

void* thread2(void* arg) 
{
	sem_wait(&sem_thread2);  // Attendre son tour
	for (int i = 1; i <= N; i++) 
	        printf("Thread 2: %d\n", -i);
	        
	sem_post(&sem_thread1);  // Libérer le sémaphore pour le thread 1
	
	pthread_exit(NULL);
}

int main() 
{
    	pthread_t t1, t2;
    	int resultat;

    	// Initialisation des sémaphores
    	resultat = sem_init(&sem_thread1, 0, 1);
    	if(resultat == -1)
    	{
    		printf("Erreur d'initialisation de la semaphore.\n");
    		return 0;
    	}
    	resultat = sem_init(&sem_thread2, 0, 0);
	if(resultat == -1)
    	{
    		printf("Erreur d'initialisation de la semaphore.\n");
    		return 0;
    	}
    	// Création des threads
    	resultat = pthread_create(&t1, NULL, thread1, NULL);
    	if(resultat == -1)
    	{
    		printf("Erreur de lancement du thread.\n");
    		return 0;
    	}
    	resultat = pthread_create(&t2, NULL, thread2, NULL);
    	if(resultat == -1)
    	{
    		printf("Erreur de lancement du thread.\n");
    		return 0;
    	}

    	// Attente des threads
    	pthread_join(t1, NULL);
    	pthread_join(t2, NULL);

    

    	return 0;
}