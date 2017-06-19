CFLAGS = -I/remoteApi -I/include -DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	CFLAGS += -D__linux
else
	CFLAGS += -D__APPLE__
endif

all: 
	@rm -f bin/*.*
	@rm -f *.o 
	g++ -std=c++11 $(CFLAGS) -c ../*.cpp -w
	@echo -w is supressing warnings
	gcc $(CFLAGS) -c remoteApi/extApi.c -o extApi.o
	gcc $(CFLAGS) -c remoteApi/extApiPlatform.c -o extApiPlatform.o
	@mkdir -p bin
	g++ *.o -o ../../../fuzzyKJunior -lpthread
