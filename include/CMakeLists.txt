file(GLOB_RECURSE _headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.h)
target_sources(libjsonparser PUBLIC ${_headers})
unset(_headers)