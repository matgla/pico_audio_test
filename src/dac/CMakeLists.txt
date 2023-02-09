add_library(pico_audio_dac STATIC)
add_library(pico_audio::dac ALIAS pico_audio_dac)

target_sources(pico_audio_dac
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dac/dac.hpp 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/dac.cpp
)

target_link_libraries(pico_audio_dac 
    PRIVATE 
        common_flags_pico
        hardware_irq
        hardware_clocks
        hardware_gpio
        hardware_pwm
)

target_include_directories(pico_audio_dac 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/src/dac/include
)