all:
	g++ main.cpp ./src/GCode.cpp ./src/Vector2.cpp -o generate.exe
	./generate.exe
