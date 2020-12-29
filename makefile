CC= g++
CFLAGS= -std=gnu++17 -I.
DEPS= shared.h

least-squares: dzvector.o endotatio.o forma.o main.o 
	$(CC) -o least-squares dzvector.o endotatio.o forma.o main.o $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o core untitled least-squares a.out
