add_rules("mode.debug", "mode.release")

target("bc_runner")
    add_cxxflags("/std:c++17")
    set_kind("binary")
    add_files("src/*.cpp")
target_end()
