#original contributer: CabrestopUK
all: main.exe

check:
	g++ -c main.cpp -o main.o -Wall -Wextra -Wshadow -Werror
	g++ -c csv.cpp -o csv.o -Wall -Wextra -Wshadow -Werror
	g++ -c type-utils.cpp -o type-utils.o -Wall -Wextra -Wshadow -Werror
	g++ -c account-utils.cpp -o account-utils.o -Wall -Wextra -Wshadow -Werror
	g++ main.o account-utils.o type-utils.o csv.o -o main -Wall -Wextra -Wshadow -Werror
	
main.exe: main.o account-utils.o type-utils.o csv.o
	g++ main.o account-utils.o type-utils.o csv.o -o main
	
csv.o: csv.h csv.cpp
	g++ -c csv.cpp -o csv.o

account-utils.o: account-utils.cpp account-utils.h
	g++ -c account-utils.cpp -o account-utils.o 

type-utils.o: type-utils.cpp type-utils.h
	g++ -c type-utils.cpp -o type-utils.o 

main.o: main.cpp
	g++ -c main.cpp -o main.o 

clean:
	rm *.o