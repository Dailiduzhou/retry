set_project("studentmgr")
set_version("0.1.0")
set_languages("c++11")

set_warnings("all", "extra")
add_rules("mode.debug", "mode.release")

add_requires("sqlite3")

target("studentmgr")
set_kind("binary")
add_includedirs("include")
add_files("src/*.cpp")
add_packages("sqlite3")

