cmake_minimum_required(VERSION 3.9)
# Compiler flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(APPLE)
  message("hello apple")
  set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Sanctum-of-Shadows)

#### setup Directories ####
#Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
# IRRLICHT
file(GLOB_RECURSE IRRLICHTSOURCES lib/irrlicht/source/Irrlicht/*.cpp lib/irrlicht/source/Irrlicht/*.h)
add_library(IRRLICHT STATIC ${IRRLICHTSOURCES})
set(IRRLICHT_INCS "${CMAKE_SOURCE_DIR}/lib/irrlicht/include")
#target_include_directories(IRRLICHT INTERFACE "${CMAKE_SOURCE_DIR}/lib/irrlicht/source/Irrlicht/" )
target_include_directories(IRRLICHT PUBLIC ${IRRLICHT_INCS})
#target_link_libraries(IRRLICHT gdi32 opengl32 d3dx9d winmm)
if (MSVC)
	target_compile_options(IRRLICHT PUBLIC "/MP")
	target_link_options(IRRLICHT PUBLIC -lgdi32 -lopengl32 -ld3dx9d -lwinmm -Wl --add-stdcall-alias)
	target_compile_definitions(IRRLICHT PUBLIC 
		NO_IRR_COMPILE_WITH_DIRECT3D_9_  
		NO_IRR_COMPILE_WITH_DIRECTINPUT_JOYSTICK_ 
		__GNUWIN32__ _WIN32 WIN32 _WINDOWS _MBCS _USRDLL
		_IRR_STATIC_LIB_
	)
endif()
target_compile_definitions(IRRLICHT PUBLIC
NO_IRR_COMPILE_WITH_LIBPNG_
NO_IRR_COMPILE_WITH_LIBJPEG_
NO__IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_
)


#add_subdirectory("lib/openal-soft" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
#set(openal-soft_INCS "lib/sfml/include")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# Bullet3

set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_CLSOCKET OFF CACHE BOOL "" FORCE)
set(USE_GLUT OFF CACHE BOOL "" FORCE)
add_subdirectory("lib/bullet3" EXCLUDE_FROM_ALL)
target_compile_options(BulletCollision PUBLIC "/MP")
target_compile_options(BulletDynamics PUBLIC "/MP")
target_compile_options(LinearMath PUBLIC "/MP")
set(BULLET_INCS "${CMAKE_SOURCE_DIR}/lib/bullet3/src")
#include_directories("lib/b2d/Box2D/")
#et(B2D_INCS "lib/b2d/Box2D/")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")


# openAL

set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL OFF CACHE BOOL "" FORCE)
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(ALSOFT_CONFIG OFF CACHE BOOL "" FORCE)
add_subdirectory("lib/openal-soft" EXCLUDE_FROM_ALL)
target_compile_options(OpenAL PUBLIC "/MP")
#include_directories("lib/b2d/Box2D/")
#et(B2D_INCS "lib/b2d/Box2D/")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Add Engine and our own library projects####

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####



file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(SANCTUM ${SOURCES} )
target_include_directories(SANCTUM SYSTEM PRIVATE ${IRRLICHT_INCS} ${BULLET_INCS})
target_link_libraries(SANCTUM OpenAL BulletCollision BulletDynamics LinearMath IRRLICHT)
set(EXECUTABLES ${EXECUTABLES} SANCTUM )


FOREACH(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO )
	IF(${flag_var} MATCHES "/MD")
		STRING(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
	ENDIF(${flag_var} MATCHES "/MD")
	IF(${flag_var} MATCHES "/MDd")
		STRING(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
	ENDIF(${flag_var} MATCHES "/MDd")
ENDFOREACH(flag_var)



#### Target for copying resources to build dir####
if(APPLE)
  add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resources" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/lib/sfml/extlibs/libs-osx/Frameworks" ${CMAKE_BINARY_DIR}/lib/sfml/Frameworks
  )
else()
  add_custom_target(copy_resources ALL 
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resources" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>
  )
endif()

#### Link Dependencies ####
foreach (exe ${EXECUTABLES})
  #set working directory to build dir
  set_target_properties(${exe} PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
  )

  if(MSVC) # Hide Console in release builds
    set_target_properties(${exe} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
  endif(MSVC)
  
 add_dependencies(${exe} copy_resources)
endforeach ()

