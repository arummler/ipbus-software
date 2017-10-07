set(MAX_NUM_ARGS "32")
configure_file(src/common/generator.cxx.in src/common/generator.cxx @ONLY)

set(USE_BACKTRACE FALSE)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/uhal/log)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/src/common)

find_package(Boost 1.53 REQUIRED COMPONENTS
             thread system)
	     
ADD_EXECUTABLE(generator ${CMAKE_CURRENT_BINARY_DIR}/src/common/generator.cxx)
set_target_properties(generator PROPERTIES LINKER_LANGUAGE CXX)
#GET_TARGET_PROPERTY(GENERATOR_EXE generator LOCATION)
ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/uhal/log/log.hpp ${CMAKE_CURRENT_BINARY_DIR}/include/uhal/log/log.hxx ${CMAKE_CURRENT_BINARY_DIR}/src/common/log.cpp
   COMMAND generator ${CMAKE_CURRENT_BINARY_DIR}/include/uhal/log/log.hpp ${CMAKE_CURRENT_BINARY_DIR}/include/uhal/log/log.hxx ${CMAKE_CURRENT_BINARY_DIR}/src/common/log.cpp
   DEPENDS generator
)
   
add_library(cactus_uhal_log SHARED 
	src/common/BacktraceSymbols.cpp 
	src/common/LogLevels.cpp 
	src/common/log_inserters.integer.cpp 
	src/common/log_inserters.quote.cpp 
	src/common/log_inserters.time.cpp 
	src/common/GccOutputCleaner.cpp 
	src/common/exception.cpp 
	src/common/log_inserters.location.cpp 
	src/common/log_inserters.threadID.cpp 
	${CMAKE_CURRENT_BINARY_DIR}/src/common/log.cpp
)

target_include_directories(cactus_uhal_log PUBLIC include ${Boost_INCLUDE_DIRS})

#target_link_libraries(cactus_uhal_log ${Boost_thread_LIBRARY} ${Boost_system_LIBRARY})
target_link_libraries(cactus_uhal_log ${Boost_libraries})


