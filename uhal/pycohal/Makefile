BUILD_HOME = $(shell pwd)/../..

include $(BUILD_HOME)/config/Makefile.macros

PACKAGE_VER_MAJOR = 2
PACKAGE_VER_MINOR = 5
PACKAGE_VER_PATCH = 1
PACKAGE_RELEASE = 1

PYTHON_VERSION = $(shell python -c "import sys; print str(sys.version_info[0]) + '.' + str(sys.version_info[1])")

PYTHON_LIB=python${PYTHON_VERSION}

export CACTUS_ROOT
export PACKAGE_VER_MAJOR PACKAGE_VER_MINOR PACKAGE_VER_PATCH


BINDINGS_SOURCES = $(wildcard src/common/*.cpp)
BINDINGS_OBJECT_FILES = $(patsubst src/common/%.cpp,obj/%.o,${BINDINGS_SOURCES})
BINDINGS_LIB = pkg/uhal/_core.so

LIBRARY_PATH = \
		${EXTERN_BOOST_LIB_PREFIX} \
		${EXTERN_PUGIXML_LIB_PREFIX} \
		${UHAL_UHAL_LIB_PREFIX} \
		${UHAL_LOG_LIB_PREFIX} \
		${UHAL_GRAMMARS_LIB_PREFIX} \
		${PYTHON_LIB_PREFIX}
LIBRARY_PATH := $(addprefix -L,$(LIBRARY_PATH))


BINDING_LIBRARIES = 	\
			-lpthread \
			-ldl \
			-lutil \
			-l${PYTHON_LIB} \
			\
			-lboost_filesystem \
			-lboost_python \
			-lboost_regex \
			-lboost_system \
			-lboost_thread \
			\
			-l${PUGIXML_LIB_NAME} \
			-lcactus_uhal_grammars \
			-lcactus_uhal_log \
			-lcactus_uhal_uhal


INCLUDE_PATH = include  \
				${EXTERN_BOOST_INCLUDE_PREFIX} \
				${PYTHON_INCLUDE_PREFIX} \
				${EXTERN_PUGIXML_INCLUDE_PREFIX}  \
				${UHAL_UHAL_INCLUDE_PREFIX}  \
				${UHAL_LOG_INCLUDE_PREFIX}  \
				${UHAL_GRAMMARS_INCLUDE_PREFIX} 
INCLUDE_PATH := $(addprefix -I,$(INCLUDE_PATH))

CPP_FLAGS = -g -Wall -pedantic -MMD -MP -fPIC ${INCLUDE_PATH}

LINK_BINDINGS_FLAGS_COMMON = -shared -fPIC -Wall -g ${LIBRARY_PATH}  ${BINDING_LIBRARIES}

ifeq (${CACTUS_OS},osx)
  LINK_BINDINGS_FLAGS = ${LINK_BINDINGS_FLAGS_COMMON}
  CPP_FLAGS += -Wno-c++11-extensions
else
  LINK_BINDINGS_FLAGS = ${LINK_BINDINGS_FLAGS_COMMON} -Wl,-h -Wl,-Bstatic -Wl,-Bdynamic
endif

.PHONY: all _all clean _cleanall build _buildall install _installall rpm _rpmall test _testall spec_update generator

default: build

clean: _cleanall
_cleanall:
	rm -rf ${RPMBUILD_DIR}
	rm -rf obj
	rm -rf ${BINDINGS_LIB}
	rm -rf build dist MANIFEST

all: _all
build: _all
buildall: _all
_all: ${BINDINGS_LIB}	

#Library will be compiled and will be packaged
${BINDINGS_LIB}: ${BINDINGS_OBJECT_FILES}
	g++ ${LINK_BINDINGS_FLAGS} ${BINDINGS_OBJECT_FILES} -o $@

${BINDINGS_OBJECT_FILES}: obj/%.o : src/common/%.cpp
	mkdir -p obj
	g++ -c ${CPP_FLAGS} -ftemplate-depth-128 -O0 -rdynamic -finline-functions -Wno-inline -DNDEBUG  $< -o $@	

-include $(BINDINGS_OBJECT_FILES:.o=.d)	

rpm: _rpmall
_rpmall: ${BINDINGS_LIB}
	rm -rf /var/tmp/cactus*
	$(eval LIB_DEPENDENCIES := $(shell ldd ${BINDINGS_LIB} | sed -n 's/\s*\(libboost_python.so[^ ]*\).*/\1()(64bit)/p'))
	$(eval LIB_DEPENDENCIES += $(shell ldd ${BINDINGS_LIB} | sed -n 's/\s*\(libcactus_uhal_uhal.so[^ ]*\).*/\1()(64bit)/p'))
	$(info LIB_DEPENDENCIES=${LIB_DEPENDENCIES})
	python setup.py bdist_rpm --binary-only --force-arch=`uname -m` --requires "${LIB_DEPENDENCIES}" \
	        --release ${PACKAGE_RELEASE}.${CACTUS_OS}.python${PYTHON_VERSION}


