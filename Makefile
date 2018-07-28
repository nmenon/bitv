bin:= bitv
src_dir:= src
CFLAGS := -O3 -Wall

objs:= ${src_dir}/bitv.o

all: ${bin}

clean:
	@rm -f ${objs} ${bin}

distclean: clean

${bin}: ${objs}
	$(CC) $(CFLAGS) -o $@ $<


