add_library(cos_plugin SHARED cos_plugin.cpp)

target_include_directories(cos_plugin PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(cos_plugin PROPERTIES
    DEFINE_SYMBOL BUILDING_PLUGIN_DLL
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins
)
