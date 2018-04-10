CC =  g++ -Wextra -std=c++14
OUTPUT = TripPlanner
all: link

link: main connection graphviewer InfoLoader teste menu
	$(CC) -o $(OUTPUT) main.o connection.o graphviewer.o info.o test.o menu.o

main:
	$(CC) -c Main.cpp -o main.o

connection:
	$(CC) -c GraphViewer/connection.cpp -o connection.o

graphviewer:
	$(CC) -c GraphViewer/graphviewer.cpp -o graphviewer.o

InfoLoader:
	$(CC) -c InfoLoader.cpp -o info.o

teste:
	$(CC) -c Test.cpp -o test.o

menu:
	$(CC) -c menu.cpp -o menu.o

clean:
	rm *.o
