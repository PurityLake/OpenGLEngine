if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(ASSIMP_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(ASSIMP_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	
if(WIN32)
	set(ASSIMP_ROOT_DIR "$ENV{ASSIMP_ROOT_DIR}")

	# Find path of each library
	find_path(ASSIMP_INCLUDE_DIR
		NAMES
			assimp/anim.h
		HINTS
			${ASSIMP_ROOT_DIR}/include
	)

	if(MSVC12)
		set(ASSIMP_MSVC_VERSION "vc120")
	elseif(MSVC14)	
		set(ASSIMP_MSVC_VERSION "vc140")
	elseif(MSVC15)	
		set(ASSIMP_MSVC_VERSION "vc150")
	elseif(MSVC16)	
		set(ASSIMP_MSVC_VERSION "vc160")
	elseif(MSVC17)	
		set(ASSIMP_MSVC_VERSION "vc170")
	endif(MSVC12)
	
	if(MSVC_TOOLSET_VERSION)
	
		find_path(ASSIMP_LIBRARY_DIR
			NAMES
				assimp-vc${MSVC_TOOLSET_VERSION}-mt.lib
			HINTS
				${ASSIMP_ROOT_DIR}/lib
		)
		
		find_library(ASSIMP_LIBRARY_RELEASE				assimp-vc${MSVC_TOOLSET_VERSION}-mt.lib 			PATHS ${ASSIMP_LIBRARY_DIR})
		find_library(ASSIMP_LIBRARY_DEBUG				assimp-vc${MSVC_TOOLSET_VERSION}-mtd.lib			PATHS ${ASSIMP_LIBRARY_DIR})
		
		set(ASSIMP_LIBRARY 
			optimized 	${ASSIMP_LIBRARY_RELEASE}
			debug		${ASSIMP_LIBRARY_DEBUG}
		)
		
		set(ASSIMP_LIBRARIES "ASSIMP_LIBRARY_RELEASE" "ASSIMP_LIBRARY_DEBUG")
	endif(MSVC_TOOLSET_VERSION)
	
else(WIN32)

	find_path(
	  ASSIMP_INCLUDE_DIRS
	  NAMES assimp/postprocess.h assimp/scene.h assimp/version.h assimp/config.h assimp/cimport.h
	  PATHS /usr/local/include
	  PATHS /usr/include/

	)

	find_library(
	  ASSIMP_LIBRARIES
	  NAMES assimp
	  PATHS /usr/local/lib/
	  PATHS /usr/lib64/
	  PATHS /usr/lib/
	)

	if (ASSIMP_INCLUDE_DIRS AND assimp_LIBRARIES)
	  SET(ASSIMP_FOUND TRUE)
	ENDIF (ASSIMP_INCLUDE_DIRS AND assimp_LIBRARIES)

	if (ASSIMP_FOUND)
	  if (NOT ASSIMP_FIND_QUIETLY)
		message(STATUS "Found asset importer library: ${ASSIMP_LIBRARIES}")
	  endif (NOT ASSIMP_FIND_QUIETLY)
	else (ASSIMP_FOUND)
	  if (ASSIMP_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find asset importer library")
	  endif (ASSIMP_FIND_REQUIRED)
	endif (ASSIMP_FOUND)
	
endif(WIN32)
