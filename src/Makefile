CXX = gcc
CXXFLAGS = -I$(INCDIR)
INCDIR = ../include
OBJDIR = ../obj

_DEP = solver.h helper.h structure.h stl.h
DEP = $(patsubst %,$(INCDIR)/%,$(_DEP))

_OBJ = main.o solver.o helper.o stl.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o : %.c $(DEP)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

all : $(OBJ)
	$(CXX) $(OBJ) $(CXXFLAGS) -o ../bin/myqm

.PHONY : clean

clean :
	rm -f $(OBJDIR)/*.o *~ *.bak ../bin/myqm *.exe.stackdump