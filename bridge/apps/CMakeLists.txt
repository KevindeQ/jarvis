add_executable (bridge bridge.cpp bridge_app.cpp bridge_app.h)

target_compile_features(bridge PRIVATE cxx_std_17)

target_link_libraries(bridge bridge_lib)