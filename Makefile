all: link

link: main connection graphviewer InfoLoader teste menu
	g++ -o proj main.o connection.o graphviewer.o info.o test.o menu.o

main:
	g++ -c Main.cpp -o main.o

connection:
	g++ -c GraphViewer/connection.cpp -o connection.o

graphviewer:
	g++ -c GraphViewer/graphviewer.cpp -o graphviewer.o

InfoLoader:
	g++ -c InfoLoader.cpp -o info.o

teste:
	g++ -c Test.cpp -o test.o

menu:
	g++ -c menu.cpp -o menu.o
