find_package(pugixml REQUIRED)
#find_package(cactus_uhal_log REQUIRED)
#find_package(cactus_uhal_grammars REQUIRED)
find_package(Boost 1.53 REQUIRED COMPONENTS
             thread system filesystem )

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
# $<TARGET_PROPERTY:cactus_uhal_log,INTERFACE_INCLUDE_DIRECTORIES>
# $<TARGET_PROPERTY:cactus_uhal_grammars,INTERFACE_INCLUDE_DIRECTORIES>
# workaround https://gitlab.kitware.com/cmake/cmake/issues/16610 ? not really feasible as it results in PUBLIC linking, need to wait for future cmake version and demand log and grammars explicitly in consumer
# https://gitlab.kitware.com/cmake/cmake/issues/16324
# https://gitlab.kitware.com/cmake/cmake/issues/14778
target_include_directories(cactus_uhal_uhal PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/uhal/TemplateDefinitions>
    $<INSTALL_INTERFACE:include/uhal>
    $<INSTALL_INTERFACE:include/uhal/uhal>
    $<INSTALL_INTERFACE:include/uhal/uhal/TemplateDefinitions>
)

target_link_libraries(cactus_uhal_uhal PUBLIC cactus_uhal_log cactus_uhal_grammars INTERFACE boost_thread boost_system boost_filesystem )

install(TARGETS cactus_uhal_uhal EXPORT cactus_uhal_uhalConfig
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

file(GLOB INC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/uhal/*.hpp")
install(FILES ${INC_FILES} DESTINATION include/uhal/uhal)

file(GLOB INC_FILES2 "${CMAKE_CURRENT_SOURCE_DIR}/include/uhal/TemplateDefinitions/*")
install(FILES ${INC_FILES2} DESTINATION include/uhal/uhal/TemplateDefinitions)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT cactus_uhal_uhalConfig 
	DESTINATION share/cactus_uhal_uhal/cmake
	EXPORT_LINK_INTERFACE_LIBRARIES)

# This makes the project importable from the build directory
export(TARGETS cactus_uhal_uhal  
	FILE cactus_uhal_uhalConfig.cmake
	EXPORT_LINK_INTERFACE_LIBRARIES)



