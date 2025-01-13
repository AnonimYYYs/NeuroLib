cmake_minimum_required(VERSION 3.10)
project(MyNeuroLib)

# Добавляем библиотеку из файлов в подпапке NeuroLib
add_library(NeuroLib SHARED NeuroLib/NeuroLib.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Указываем путь к заголовочному файлу для использования в других проектах
target_include_directories(NeuroLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/NeuroLib)

# Определяем исполняемый файл main.cpp, который будет использовать эту библиотеку
add_executable(main_exec main.cpp)

# Связываем библиотеку NeuroLib с исполняемым файлом main_exec
target_link_libraries(main_exec NeuroLib)