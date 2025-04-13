cmake_minimum_required(VERSION 3.10)
project(bigint_project)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем библиотеку из наших файлов
add_library(bigint STATIC bigint.cpp bigint.hpp)

# Создаем исполняемый файл
add_executable(example example.cpp)

# Связываем библиотеку с исполняемым файлом
target_link_libraries(example bigint)

# Включаем директорию с заголовками
target_include_directories(bigint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
