#
## Simple .so Makefile
#
#
vpath %.cpp src
vpath %.h include
vpath %.o obj
CC      := g++
LD      := g++
CFLAGS  :=
LDFLAGS := -fPIC -shared 
SOURCE  := $(wildcard src/*.cpp)
OBJS 	:= $(SOURCE:src/%.cpp=obj/%.o)  # or ->  OBJS 	:= $(patsubst src/%.cpp, obj/%.o, $(SOURCE))
BIN     := main
DLIB    := mmseg
TARGET_LIB := lib$(DLIB).so
WARNING := -Wno-deprecated
#WARNING := -W -Wall


all:$(OBJS)
		    $(LD) $(LDFLAGS) -O2 -o $(TARGET_LIB) $(OBJS)  $(WARNING)  
			$(CC) -o $(BIN)  -O2 -Iinclude  -L./ -l$(DLIB)  src/main.cc -Wl,-rpath,./ $(WARNING)  

obj/%.o:src/%.cpp
			$(CC) -c $(CFLAGS) -Iinclude $< -o $@  $(WARNING)

.PHONY: clean

debug:
	@echo $(ENABLE_WARNING)
	@echo $(WARNING)
	@for i in $(OBJS); \
		do echo $$i; \
	done
	@for i in $(SOURCE); \
		do echo $$i; \
	done

clean:
	find ./ -name "*.o"  | xargs rm -rf
	rm -rf *.so

re:
	make clean
	make all
