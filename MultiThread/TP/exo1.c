#include <string.h>
#include <stdio.h>//perror
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "calcul/calcul.h"


struct paramsFonctionThread {
  int idThread;
  int tpms;
  int *c;
  pthread_mutex_t *verrou;
};


void * fonctionThread (void * params){
  struct paramsFonctionThread * args = (struct paramsFonctionThread *) params;

  int sec = 1;
  pthread_t thread = pthread_self();
  printf("Thread %ld : Création du thread du processus %i.\n",thread,getpid());
  calcul(args->tpms);

  //Début section critique
  if(pthread_mutex_lock(args->verrou)!=0){ //Vérouillage
    perror("Erreur de verrouillage\n");
    exit(1);
  } else {
    printf("Thread %ld : Verrouillage.\n",thread);
    printf("Thread %ld : soit la variable c : %i que l'on va incrémenté.\n",thread,(*args->c));
    (*args->c) += 1;
    printf("Thread %ld : soit la variable c incrémenté : %i.\n",thread,(*args->c));
  }

  if(pthread_mutex_unlock(args->verrou)!=0){ //Dévérouillage
    perror("Erreur de déverrouillage\n");
    exit(1);
  }
  //Fin section critique

  printf("Thread %ld : Déverrouillage.\n",thread);
  calcul(args->tpms);
  printf("Thread %ld : Fin d'execution.\n",thread);
  pthread_exit(NULL);
}


int main(int argc, char * argv[]){

  if (argc < 3 ){
    printf("utilisation: %s  nombre_threads tempsAttente \n", argv[0]);
    return 1;
  }     

  // garder cette saisie et modifier le code en temps venu. 
  printf("saisir un chiffre : ");
  int c = getc(stdin)-'0';

  printf("Début de création du tableau de thread.\n");
  
  pthread_t threads[atoi(argv[1])];

  pthread_mutex_t verrou;
  pthread_mutex_init(&verrou, NULL);

  printf("Boucle de création des threads.\n");
  
  // cr�ation des threards 
  for (int i = 0; i < atoi(argv[1]); i++){

    struct paramsFonctionThread args = {i,atoi(argv[2]),&c,&verrou};

    // compl�ter pour initialiser les param�tres
    if (pthread_create(&threads[i], NULL, fonctionThread, &args) != 0){
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
  pthread_mutex_destroy(&verrou);
  printf("Principal : Tout les threads ont terminé, fin.\n");

  return 0;
 
}
 
