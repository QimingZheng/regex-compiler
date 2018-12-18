CXX=g++
CXXFLAG= --std=c++11 -O0
CXX_INCLUDE= -I../src/
CXX_LIBRARY= -L../src/
NVCC= nvcc
NVCCFLAG= --std=c++11
NVCC_INCLUDE= -I/usr/local/cuda/include -I../src/
NVCC_LIBRARY= -L/usr/local/cuda/lib -L../src/

all: parser_UT compiler_UT matcher_UT gpu_matcher_UT iNFA_helper Profiler

parser_UT:
	${CXX} ${CXXFLAG} ${CXX_INCLUDE} ${CXX_LIBRARY} parser_UT.cc -o parser_UT -lregex_internal

compiler_UT:
	${CXX} ${CXXFLAG} ${CXX_INCLUDE} ${CXX_LIBRARY} compiler_UT.cc -o compiler_UT -lregex_internal

matcher_UT:
	${CXX} ${CXXFLAG} ${CXX_INCLUDE} ${CXX_LIBRARY} matcher_UT.cc -o matcher_UT -lregex_internal

gpu_matcher_UT:
	${NVCC} ${NVCCFLAG} ${NVCC_INCLUDE} ${NVCC_LIBRARY} matcher_UT.cu -o gpu_matcher_UT -lregex_internal

iNFA_helper:
	${CXX} ${CXXFLAG} ${CXX_INCLUDE} ${CXX_LIBRARY} iNFA_helper.cc -o iNFA_helper -lregex_internal

Profiler:
	${NVCC} ${NVCCFLAG} ${NVCC_INCLUDE} ${NVCC_LIBRARY} profile_gpu_matcher.cu -o Profiler -lregex_internal

clean:
	rm parser_UT compiler_UT matcher_UT gpu_matcher_UT iNFA_helper Profiler
