CPP = g++
LINKER_CONFIG = -g -Wall -mavx
QUANT_VEC_PROJECT = quant_vec
TESTING_PROJECT = tester
STANDARD = c++11

quant_vector:
	${CPP} ${LINKER_CONFIG} -std=$(STANDARD) -o ${QUANT_VEC_PROJECT} "${QUANT_VEC_PROJECT}.cpp"

testing:
	${CPP} ${LINKER_CONFIG} -std=$(STANDARD) -o ${QUANT_VEC_PROJECT} "${TESTING_PROJECT}.cpp"

float_class_testing:
	${CPP} ${LINKER_CONFIG} -std=$(STANDARD) -o ${QUANT_VEC_PROJECT} tester_float.cpp