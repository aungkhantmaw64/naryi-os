target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(app PRIVATE
                  ${CMAKE_CURRENT_SOURCE_DIR}/screen_manager.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/screen_api.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/watchface.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/obitron_47.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/assets/images/wavy_bg.c)
