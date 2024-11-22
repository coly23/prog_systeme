#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour découper un fichier en plusieurs parties
void split(const char *nom_fichier, size_t taille_partie) 
{
	// Ouvrir le fichier en mode lecture binaire
	FILE *fichier_entree = fopen(nom_fichier, "rb");
	if (fichier_entree == NULL) 
	{
		perror("Erreur lors de l'ouverture du fichier");
		exit(1);
	}

	char buffer[1024];  // Tampon pour lire les données
	size_t octets_lus, numero_partie = 0;
	char nom_partie[256];  // Nom du fichier de sortie pour chaque partie

	// Boucle tant qu'on n'est pas à la fin du fichier
	while (!feof(fichier_entree)) 
	{
		// Générer un nom pour chaque partie
		snprintf(nom_partie, sizeof(nom_partie), "%s.part%zu", nom_fichier, numero_partie + 1);

		// Ouvrir un nouveau fichier pour écrire la partie
		FILE *fichier_sortie = fopen(nom_partie, "wb");
		if (fichier_sortie == NULL) 
		{
			perror("Erreur lors de la création de la partie");
			fclose(fichier_entree);
			exit(1);
		}

		size_t octets_ecrits = 0;

		// Écrire dans le fichier partie tant qu'on n'a pas atteint la taille souhaitée
		while (octets_ecrits < taille_partie && (octets_lus = fread(buffer, 1, sizeof(buffer), fichier_entree)) > 0) 
		{
		    fwrite(buffer, 1, octets_lus, fichier_sortie);
		    octets_ecrits += octets_lus;
		}

		fclose(fichier_sortie);  // Fermer la partie créée
		numero_partie++;  // Passer à la partie suivante
	}

	fclose(fichier_entree);  // Fermer le fichier d'entrée
	printf("Fichier découpé en %zu parties.\n", numero_partie);
}


// Fonction pour reconstituer un fichier à partir de plusieurs parties
void join(const char *nom_fichier_sortie, int nombre_parties, char *parties[]) 
{
	// Ouvrir le fichier de sortie en mode écriture binaire
	FILE *fichier_sortie = fopen(nom_fichier_sortie, "wb");
	if (fichier_sortie == NULL) 
	{
        	perror("Erreur lors de la création du fichier de sortie");
        	exit(1);
	}

	char buffer[1024];  // Tampon pour lire les données
	size_t octets_lus;

	// Parcourir chaque partie fournie en argument
	for (int i = 0; i < nombre_parties; i++) 
	{
        	// Ouvrir une partie en mode lecture binaire
        	FILE *fichier_entree = fopen(parties[i], "rb");
        	if (fichier_entree == NULL) 
        	{
        		fprintf(stderr,"Erreur : fichier introuvable %s\n", parties[i]);
            		//perror("Erreur lors de l'ouverture d'une partie");
            		fclose(fichier_sortie);
            		exit(1);
        	}

        // Lire les données de la partie et les écrire dans le fichier de sortie
        while ((octets_lus = fread(buffer, 1, sizeof(buffer), fichier_entree)) > 0) 
        	fwrite(buffer, 1, octets_lus, fichier_sortie);

        fclose(fichier_entree);  // Fermer la partie traitée
   	}

    	fclose(fichier_sortie);  // Fermer le fichier de sortie
    	printf("Fichier reconstitué avec succès : %s\n", nom_fichier_sortie);
}


int main(int argc, char *argv[]) 
{
	if (argc < 3) 
	{
        	fprintf(stderr, "Usage: %s \n", argv[0]);
        	return 0;
        }
	else if(argc == 3)
	{
		
		size_t taille_partie = atol(argv[2]);
		if (taille_partie <= 0)
		{
			fprintf(stderr, "La taille des parties doit être supérieure à 0.\n");
			return 0;
	    	}

	 	split(argv[1], taille_partie);
	 }
	 else if(argc > 3)
	 	join(argv[1], argc - 2, &argv[2]);
	 	
 	return 0;
}