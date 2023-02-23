########################################
#~ définitions
########################################

# nom de l'executable
BIN=bin/acompleter bin/acompleterITE bin/acompleterCONCU

# liste des fichiers sources 
SRCS3=acompleter.cpp
SRCS4=acompleterITE.cpp
SRCS5=acompleterCONCU.cpp

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.cpp
	g++ -Wall -Iinclude -c $< -o $@

bin/acompleter: $(SRCS3:%.cpp=obj/%.o)
	g++ -o $@ $+

bin/acompleterITE: $(SRCS4:%.cpp=obj/%.o)
	g++ -o $@ $+

bin/acompleterCONCU: $(SRCS5:%.cpp=obj/%.o)
	g++ -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~file fourni ou directement en utilisant gcc.

