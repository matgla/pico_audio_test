add_executable(audio_test)

target_sources(audio_test
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(audio_test
    PRIVATE
        common_flags

        pico_stdlib
)



pico_add_extra_outputs(audio_test)

