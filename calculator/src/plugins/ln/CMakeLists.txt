add_library(ln_plugin SHARED ln_plugin.cpp)

target_include_directories(ln_plugin PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(ln_plugin PROPERTIES
    DEFINE_SYMBOL BUILDING_PLUGIN_DLL
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/plugins
)
