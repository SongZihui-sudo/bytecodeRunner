add_rules("mode.debug", "mode.release")

target("bc_runner")
    on_load(function (target)
        target:set("languages", "c++17")
    end)
    set_kind("binary")
    add_files("src/*.cpp")
target_end()