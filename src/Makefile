CXX=g++
CXXFLAG= --std=c++11 -O0
CXX_INCLUDE=
CXX_LIBRARY=
NVCC= nvcc
NVCCFLAGS= -arch=compute_60 -code=sm_60 -std=c++11 -Xptxas -dlcm=ca
NVCC_INCLUDE= -I/usr/local/cuda/include
NVCC_LIBRARY= -L/usr/local/cuda/lib

all: parser compiler matcher gpu_matcher

parser:
	${CXX} ${CXXFLAG} parser.cc -c -o parser.o

compiler:
	${CXX} ${CXXFLAG} compiler.cc -c -o compiler.o

matcher:
	${CXX} ${CXXFLAG} matcher.cc -c -o matcher.o

gpu_matcher:
	${NVCC} ${NVCCFLAG} cuda_kernel.cu -c -o cuda_kernel.o

clean:
	rm *.o