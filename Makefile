BASE_NAME=interface
SRC_C=$(BASE_NAME).c
SRC_H=$(BASE_NAME).h
EXECUTABLE=test_$(BASE_NAME)
TEST_C=$(EXECUTABLE).c
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic -std=c11

$(EXECUTABLE): $(SRC_C)
	gcc $(SRC_C) $(CFLAGS) -o $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
