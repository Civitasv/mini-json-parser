add_executable(test_scanner test_scanner.cc)
target_link_libraries(test_scanner PUBLIC libjsonparser)

target_include_directories(test_scanner PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)

add_executable(test_parser test_parser.cc)
target_link_libraries(test_parser PUBLIC libjsonparser)

target_include_directories(test_parser PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)