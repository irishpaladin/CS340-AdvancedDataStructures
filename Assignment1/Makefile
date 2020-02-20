CXX = g++ # or CC if you prefer it on Hercules

assign1srp796: Main.o Stack.o
	$(CXX) -o assign1srp796 Main.o Stack.o

Main.o :  Main.cpp Main.h Stack.h
	$(CXX) -c  Main.cpp

Stack.o : Stack.h



clean:
	@ /bin/rm -f *.o
