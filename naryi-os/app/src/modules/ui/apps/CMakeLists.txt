target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(app PRIVATE
                  ${CMAKE_CURRENT_SOURCE_DIR}/watchface_app.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/settings_app.c
                  ${CMAKE_CURRENT_SOURCE_DIR}/music_app.c
              )
