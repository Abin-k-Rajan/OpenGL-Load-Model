g++ -c -o functions.o functions.cpp
g++ -c -o main.o main.cpp -I"C:\Program Files\Common Files\MinGW\include"
g++ -o main.exe main.o functions.o -L"C:\MinGW\lib\freeglut" -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32 -m32
.\main