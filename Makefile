#original contributer: CabrestopUK
all: main.exe

main.exe: main.o account-utils.o type-utils.o
	g++ main.o account-utils.o type-utils.o -o main
	
account-utils.o: account-utils.cpp account-utils.h
	g++ -c account-utils.cpp -o account-utils.o

type-utils.o: type-utils.cpp type-utils.h
	g++ -c type-utils.cpp -o type-utils.o

main.o: main.cpp account-utils.h
	g++ -c main.cpp -o main.o

clean:
	rm *.o