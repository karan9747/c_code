CC = gcc  
CFLAGS = -g  # -Wall for warnings and -g for debugging
TARGET = traverse  

all: $(TARGET)

$(TARGET): advanced_file_traverser.o
	$(CC) $(CFLAGS) -o $(TARGET) advanced_file_traverser.o

advanced_file_traverser.o: advanced_file_traverser.c   # Add src/ if main.c is in the src folder
	$(CC) $(CFLAGS) -c advanced_file_traverser.c  
	

clean:
	rm -f *.o $(TARGET)


