﻿cmake_minimum_required(VERSION 3.10)
project(MyNeuroLib)

# Добавляем библиотеку из файлов в подпапке NeuroLib
add_library(NeuroLib SHARED 
	   
	"NeuroLib/Synapse/Synapse.cpp" 
	"NeuroLib/Neuron/Neuron.cpp"  
	"NeuroLib/Signal/Signal.cpp"  
	"NeuroLib/Network/Network.cpp"  
	"NeuroLib/Network/PyNetwork.cpp" 
	"NeuroLib/Network/SimpleForwardNetwork/SimpleForwardNetwork.cpp" 
	"NeuroLib/Network/SimpleForwardNetwork/PySimpleForwardNetwork.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Указываем путь к заголовочному файлу для использования в других проектах
target_include_directories(NeuroLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/NeuroLib)

# Определяем исполняемый файл main.cpp, который будет использовать эту библиотеку
add_executable(main_exec main.cpp  
	"NeuroLib/Synapse/Synapse.cpp" 
	"NeuroLib/Neuron/Neuron.cpp" 
	"NeuroLib/Signal/Signal.cpp" 
	"NeuroLib/Network/Network.cpp"  
	"NeuroLib/Network/PyNetwork.cpp" 
	"NeuroLib/Network/SimpleForwardNetwork/SimpleForwardNetwork.cpp" 
	"NeuroLib/Network/SimpleForwardNetwork/PySimpleForwardNetwork.cpp")

# Связываем библиотеку NeuroLib с исполняемым файлом main_exec
target_link_libraries(main_exec NeuroLib)