cmake_minimum_required(VERSION 3.10)

# Указываем название проекта
project(ProcessManager)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем папки, где будут лежать файлы
include_directories(${PROJECT_SOURCE_DIR}/include)

# Добавляем исходные файлы для библиотеки
add_library(process_manager STATIC
    src/process_manager.cpp
)

# Добавляем тестовую программу
add_executable(test_program tests/main.cpp)

# Линкуем библиотеку к тестовой программе
target_link_libraries(test_program process_manager)

# Для кроссплатформенности можно добавлять дополнительные флаги или настройки
# В случае необходимости — конкретные флаги для компиляции на Windows или Linux
