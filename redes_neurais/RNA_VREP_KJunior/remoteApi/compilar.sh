#!/bin/bash

#compilando o primeiro
cp makefile0 makefile
rm neural
make
rm makefile

#treinando
./neural junin

#compilando o executavel final
cp makefile1 makefile
make
rm makefile
