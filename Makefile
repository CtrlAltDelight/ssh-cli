BASE_NAME=sshcli
SRC_C=$(BASE_NAME).c
SRC_H=$(BASE_NAME).h
EXECUTABLE=$(BASE_NAME)
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic -std=c11

$(EXECUTABLE): $(SRC_C)
	gcc $(SRC_C) $(CFLAGS) -o $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
