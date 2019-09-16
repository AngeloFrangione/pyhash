cmake_minimum_required(VERSION 3.10)
# add_definitions(-DG_LOG_DOMAIN="oio.ecp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -fPIC")

include_directories(BEFORE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_BINARY_DIR})

# include_directories(AFTER
# 		${GLIB2_INCLUDE_DIRS}
# 		${CURL_INCLUDE_DIRS}
# 		${JSONC_INCLUDE_DIRS})

# link_directories(
# 		${GLIB2_LIBRARY_DIRS}
# 		${CURL_LIBRARY_DIRS}
# 		${JSONC_LIBRARY_DIRS})

add_library(hasher SHARED chasher.cpp hasher.cpp)

set_target_properties(hasher PROPERTIES PUBLIC_HEADER "chasher.h" VERSION 0.0.0 SOVERSION 0)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
target_include_directories(hasher PRIVATE ${GLIB_INCLUDE_DIRS})


target_link_libraries(hasher
		${JSONC_LIBRARIES} ${GLIB2_LIBRARIES}
		${EC_LIBRARIES} ${PYTHON_LIBRARIES} ${GLIB_LDFLAGS} -lcrypto)


install(TARGETS hasher
		LIBRARY DESTINATION /lib
		PUBLIC_HEADER DESTINATION include)

