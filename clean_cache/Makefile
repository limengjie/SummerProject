MKFILE = Makefile

COMPILECPP = g++ -g -O0 -Wall -Wextra -rdynamic -std=gnu++11
CPPSOURCE  = cl_cache.cpp
CPPHEADER  = 
EXECBIN    = cl_cache
OBJECTS    = ${CPPSOURCE:.cpp=.o}

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS}

%.o : %.cpp
	${COMPILECPP} -c $<

clean:
	- rm ${OBJECTS} ${EXECBIN}
