CC = gcc                 
CFLAGS = -Wall -Wextra    
EXEC = programa           
SRC = main.c              

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(SRC) -o $(EXEC) $(CFLAGS)

clean:
	rm -f $(EXEC)

