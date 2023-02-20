TOPLEVEL := ../../..
APP=tcbin
NVCC=/usr/local/cuda/bin/nvcc
all:
	$(NVCC) -O3   -I ../include/ undirected_triangle_counting.cu -o tc
	mv tc $(TOPLEVEL)/bin/GPU/tc/tc
