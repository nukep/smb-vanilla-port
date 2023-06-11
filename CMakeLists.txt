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
include_directories(smbport ${SDL2_INCLUDE_DIRS})

add_library(smb1 STATIC "src/smb1.cpp")

add_library(smb2j STATIC "src/smb2j.cpp")

add_library(foundation STATIC "src/foundation.cpp" "src/common.cpp")
target_link_libraries(foundation PRIVATE smb1 smb2j)

# Add source to this project's executable.
add_executable(smbport "src/main.c" "src/movie.c" "src/audio.cpp" "src/time.c")

target_link_libraries(smbport foundation)
target_link_libraries(smbport ${SDL2_LIBRARIES})
target_link_libraries(smbport Nes_Snd_Emu)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET smbport PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
