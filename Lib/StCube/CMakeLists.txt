cmake_minimum_required(VERSION 3.22)

include(${CMAKE_SOURCE_DIR}/Cmake/Utils/BuildOpts.cmake)

set(MCPU "-mcpu=cortex-m7" CACHE STRING "" FORCE)
set(MFPU "-mfpu=fpv5-d16" CACHE STRING "" FORCE)
set(MFLOAT_ABI "-mfloat-abi=hard" CACHE STRING "" FORCE)
set(MCU_DEVICE "STM32H743xx" CACHE STRING "" FORCE)
set(MCU_LINCER_SCRIPT
    "${CMAKE_CURRENT_SOURCE_DIR}/STM32H743IIKX_FLASH.ld"
    CACHE STRING "" FORCE
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    Core/Src/main.c
    Core/Src/stm32h7xx_hal_msp.c
    Core/Src/stm32h7xx_it.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c
    Core/Startup/startup_stm32h743iikx.s
    Core/Src/system_stm32h7xx.c
)

add_library(${PROJECT_NAME}StInterface INTERFACE)
target_add_CPU_flags(${PROJECT_NAME}StInterface)
target_include_directories(
    ${PROJECT_NAME}StInterface
    SYSTEM INTERFACE
    Core/Inc
    Drivers/CMSIS/Device/ST/STM32H7xx/Include
    Drivers/CMSIS/Include
    Drivers/STM32H7xx_HAL_Driver/Inc
    Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
)

file(GLOB_RECURSE ${PROJECT_NAME}StDriversSrc
    Drivers/STM32H7xx_HAL_Driver/Src/*.c
)

add_library(${PROJECT_NAME}StDrivers
    ${${PROJECT_NAME}StDriversSrc}
)

target_link_libraries(
    ${PROJECT_NAME}StDrivers
    ${PROJECT_NAME}StInterface
)
target_link_libraries(
    ${PROJECT_NAME}StInterface
    INTERFACE
    ${PROJECT_NAME}StDrivers
)