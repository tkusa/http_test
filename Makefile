# compiler setting
CC = g++
CFLAGS = -Wall -g

SERVER_PROG = server
SERVER_OBJECTS = server.o socket.o request.o response.o parser.o
CLIENT_PROG = client
CLIENT_OBJECTS = client.o socket.o request.o response.o parser.o
OBJ = ./build/obj
BIN = ./build/bin
SRC = ./src
BINPROGS = $(addprefix $(BIN)/, $(SERVER_PROG) $(CLIENT_PROG))

all: prepare $(BINPROGS)

clean:
	rm -f $(OBJ)/* $(BIN)/*

prepare:
	mkdir -p $(OBJ);
	mkdir -p $(BIN);

server: 
	
# compile obj
$(OBJ)/%.o : $(SRC)/%.cpp
	$(COMPILE.cpp) $< -o $@

$(OBJ)/%.o : $(SRC)/connection/%.cpp
	$(COMPILE.cpp) $< -o $@

$(OBJ)/%.o : $(SRC)/http/%.cpp
	$(COMPILE.cpp) $< -o $@

# link server program
$(BIN)/$(SERVER_PROG): $(addprefix $(OBJ)/, $(SERVER_OBJECTS))
	$(LINK.o) $^ $(LDLIBS) -o $@

# link client program
$(BIN)/$(CLIENT_PROG): $(addprefix $(OBJ)/, $(CLIENT_OBJECTS))
	$(LINK.o) $^ $(LDLIBS) -o $@

