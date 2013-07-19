#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc , char *argv[]) {
char ligne[80], *arg[2];
printf("myshell> ");

  while (fgets(ligne,sizeof(ligne),stdin) != NULL) {
		if (strcmp(ligne,"exit\n") == 0) {
		exit(EXIT_SUCCESS);
		}
	ligne[strlen(ligne)-1]= '\0';
	arg[0] = ligne; /* nom de l’executable */
	arg[1] = NULL; /* fin des parametres */
	
	switch (fork()) {
	case -1: /* erreur */
		fprintf(stderr,"Erreur dans fork()\n");
		exit(EXIT_FAILURE);
	case 0: /* fils */
	execvp(arg[0],arg);
	fprintf(stderr,"Erreur dans execvp(\"%s\")\n",arg[0]);
	exit(EXIT_FAILURE);
	default:
	wait(NULL);
	}
printf("myshell> ");
} /* fin du while */
exit(EXIT_SUCCESS);
}
