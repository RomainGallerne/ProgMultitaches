########################################
#~ définitions
########################################

BIN=bin/exo1


# liste des fichiers sources 
SRCS0=exo1.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

bin/exo1: $(SRCS0:%.ccc=obj/%.o)
	gcc calcul/calculC.o -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~
