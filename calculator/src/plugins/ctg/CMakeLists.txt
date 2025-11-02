add_library(ctg_plugin SHARED ctg_plugin.cpp)

target_include_directories(ctg_plugin PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(ctg_plugin PROPERTIES
    DEFINE_SYMBOL BUILDING_PLUGIN_DLL
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins
)