OUT=ifiber.exe
OBJS=fiber.obj main.obj
CC=gcc
CFLAGS=-O2

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(OUT)

fiber.obj: fiber.c fiber.h
	$(CC) $(CFLAGS) -c fiber.c -o fiber.obj
	
main.obj: main.c
	$(CC) $(CFLAGS) -c main.c -o main.obj
	
clean:
	-rm *.obj
	-rm *.exe
