# esse eh o makefile 1

CFLAGS = -I../remoteApi -I../include -DNON_MATLAB_PARSING -DMAX_EXT_API_CONNECTIONS=255

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	CFLAGS += -D__linux
else
	CFLAGS += -D__APPLE__
endif

all:
	g++ $(CFLAGS) -c controleneural.c -o controleneural.o
	gcc $(CFLAGS) -c ../remoteApi/extApi.c -o extApi.o
	gcc $(CFLAGS) -c ../remoteApi/extApiPlatform.c -o extApiPlatform.o
	g++ neuron.o extApi.o extApiPlatform.o trnpair.o neuronet.o vectorpair.o controleneural.o -o juninClient -lpthread
