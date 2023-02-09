find_package(eul REQUIRED)

set (target_arch rp2040)

add_subdirectory(arch)
add_subdirectory(dac)
add_subdirectory(ui)

add_executable(audio_test)

target_sources(audio_test
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(audio_test
    PRIVATE
        pico_audio::arch
        pico_audio::dac
        pico_audio::ui
        
        fatfs
    
        pico_stdlib
        pico_audio_pwm
        pico_sd_card
        eul_container
)

target_compile_definitions(audio_test
    PRIVATE     
        USE_AUDIO_PWM=1
        USE_AUDIO_I2S=0
        USE_AUDIO_SPDIF=0
        PICO_AUDIO_PWM_L_PIN=2
        PICO_AUDIO_PWM_R_PIN=3
        PICO_SD_CLK_PIN=28
        PICO_SD_CMD_PIN=27
        PICO_SD_DAT0_PIN=18
)

target_compile_options(audio_test
    PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a -Wfloat-equal -Wshadow -Wundef -Wpointer-arith -Wcast-align -Wconversion -Wall
        -fno-exceptions>
        $<$<CONFIG:DEBUG>:-Og -g> 
        $<$<CONFIG:RELEASE>:-Os>
)

pico_add_extra_outputs(audio_test)



