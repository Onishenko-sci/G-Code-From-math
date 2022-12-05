all:
	g++ main.cpp ./src/print_head.cpp ./src/Vector2.cpp -o generate.exe
	./generate.exe
