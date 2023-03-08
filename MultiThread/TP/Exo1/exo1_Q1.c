#include <string.h>
#include <stdio.h>//perror
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "calcul/calcul.h"


struct paramsFonctionThread {

  int idThread;

  // si d'autres param�tres, les ajouter ici.

};


void * fonctionThread (void * params){
  struct paramsFonctionThread * args = (struct paramsFonctionThread *) params;

  int sec = 2;
  pthread_t thread = pthread_self();
  printf("Thread %ld : Création du thread du processus %i qui durera %i secondes.\n",thread,getpid(),sec*3);
  calcul(sec);
  printf("Thread %ld : Fin d'execution.\n",thread);
  pthread_exit(NULL);
}


int main(int argc, char * argv[]){

  if (argc < 2 ){
    printf("utilisation: %s  nombre_threads  \n", argv[0]);
    return 1;
  }     
  
  pthread_t threads[atoi(argv[1])];
  
  // cr�ation des threards 
  for (int i = 0; i < atoi(argv[1]); i++){

    // Le passage de param�tre est fortement conseill� (�viter les
    // variables globles).

    // compl�ter pour initialiser les param�tres
    if (pthread_create(&threads[i], NULL, fonctionThread, NULL) != 0){
      perror("Principal : erreur de creation des thread\n");
      exit(1);
    }
  }
  //On attend la fin des thread
  for (int i = 0; i < atoi(argv[1]); i++){
    if(pthread_join(threads[i], NULL) != 0){
      perror("Principal : erreur à l'attente des threads\n");
      exit(1);
    }
  }
  printf("Principal : Tout les threads ont terminé, fin.\n");


// garder cette saisie et modifier le code en temps venu.
/*  char c; 
  printf("saisir un caract�re \n");
  fgets(m, 1, stdin);*/

  return 0;
 
}
 
