add_library(arch_rp2040_mmc)

pico_generate_pio_header(arch_rp2040_mmc ${CMAKE_CURRENT_SOURCE_DIR}/mmc_spi.pio)

set (include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include/arch/rp2040/mmc)

target_sources(arch_rp2040_mmc 
    PUBLIC 
        ${include_dir}/mmc.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/mmc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mmc_spi.cpp
)

target_link_libraries(arch_rp2040_mmc 
    PRIVATE 
        common_flags 
        hardware_pio_headers
)

target_include_directories(arch_rp2040_mmc
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

