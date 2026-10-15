CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = main.cpp \
      src/storage.cpp \
      src/array.cpp \
      src/forward_list.cpp \
      src/list.cpp \
      src/stack.cpp \
      src/queue.cpp \
      src/avl.cpp

BIN = dbms_cpp

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

rust:
	cd rust && cargo build --release
	cp rust/target/release/dbms_rust rust/dbms_rust

clean:
	rm -f $(BIN)
	cd rust && cargo clean
