OBJS	= output/main.o output/lab2.o
SOURCE	= main.c lab2.c
HEADER	= lab2.h
OUT	= output/lab2
CFLAGS	= -g -c 
CC	= gcc
ARG = ""

all:	output/lab2

output/lab2: $(OBJS)
	$(CC) -o $@ $^

output/%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -o $@ $<
	 
clean:
	rm -f $(OBJS) $(OUT)

run: output/lab2
	make clean
	make
	./output/lab2 $(ARG)

test: output/lab2
	make clean
	make
	./output/lab2 input.txt s/Lorem/Kek/
	sleep 1
	./output/lab2 input.txt s/Kek/Lorem/
	sleep 1
	./output/lab2 input.txt s/^/test/
	./output/lab2 input.txt s/$$/test/
	sleep 1
	./output/lab2 input.txt /test/d