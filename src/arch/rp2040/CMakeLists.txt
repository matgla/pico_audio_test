add_subdirectory(mmc)

add_library(arch_rp2040)

target_sources(arch_rp2040 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/file_io.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fatfs_glue.cpp
)

find_package(fatfs REQUIRED)

target_link_libraries(arch_rp2040
    PRIVATE 
        common_flags
        fatfs

        arch_rp2040_mmc
)

target_include_directories(arch_rp2040 SYSTEM 
    PUBLIC
        $<TARGET_PROPERTY:pico_sd_card_headers,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:pico_stdlib,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:fatfs,INCLUDE_DIRECTORIES>
)

add_library(pico_audio::arch ALIAS arch_rp2040)
