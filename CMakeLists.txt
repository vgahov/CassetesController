cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands")

project(CasseteController C CXX)

set(MCU atmega324pb)
#set(F_CPU 16000000UL)
set(F_CPU 1000000UL)

# Компилятори
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_SIZE avr-size)

# Стандарти
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Загальні прапори
add_compile_options(
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os
    -Wall
    -Wextra
    -g
    -H
)

add_compile_options(-H)

#set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

add_link_options(
    -mmcu=${MCU}
)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

message(STATUS "APP_SOURCES: ${APP_SOURCES}")

message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")


# ELF
add_executable(${PROJECT_NAME}.elf ${APP_SOURCES})
#add_executable(${PROJECT_NAME}.elf src/main.cpp src/system/systemfunc.cpp)

target_compile_options(${PROJECT_NAME}.elf PRIVATE -fno-threadsafe-statics )

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    F_CPU=${F_CPU}
)

# HEX
add_custom_command(
    TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    #COMMAND ${CMAKE_SIZE} --mcu=${MCU} --format=avr ${PROJECT_NAME}.elf
    COMMAND ${CMAKE_SIZE} -A ${PROJECT_NAME}.elf
    #COMMAND ${CMAKE_SIZE} --format=elf32-avr ${PROJECT_NAME}.elf
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)