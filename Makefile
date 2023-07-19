INCDIR = ../include
CXX = gcc
CXXFLAGS = -I$(INC)
OBJDIR = obj

_DEP = stl.h structure.h helper.h solver.h
DEP = $(patsubset %,$(INCDIR)/%,$(_DEP))

_OBJ = main.o solver.o helper.o stl.o
OBJ = $(patsubset %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o : %.c $(DEP)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

all : $(OBJ)
	$(CXX) -o ../bin/QM $^ $(CXXFLAGS)

.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o *~ *.bak ../bin/QM

run :
	../bin/QM