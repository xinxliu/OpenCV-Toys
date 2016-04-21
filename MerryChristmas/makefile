CXX=g++ -std=gnu++14
OPENCV=`pkg-config --cflags --libs opencv`

TARGET=$(BIN_DIR)/MerryChristmas

OBJ_DIR=build
BIN_DIR=bin
SRC=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

$(TARGET):chkobjdir chkbindir $(OBJS)
	$(CXX) -o $@ $(OBJS) $(OPENCV)
	
$(OBJS):$(SRC)
	$(CXX) -c $(SRC) -o $(OBJS)
	
chkobjdir:
	@if test ! -d $(OBJ_DIR);\
	then \
		mkdir $(OBJ_DIR);\
	fi
	
chkbindir:
	@if test ! -d $(BIN_DIR);\
	then \
		mkdir $(BIN_DIR);\
	fi	

.PHONY:clean
clean:
	-rm -rf $(BIN_DIR) 
	-rm -rf $(OBJ_DIR)
