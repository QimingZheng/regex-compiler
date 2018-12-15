CXX=g++
CXXFLAG= --std=c++11 -O0
CXX_INCLUDE=
CXX_LIBRARY=
NVCC= nvcc
NVCCFLAGS= -arch=compute_60 -code=sm_60 -std=c++11 -Xptxas -dlcm=ca
NVCC_INCLUDE= -I/usr/local/cuda/include
NVCC_LIBRARY= -L/usr/local/cuda/lib

all: parser_UT compiler_UT matcher_UT gpu_matcher_UT

parser_UT:
	${CXX} ${CXXFLAG} parser_UT.cc -o parser_UT ../src/parser.o

compiler_UT:
	${CXX} ${CXXFLAG} compiler_UT.cc -o compiler_UT ../src/compiler.o

matcher_UT:
	${CXX} ${CXXFLAG} matcher_UT.cc -o matcher_UT ../src/matcher.o

gpu_matcher_UT:
	${NVCC} ${NVCCFLAG} matcher_UT.cu -o gpu_matcher_UT ../src/cuda_kernel.o

clean:
	rm parser_UT compiler_UT matcher_UT gpu_matcher_UT