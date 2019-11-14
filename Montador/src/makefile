IDIR =../include
CC=g++ -std=c++11
CFLAGS= -g -I $(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = PreProcessamento.hpp MontadorUmaPassada.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o PreProcessamento.o MontadorUmaPassada.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

montador: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
