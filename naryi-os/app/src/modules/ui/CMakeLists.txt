target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(apps)

target_sources(app PRIVATE
                  ${CMAKE_CURRENT_SOURCE_DIR}/app_manager.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/app.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/display_ctrl.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/obitron_47.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/assets/images/wavy_bg.c)
