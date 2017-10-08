add_library(cactus_uhal_grammars SHARED 
	src/common/HttpResponseGrammar.cpp 
	src/common/NodeTreeFirmwareInfoAttributeGrammar.cpp 
	src/common/OldHalAddressFileGrammar.cpp 
	src/common/URI.cpp 
	src/common/NodeTreeClassAttributeGrammar.cpp 
	src/common/NodeTreeParametersGrammar.cpp 
	src/common/SemicolonDelimitedUriListGrammar.cpp 
	src/common/URLGrammar.cpp 
)

find_package(Boost 1.53)
	     
target_include_directories(cactus_uhal_grammars PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:include/uhal>
    $<INSTALL_INTERFACE:include/uhal/grammars>)

install(TARGETS cactus_uhal_grammars EXPORT cactus_uhal_grammarsConfig
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

file(GLOB INC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/uhal/grammars/*")
install(FILES ${INC_FILES} DESTINATION include/uhal/grammars)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT cactus_uhal_grammarsConfig DESTINATION share/cactus_uhal_grammars/cmake)

# This makes the project importable from the build directory
export(TARGETS cactus_uhal_grammars FILE cactus_uhal_grammarsConfig.cmake)

