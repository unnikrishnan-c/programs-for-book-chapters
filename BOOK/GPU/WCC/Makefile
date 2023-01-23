TOPLEVEL := ../../..
APP=ccbin
NVCC=/usr/local/cuda/bin/nvcc
all:
	$(NVCC) -O3   -I ../include/ connected_component.cu -o cc
	mv cc $(TOPLEVEL)/bin/GPU/cc/cc
