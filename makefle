all:
	gcc -c -fPIC -w function.c -o function.o
	gcc -shared -o libfunction.so function.o
	gcc -c -w longArith.c -o longArith.o
	gcc longArith.o -L. -Wl,-rpath,. -lfunction -o longArith
	g++ -c -Wall longArith2.cpp -o longArith2.o
	g++ -c -fPIC function2.cpp -o function2.o
	g++ function2.o -g -shared -L. -lfunction -Wl,-rpath,. -o libfunction2.so
	g++ longArith2.o -o longArith2 -L. -lfunction2 -Wl,-rpath,.
	swig -c++ -python verylong.i
	g++ -c -fPIC verylong_wrap.cxx -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
	g++ verylong_wrap.o -L/Library/Frameworks/Python.framework/Versions/2.7/lib -lpython2.7 -dynamiclib -fPIC -L. -lfunction2 -Wl,-rpath,. -o _verylong.so
	rm -f *.o
	rm verylong_wrap.cxx
