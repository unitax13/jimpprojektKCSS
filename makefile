life: main.o generation.o draw.o saveimg.o readsavefile.o interface.o
	$(CC) -o life main.o generation.o draw.o saveimg.o readsavefile.o interface.o
