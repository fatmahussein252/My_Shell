BUILD_TYPE=DEBUG

all: myshell


ifeq ($(BUILD_TYPE), DEBUG)
CFLAGS= -g
endif

copy1.o: copy1.c internal.h
	gcc $(CFLAGS) -o copy1.o -c copy1.c

move.o: move.c internal.h
	gcc $(CFLAGS) -o move.o -c move.c
chdir.o: chdir.c internal.h
	gcc $(CFLAGS) -o chdir.o -c chdir.c

echo.o: echo.c internal.h
	gcc $(CFLAGS) -o echo.o -c echo.c

external.o: external.c internal.h
	gcc $(CFLAGS) -o external.o -c external.c
free.o: free.c internal.h
	gcc $(CFLAGS) -o free.o -c free.c

pipes.o: pipes.c internal.h
	gcc $(CFLAGS) -o pipes.o -c pipes.c


printEnv.o: printEnv.c internal.h
	gcc $(CFLAGS) -o printEnv.o -c printEnv.c	

redirect.o: redirect.c internal.h
	gcc $(CFLAGS) -o redirect.o -c redirect.c

type.o: type.c internal.h
	gcc $(CFLAGS) -o type.o -c type.c


myshell: myshell.o move.o copy1.o chdir.o echo.o type.o external.o printEnv.o free.o redirect.o
	gcc $(CFLAGS) -o myshell myshell.o move.o copy1.o chdir.o echo.o type.o external.o printEnv.o free.o redirect.o



