CPP = g++
LINKER_CONFIG = -g -Wall -mavx
QUANT_VEC_PROJECT = quant_vec
STANDARD = c++17

double_performance_testing:
	${CPP} ${LINKER_CONFIG} -std=$(STANDARD) -o ${QUANT_VEC_PROJECT} performance_double.cpp

float_performance_testing:
	${CPP} ${LINKER_CONFIG} -std=$(STANDARD) -o ${QUANT_VEC_PROJECT} performance_float.cpp