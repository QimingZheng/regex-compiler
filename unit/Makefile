CXX=g++
CXXFLAG= --std=c++11 -O0
CXX_INCLUDE=
CXX_LIBRARY=
NVCC= nvcc
NVCCFLAG= -arch=compute_60 -code=sm_60 --std=c++11 -Xptxas -dlcm=ca
NVCC_INCLUDE= -I/usr/local/cuda/include -I../src/
NVCC_LIBRARY= -L/usr/local/cuda/lib -I../src/

all: parser_UT compiler_UT matcher_UT gpu_matcher_UT

parser_UT:
	${CXX} ${CXXFLAG} parser_UT.cc -o parser_UT -lregex_internal

compiler_UT:
	${CXX} ${CXXFLAG} compiler_UT.cc -o compiler_UT -lregex_internal

matcher_UT:
	${CXX} ${CXXFLAG} matcher_UT.cc -o matcher_UT -lregex_internal

gpu_matcher_UT:
	${NVCC} ${NVCCFLAG} ${NVCC_INCLUDE} ${NVCC_LIBRARY} matcher_UT.cu -o gpu_matcher_UT -lregex_internal

clean:
	rm parser_UT compiler_UT matcher_UT gpu_matcher_UT