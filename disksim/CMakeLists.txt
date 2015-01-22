INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR} ${ROSS_BINARY_DIR})

SET(disksim_srcs
disksim.c disksim.h)

ADD_EXECUTABLE(disksim ${disksim_srcs})

TARGET_LINK_LIBRARIES(disksim ROSS m)
