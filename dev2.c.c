#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


void generer_matrice(int **matrice, int dimension)
{
	for (int i = 0; i < dimension; i++) 
    	{
        	for (int j = 0; j < dimension; j++)
            		matrice[i][j] = rand() % 100; //valeur aléatoire entre 0 et 99
    	}
}

void ecrire_matrice_binaire(char *nom_fichier, int **matrice, int dimension)
{
	FILE *fichier = fopen(nom_fichier, "wb");
	 if (fichier == NULL) 
    	{
        	perror("Erreur d'ouverture du fichier");
        	exit(1);
    	}
    	for (int i = 0; i < dimension; i++) 
    	{
        	for (int j = 0; j < dimension; j++)
            		fwrite(&matrice[i][j], sizeof(int), 1, fichier);  // Écrire un entier à la fois
    	}
    	fclose (fichier);
}

void ecrire_matrice_texte(char *nom_fichier, int **matrice, int dimension)
{
	FILE *fichier = fopen(nom_fichier, "w");
	 if (fichier == NULL) 
    	{
        	perror("Erreur d'ouverture du fichier");
        	exit(1);
    	}
    	for(int i = 0; i < dimension; i++)
    	{
    		for(int j = 0; j < dimension; j++)
    			fprintf(fichier, "%d\t", matrice[i][j]);
    		fprintf(fichier, "\n");
    	}
    	fclose(fichier);
}

void lire_matrice_binaire(char *nom_fichier, int dimension)
{
	FILE *fichier = fopen(nom_fichier, "rb");
	 if (fichier == NULL) 
    	{
        	perror("Erreur d'ouverture du fichier");
        	exit(1);
    	}
    	int valeur;
    	for(int i = 0; i < dimension; i++)
    	{
    		for(int j = 0; j < dimension; j++)
    		{
    			fread(&valeur, sizeof(int), 1, fichier);  // Lire un entier à la fois
    			printf("%d\t", valeur);
    		}
    		printf("\n");
    	}
    	fclose(fichier);
}


void lire_matrice_texte(char *nom_fichier, int dimension)
{
	FILE *fichier = fopen(nom_fichier, "r");
	 if (fichier == NULL) 
    	{
        	perror("Erreur d'ouverture du fichier");
        	exit(1);
    	}
    	int valeur;
    	for(int i = 0; i < dimension; i++)
    	{
    		for(int j = 0; j < dimension; j++)
    		{
    			fscanf(fichier, "%d", &valeur);
    			printf("%d\t", valeur);
    		}
    		printf("\n");
    	}
    	fclose(fichier);
}



int main(int argc, char *argv[])
{
	int dimension = 0;
	char *nom_fichier = NULL;
	int option_creation = 0, option_affichage = 0, option_binaire = 1;
	
	int opt;
	
	while((opt = getopt (argc, argv, "cad:f:bt"))!= -1)
	{
		switch (opt)
		{
			case 'c':
				option_creation = 1;
				break;
			case 'a':
				option_affichage = 1;
				break;
			case 'd':
				dimension = atoi (optarg);
				break;
			case 'b':
				option_binaire = 1;
				break;
			case 't' :
				option_binaire = 0;
				break;
			case 'f':
				nom_fichier = optarg;
				break;
			default:
				fprintf (stderr, "Utilisation: %s [-c] [-a] [-d dimension] [-b | -t] [-f nom_fichier]\n", argv[0]);
				exit(1);
		}
	}
	
	if(dimension <= 0 || nom_fichier == NULL)
	{
		printf("Vous n'avez pas donner la dimension de la matrice et le nom du fichier.\n");
		exit(1);
	}
	
	int **matrice = malloc (dimension * sizeof(int*));
	if(matrice == NULL)
	{
		perror("Erreur d'allocation");
		exit(1);
	}
	
	for(int i = 0; i < dimension; i++)
	{
		matrice[i] = malloc (dimension * sizeof(int));
		if(matrice[i] == NULL)
		{
			perror("Erreur d'allocation");
			exit(1);
		}
	}
		
		
	if (option_creation)
	{
		generer_matrice(matrice, dimension);
		if(option_binaire)
		{
			ecrire_matrice_binaire(nom_fichier, matrice, dimension);
			printf("\n Matrice chargée depuis le fichier binaire :\n");
		}
			
		else
		{
			ecrire_matrice_texte(nom_fichier, matrice, dimension);
			printf("\n Matrice chargée depuis le fichier texte :\n");
		}
	}
	
	if (option_affichage)
	{
		if(option_binaire)
			lire_matrice_binaire(nom_fichier, dimension);
		else
			lire_matrice_texte(nom_fichier, dimension);
			
		//afficher_matrice(matrice, dimension);
	}
	
	for (int i = 0; i < dimension; i++)
		free (matrice[i]);
	free (matrice);
	
	return 0;
}
	
	