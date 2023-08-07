CC = gcc
TGT = ludtm
OBJS = ludtm

all: $(TGT)

$(TGT): $(OBJS)
	$(CC) -w -pthread -ggdb -O0 ludtm.c -o $@ $^

test: $(TGT)
	./$(TGT)

.PHONY: clean
clean:
	@rm -rf $(OBJS) $(TGT)
