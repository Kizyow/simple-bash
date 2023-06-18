#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <sys/wait.h>

#define MAXLI 2048
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

char cmd[MAXLI];
char path[MAXLI];
int pathidx;

void mbash(char *argv[]){
  int res = execvp(argv[0], argv);
  
  if(res == -1){
	  printf("Commande non reconnue\n");	// erreur
  }
}

int main(int argc, char *argv[]) {

  while (1) {

    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != NULL){
      printf("%smbash%s:%s%s%s$ ", KGRN, KWHT, KCYN, cwd, KWHT);
    } else {
      printf("$ ");
    }

    fgets(cmd, MAXLI, stdin);

    // lorsque l'user appuie sur entree, ca rajoute un \n, on doit le supprimer
    int len = strlen(cmd);
    if(len == 1){
	    continue;
    }

    if(cmd[len-1] == '\n' ){
      cmd[len-1] = 0;
    }

    // arguments
    char *token;
    char *argv[32];  // tableau pour stocker les arguments
    int i = 0;

    token = strtok(cmd, " ");

    while (token != NULL) {
        argv[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    argv[i] = NULL;
    char *bck = argv[i-1];

    if(strcmp(bck, "&") == 0){
      argv[i-1] = NULL;
      i--;
    }

    // creation processus fils
    pid_t pid;
    //si l'utilisateur tape exit
    if(strcmp(argv[0], "exit") == 0){
      //on retourne un message de fin et on quitte le programme
      printf("%sAu revoir !%s\n", KRED, KWHT);
      return 0;
      
    } else if(strcmp(argv[0], "cd") == 0){
      //rechercher le repertoire donner par l'utilisateur après le cd
      chdir(argv[1]);

    }  else if(strcmp(argv[0], "author") == 0){
      //si l'utilisateur tape author, on affiche les auteurs
      printf("%sAuthors are : %sAlexandre Perrot%s, %sRémy Kinzelin\n", KMAG, KWHT, KMAG, KWHT);

    } else {
      //sinon on execute la commande
      //creation du processus fils


        if ((pid = fork()) == -1){
          //si le fork echoue, on affiche un message d'erreur
          perror("fork");

        } else if (pid == 0){   
          //si le fork reussi, on execute la commande 
          mbash(argv);
          return 1;

        } else {
          if(strcmp(bck, "&") != 0){
            wait(NULL);
          }
        }


    }

  }
  return 0;
}
