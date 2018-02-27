main: main.cpp 
	g++ -o main main.cpp model.cpp matrix.cpp vectormath.cpp -lsfml-graphics -lsfml-window -lsfml-system 