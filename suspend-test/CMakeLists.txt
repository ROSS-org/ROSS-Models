INCLUDE_DIRECTORIES(${ROSS_SOURCE_DIR} ${ROSS_BINARY_DIR})
## Must include binary dir for config.h

## If you will be using the RIO library add this
#INCLUDE_DIRECTORIES(${RIO_SOURCE_DIR} ${RIO_BINARY_DIR})

## Model Version
LIST(APPEND CMAKE_MODULE_PATH "${ROSS_SOURCE_DIR}/cmake/")
INCLUDE(GetGitRevisionDescription)
GET_GIT_HEAD_REVISION(GIT_RESPEC_SUSPEND GIT_SHA1_SUSPEND)

## Build Configuration Header File
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/suspend_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/suspend_config.h @ONLY)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/suspend_config.h.in PROPERTIES GENERATED FALSE)
SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/suspend_config.h PROPERTIES GENERATED TRUE)

# All source files for the model
SET(suspend_srcs
	suspend_main.c
	increment_driver.c
	decrement_driver.c
	receiver_driver.c
	suspend_map.c
	suspend.h
	suspend_config.h
)

# Set the executable name here: suspend
# You will be executing the ./suspend binary
ADD_EXECUTABLE(suspend ${suspend_srcs})

ADD_TEST(suspend_test mpirun -np 2 ./suspend --synch=3 --nkp=2)

TARGET_LINK_LIBRARIES(suspend ROSS m)
## Alternatively, use this command with RIO
#TARGET_LINK_LIBRARIES(suspend ROSS RIO m)
