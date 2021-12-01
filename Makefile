main : main.o Aquarium.o Milieu.o Bestiole.o Comportement.o Gregaire.o Peureuse.o Kamikaze.o
	g++ -Wall -std=c++11 -o main main.o Aquarium.o Bestiole.o Milieu.o Comportement.o Gregaire.o Peureuse.o Kamikaze.o -I . -lX11 -lpthread

Aquarium.o : Aquarium.h Aquarium.cpp
	g++ -Wall -std=c++11  -c Aquarium.cpp -I .

Milieu.o : Milieu.h Milieu.cpp
	g++ -Wall -std=c++11  -c Milieu.cpp -I .

Bestiole.o : Bestiole.h Bestiole.cpp Gregaire.cpp Gregaire.h Comportement.h
	g++ -Wall -std=c++11  -c Bestiole.cpp -I .

Comportement.o : Comportement.h Comportement.cpp
	g++ -Wall -std=c++11  -c Comportement.cpp -I .

Gregaire.o: Gregaire.h Gregaire.cpp Comportement.h
	g++ -Wall -std=c++11  -c Gregaire.cpp -I .

Peureuse.o: Peureuse.h Peureuse.cpp Comportement.h
	g++ -Wall -std=c++11  -c Peureuse.cpp -I .

Kamikaze.o: Kamikaze.h Kamikaze.cpp Comportement.h
	g++ -Wall -std=c++11  -c Kamikaze.cpp -I .	

main.o: main.cpp Comportement.h Gregaire.h Peureuse.h Kamikaze.h
	g++ -Wall -std=c++11  -c main.cpp -I .
clear:
	rm *.o main



