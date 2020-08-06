CPP = g++
LINKER_CONFIG = -g -Wall -mavx
QUANT_VEC_PROJECT = quant_vec
TESTING_PROJECT = tester

quant_vector:
	${CPP} ${LINKER_CONFIG} -o ${QUANT_VEC_PROJECT} "${QUANT_VEC_PROJECT}.cpp"

testing:
	${CPP} ${LINKER_CONFIG} -o ${QUANT_VEC_PROJECT} "${TESTING_PROJECT}.cpp"