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

target_include_directories(cactus_uhal_grammars PUBLIC include)

install(TARGETS cactus_uhal_grammars
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

file(GLOB INC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/uhal/grammars/*")
install(FILES ${INC_FILES} DESTINATION include/uhal/grammars)
