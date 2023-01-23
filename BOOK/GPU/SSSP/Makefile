TOPLEVEL := ../../..
APP=ssspbin
NVCC=/usr/local/cuda/bin/nvcc
all:
	$(NVCC) -O3   -I ../include/ newgpusssp1.cu -o sssp
	mv sssp $(TOPLEVEL)/bin/GPU/sssp/sssp
	$(NVCC) -O3   -I ../include/ singcollsssp.cu -o singcollsssp
	mv singcollsssp $(TOPLEVEL)/bin/GPU/sssp/singcollsssp
