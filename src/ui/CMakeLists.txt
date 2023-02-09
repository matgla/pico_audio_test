add_library(pico_audio_ui STATIC)

add_library(pico_audio::ui ALIAS pico_audio_ui)

target_sources(pico_audio_ui 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/ui/app.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/argument_helpers.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sine_command.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/argument_helpers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sine_command.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
)

target_link_libraries(pico_audio_ui 
    PUBLIC
        eul_functional
    PRIVATE 
        common_flags
)

target_include_directories(pico_audio_ui 
    PUBLIC  
        ${PROJECT_SOURCE_DIR}/src/ui/include
)