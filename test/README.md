cd ..

make

./nelua examples/helloworld.nelua --print-code > examples/helloworld.c

clang exampes/helloworld.c -o examples/helloworld

examples/helloworld