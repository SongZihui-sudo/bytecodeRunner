add_rules("mode.debug", "mode.release")

target("bc_runner")
    set_kind("binary")
    add_files("src/*.cpp")
target_end()
