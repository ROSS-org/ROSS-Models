INCLUDE_DIRECTORIES(${ROSS_BINARY_DIR})
IF(BGPM)
	INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR} ${BGPM_LIB})
ELSE(NOT(BGPM))
	INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR})
ENDIF(BGPM)

SET(dphold_srcs
dphold.c		dphold.h)

ADD_EXECUTABLE(dphold ${dphold_srcs})

IF(BGPM)
	TARGET_LINK_LIBRARIES(dphold ROSS imp_bgpm m)   
ELSE(NOT(BGPM))
	TARGET_LINK_LIBRARIES(dphold ROSS m)   
ENDIF(BGPM)

add_test(NAME conservative
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND mpirun -np 2 ./dphold --synch=2 --lookahead=0.0001 --end=10000.0)

add_test(NAME optimistic
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND mpirun -np 2 ./dphold --synch=3 --lookahead=0.0001 --end=10000.0 --buddy_size=20)
