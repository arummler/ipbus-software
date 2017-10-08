set(MAX_NUM_ARGS "32")
configure_file(src/common/generator.cxx.in src/common/generator.cxx @ONLY)

set(USE_BACKTRACE FALSE)

# If we have compiler requirements for this library, list them
# here
#target_compile_features(lib
#    PUBLIC cxx_auto_type
#    PRIVATE cxx_variadic_templates)

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

target_include_directories(cactus_uhal_log PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:include/uhal>
    $<INSTALL_INTERFACE:include/uhal/log>)

#target_link_libraries(cactus_uhal_log ${Boost_thread_LIBRARY} ${Boost_system_LIBRARY})
target_link_libraries(cactus_uhal_log INTERFACE boost_thread boost_system)

install(TARGETS cactus_uhal_log EXPORT cactus_uhal_logConfig
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

file(GLOB INC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/uhal/log/*")
install(FILES ${INC_FILES} DESTINATION include/uhal/log)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT cactus_uhal_logConfig DESTINATION share/cactus_uhal_log/cmake)

# This makes the project importable from the build directory
export(TARGETS cactus_uhal_log  FILE cactus_uhal_logConfig.cmake)



