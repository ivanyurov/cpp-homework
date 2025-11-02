add_library(tg_plugin SHARED tg_plugin.cpp)

target_include_directories(tg_plugin PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(tg_plugin PROPERTIES
    DEFINE_SYMBOL BUILDING_PLUGIN_DLL
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins
)