CC := cc
OBJDIR := obj
INCDIR := include
OBJ := learn_makefile.o printfunc.o
MKDIR := mkdir -p
IFLAGS := -I $(INCDIR)

task: $(OBJDIR)/learn_makefile.o $(OBJDIR)/printfunc.o
	$(CC) -o $@ $^ 

$(shell $(MKDIR) $(OBJDIR))

$(OBJDIR)/learn_makefile.o: src/learn_makefile.c 
	$(CC) $(IFLAGS) -c $< -o $@

$(OBJDIR)/printfunc.o: src/printfunc.c 
	$(CC) $(IFLAGS) -c $< -o $@ 


.PHONY: clean
clean:
	rm -f $(OBJDIR)/learn_makefile.o $(OBJDIR)/printfunc.o task