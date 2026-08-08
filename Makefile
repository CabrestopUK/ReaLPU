all: main.exe clean

main.exe: main.o account-utils.o
	g++ main.o account-utils.o -o main
	
account-utils.o: account-utils.cpp account-utils.h
	g++ -c account-utils.cpp -o account-utils.o

main.o: main.cpp account-utils.h
	g++ -c main.cpp -o main.o

clean:
	rm *.o