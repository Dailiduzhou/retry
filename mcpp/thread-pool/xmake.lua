add_rules("mode.debug", "mode.release")

set_languages("c++17")
set_warnings("all")

target("thread-pool")
    set_kind("binary")
    add_files("src/*.cpp")
    add_syslinks("pthread")
