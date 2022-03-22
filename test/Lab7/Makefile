
output: main.o Registrar.o Course.o Student.o
	g++ main.o Registrar.o Course.o Student.o -o output

main.o: main.cpp
	g++ -c main.cpp

Registrar.o: Registrar.cpp Registrar.h
	g++ -c Registrar.cpp

Course.o: Course.cpp Course.h
	g++ -c Course.cpp

Student.o: Student.cpp Student.h
	g++ -c Student.cpp

clean:
	rm *.o output