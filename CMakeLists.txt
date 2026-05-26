cmake_minimum_required(VERSION 3.28)

project(launcher)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Widgets Core Multimedia MultimediaWidgets OpenGL OpenGLWidgets REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2MIXER REQUIRED SDL2_mixer)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${PROJECT_NAME}
src/main.cpp
src/MediaContainer.cpp
src/MediaContainer.hpp
src/MetaWidget.hpp
src/MyMenu.hpp
src/MyMenu.cpp
MyPictureWidget/demuxer.h
MyPictureWidget/public.h
MyPictureWidget/resampler.h
MyPictureWidget/videoWidget_gl.cc
MyPictureWidget/videoWidget_gl.h
MyPictureWidget/audioWidget_sdl2.h
)

qt_add_resources(${PROJECT_NAME} resources.qrc)

target_link_libraries(${PROJECT_NAME}  PUBLIC Qt6::Core Qt6::Widgets Qt6::Multimedia Qt6::MultimediaWidgets Qt6::OpenGL Qt6::OpenGLWidgets OpenGL::GL OpenGL::GLU)

set(FFMPEG_INCLUDE_DIR "/usr/local/ffmpeg/include")
set(FFMPEG_LIB_DIR "/usr/local/ffmpeg/lib")
include_directories(${FFMPEG_INCLUDE_DIR})
link_directories(${FFMPEG_LIB_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC avformat avcodec avutil swscale swresample)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
)