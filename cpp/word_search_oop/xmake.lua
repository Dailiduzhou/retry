set_project("word_search_oop")
set_version("0.1.0")
set_languages("c++17")

add_rules("mode.debug", "mode.release")

target("word_search_oop")
    set_kind("binary")
    add_includedirs("include")
    add_files("src/*.cpp", "main.cpp")
