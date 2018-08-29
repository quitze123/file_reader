CC=gcc
CFLAGS=-I.

run: read_file.o
	$(CC) $(CFLAGS) -o run read_file.o
	
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
