CC=clang
CFLAGS=-O0 -g -fPIC
LINK_FLAGS=-lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin2img: main.o lodepng.o hilbert_curve.o
	${CC} -o $@ $^ ${CFLAGS} ${LINK_FLAGS}
