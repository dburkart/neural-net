# Compiler to use
CC=g++

# Compilation flags
CFLAGS=-c

BASE=perceptron.cpp layer.cpp network.cpp

# Source files for the prediction program
PREDICT_SRC=$(BASE) predict.cpp

PREDICT_OBJ=$(PREDICT_SRC:.cpp=.o)

# Source files for the learning program
TRAIN_SRC=$(BASE) train.cpp

TRAIN_OBJ=$(TRAIN_SRC:.cpp=.o)

# Compile everything
all: $(TRAIN_SRC) $(PREDICT_SRC) train predict

# Compile the training program
train: $(TRAIN_OBJ)
	$(CC) $(TRAIN_OBJ) -o $@
	
# Compile the prediction program
predict: $(PREDICT_OBJ)
	$(CC) $(PREDICT_OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f *.o
