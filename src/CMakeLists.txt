add_library(libjsonparser STATIC scanner.cc parser.cc)

target_include_directories(libjsonparser PUBLIC
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)

add_executable(json_parser run.cc)
target_include_directories(json_parser PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)

target_link_libraries(json_parser PUBLIC libjsonparser)