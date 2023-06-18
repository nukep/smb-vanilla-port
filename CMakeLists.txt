# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("smbport")


add_subdirectory( Nes_Snd_Emu )

find_package(SDL2 REQUIRED)
find_package(OpenGL)
find_package(GLEW)
include_directories(smbport ${SDL2_INCLUDE_DIRS})
include_directories(smbport ${GLEW_INCLUDE_DIRS})

add_library(smbcore STATIC "src/foundation.cpp" "src/common.cpp" "src/smb1.cpp" "src/smb2j.cpp")

# Add source to this project's executable.
add_executable(smbport "src/main_sdl.c" "src/movie.c" "src/audio.cpp" "src/time.c" "src/render_opengl.c"  "src/render_raster.c" "src/thirdparty/ini.c")

target_link_libraries(smbport smbcore)
target_link_libraries(smbport ${SDL2_LIBRARIES})
target_link_libraries(smbport ${OPENGL_LIBRARIES})
target_link_libraries(smbport ${GLEW_LIBRARIES})
target_link_libraries(smbport Nes_Snd_Emu)


add_executable(smbport-testrunner "src/main_testrunner.c"  "src/movie.c")
target_link_libraries(smbport-testrunner smbcore)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET smbport PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
