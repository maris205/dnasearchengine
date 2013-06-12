OUTPUT := stability

# to build the library , just use "make"
# to clean the library object files, use "make clean"
# to clean all the library files, use "make realclean"
# to build the library file dependency, use "make depend"
# to install the header files, use "make install"

USER_MARCOS     := 
HEADERS         := ./ 
LIBS_PATH	:=  
LIBS 		:= 
#QueryKeyWords QueryCat
# IndexSelect NonChiProcess

SOURCE := $(wildcard ./*.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SOURCE))

CFLAGS = -g 
CC = g++ 

#%.o: %.c
#	$(CC) $(CFLAGS) $(addprefix -D,$(USER_MARCOS)) $(addprefix -I, $(HEADERS))  -c $< -o $@ 
%.o: %.cpp 
	$(CC) $(CFLAGS) $(addprefix -D,$(USER_MARCOS)) $(addprefix -I, $(HEADERS))  -c $< -o $@ 

$(OUTPUT):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(addprefix -L,$(LIBS_PATH)) $(addprefix -l,$(LIBS))
	@echo "===============OK."

clean:
	rm $(OUTPUT) *.o
#	rm -rf $(OUTPUT) *.o

install:$(OUTPUT)

show:
	@echo $(SOURCE) $(OBJS)
