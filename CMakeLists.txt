cmake_minimum_required(VERSION 3.17)
project(class_protect)
link_directories("C:/RT/msys64/mingw64/lib")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D FREEGLUT_STATIC")
add_executable(class_protect main.cpp
        List/LinkList.h
        DTO/Initmap.cpp
        DTO/DTO.h DTO/DTO.cpp
        config.h
        GUI/GUI.cpp GUI/GUI.h
        ToolFunction/toolsFunction.cpp
        ReadIndex/readExcel.cpp
        KeyEvent/KeyEvent.h KeyEvent/KeyEvent.cpp)
target_link_libraries(class_protect freeglut_static opengl32 winmm gdi32 glu32.lib graphics64 uuid msimg32 imm32 ole32 oleaut32 gdiplus)
