CC=g++
CFLAGS=-I.
DEPS = BST_of_Words.h Line.h LineList.h S_Expression_Tree.h tokenstuff.h Word.h Xyz_Database.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

querymake: main.o BST_of_Words.o Line.o LineList.o S_Expression_Tree.o Word.o Xyz_Database.o 
	g++ -o querymake main.o BST_of_Words.o Line.o LineList.o S_Expression_Tree.o Word.o Xyz_Database.o -I.
