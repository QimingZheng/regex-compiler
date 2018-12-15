CXX=g++
CXXFLAG= --std=c++11 -O0
CXX_INCLUDE=
CXX_LIBRARY=
NVCC= nvcc
NVCCFLAGS= -arch=compute_60 -code=sm_60 -std=c++11 -Xptxas -dlcm=ca
NVCC_INCLUDE= -I/usr/local/cuda/include
NVCC_LIBRARY= -L/usr/local/cuda/lib

all: regex_internal gpu_matcher

regex_internal:
	${CXX} ${CXXFLAG} matcher.cc -fPIC -shared -o libmymatcher.so

gpu_matcher:
	${NVCC} ${NVCCFLAG} cuda_kernel.cu -c -o cuda_kernel.o

clean:
	rm *.o