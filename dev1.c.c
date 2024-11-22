#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Definition des fonctions f et g

int f (int n)
{
	int puiss = 1;
	for (int i = 0; i < n; i++)
		puiss = puiss * 2;
	return puiss;
}

int g (int n)
{
	return 2 * n;
}

int main (int argc, char* argv[])
{
	if(argc < 3)
	{
		printf ("Usage: %s", argv[0]);
		return 1;
	}
	
	int n = 0; 
	int option_f = 0, option_g = 0;
	
	// parcours des arguments pour traiter les options
	for(int i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "-f") == 0 && i < argc)
		{
			option_f = 1;	
			n = atoi (argv[2]);   //récupère la valeur de n après -f   
			i++;         //ignore le prochain argument car etant la valeur de n
		}	   
		else if(strcmp(argv[i], "-g") == 0 && i < argc)
		{
			option_g = 1;
			n = atoi (argv[2]);
			i++;
		}	
	}
	
	//cas où seulement -f est spécifié
	if((option_f == 1) && (option_g == 0))
		printf("f(%d) = %d\n", n, f(n));
	
	//cas où seulement -g est spécifié
	else if((option_g == 1) && (option_f== 0))
		printf("g(%d) = %d\n", n, g(n));
	
	//cas où les deux -f et -g sont spécifiés
	else if((option_f == 1) && (option_g == 1))
	{
		// verification de l'ordre d'apparition de -f et -g
		int fog = 0;    // 1 si c'est f(g(n)), 0 si c'est g(f(n))
		
		for(int i = 1; i < argc; i++)
		{ 
			if(strcmp(argv[i], "-f") == 0)
			{
				fog = 1;   //f avant g, donc fog
				break;
			}
			else if(strcmp(argv[i], "-g") == 0)
			{
				fog = 0;   //g avant f, donc gof
				break;
			}
		}
		
	
		if(fog == 1) 
			//calcul de f(g(n))
			printf("fog(%d) = f(g(%d)) = %d\n", n, n, f(g(n)));
		else if(fog == 0)
			//calcul de g(f(n))
			printf("gof(%d) = g(f(%d)) = %d\n", n, n, g(f(n)));
		
	}
	else 
		printf("Erreur, vous devez spécifier au moins une des options -f ou -g.\n");
	
	return 0;
}
		