#define MAX_SIZE 100
#include <stdio.h>
#include <stdlib.h> /* EXIT_FAILURE; */
#include <sys/types.h> /* open */
#include <sys/stat.h> /* open */
#include <fcntl.h> /* open */
#include <unistd.h> /* read, write */


int main (int argc, char *argv[]) 
{
	if ( argc != 3 )

	{
		perror("Zła liczba argumentów. Prawidłowa postać polecenia: ./kopiuj.x 'nazwa pliku kopiowanego' 'nazwa pliku docelowego' ");
		return EXIT_FAILURE;
	}

int plik_k; /* plik kopiowany */
int plik_d; /* plik docelowy */

void *bufor;

	if ( (bufor = malloc (MAX_SIZE)) == NULL )
	{
		perror ("Nie można uzyskać pamięci");
		return EXIT_FAILURE;
	}

plik_k = open (argv[1], O_RDWR); /* read and write */

	if (plik_k == -1)
	{
		perror("Plik nie może być otworzony");
		return EXIT_FAILURE;
	}

plik_d = open (argv[2], O_RDWR); /* read and write */

	if (plik_d == -1)
	{
		perror("Plik nie może być otworzony");
		return EXIT_FAILURE;
	}

read(plik_k, bufor, MAX_SIZE);

	if ( read(plik_k, bufor, MAX_SIZE) == -1 )
	{
		perror("Plik nie może być oczytany");
		return EXIT_FAILURE;
	}

write(plik_d, bufor, MAX_SIZE);

	if ( write(plik_d, bufor, MAX_SIZE) == -1 )
	{
		perror("Bład zapisu do pliku");
		return EXIT_FAILURE;
	}

printf ("Przekopiowano %s do %s \n", argv[1], argv[2]);
return 0;
}