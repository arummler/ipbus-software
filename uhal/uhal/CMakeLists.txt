find_package(pugixml REQUIRED)

add_library(cactus_uhal_uhal SHARED 
	src/common/Buffers.cpp 
	src/common/ClientInterface.cpp 
	src/common/DerivedNodeFactory.cpp 
	src/common/Node.cpp 
	src/common/ProtocolControlHub.cpp 
	src/common/Utilities.cpp 
	src/common/logo.cpp 
	src/common/ClientFactory.cpp 
	src/common/ConnectionManager.cpp 
	src/common/HwInterface.cpp 
	src/common/NodeTreeBuilder.cpp 
	src/common/ProtocolIPbusCore.cpp 
	src/common/ValMem.cpp 
)

target_include_directories(cactus_uhal_uhal PUBLIC include include/uhal/TemplateDefintions)

target_link_libraries(cactus_uhal_uhal cactus_uhal_log cactus_uhal_grammars)

install(TARGETS cactus_uhal_uhal
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

file(GLOB INC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/uhal/uhal/*")
install(FILES ${INC_FILES} DESTINATION include/uhal/uhal)
