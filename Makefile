CC = gcc                 
CFLAGS = -Wall -Wextra    
EXEC = codpostal           
SRC = main.c              

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(SRC) -o $(EXEC) $(CFLAGS)

clean:
	rm -f $(EXEC)

