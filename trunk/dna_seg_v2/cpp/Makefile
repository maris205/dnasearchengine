OUTPUT := test

# to build the library , just use "make"
# to clean the library object files, use "make clean"

USER_MARCOS     :=
HEADERS         := ./
LIBS_PATH	:=
LIBS 		:=

SOURCE := $(wildcard ./*.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SOURCE))

CFLAGS = -g
CC = g++

%.o: %.cpp
	$(CC) $(CFLAGS) $(addprefix -D,$(USER_MARCOS)) $(addprefix -I, $(HEADERS))  -c $< -o $@

$(OUTPUT):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(addprefix -L,$(LIBS_PATH)) $(addprefix -l,$(LIBS))
	@echo "===============OK."

clean:
	rm $(OUTPUT) *.o

show:
	@echo $(SOURCE) $(OBJS)
