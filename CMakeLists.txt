cmake_minimum_required(VERSION 3.0)

find_package(PkgConfig)

pkg_check_modules(RPIMEMMGR librpimemmgr>=2.0.1)
if (NOT RPIMEMMGR_FOUND)
    message(STATUS "Adding /opt/vc/lib/pkgconfig to PKG_CONFIG_PATH")
    set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/opt/vc/lib/pkgconfig")
    pkg_check_modules(RPIMEMMGR librpimemmgr>=2.0.1)
    if (NOT RPIMEMMGR_FOUND)
        message(FATAL_ERROR "bcm_host not found even in /opt/vc/lib")
    endif ()
endif ()

pkg_check_modules(MAILBOX REQUIRED libmailbox>=3.0.1)

set(CMAKE_C_FLAFS "${CMAKE_C_FLAGS} -W -Wall -Wextra -pipe -O2 -g")
add_executable(vpuid main.c)
target_include_directories(vpuid PRIVATE "${RPIMEMMGR_INCLUDE_DIRS}"
                                         "${MAILBOX_INCLUDE_DIRS}")
target_compile_options(vpuid PRIVATE "${RPIMEMMGR_CFLAGS_OTHER}"
                                     "${MAILBOX_CFLAGS_OTHER}")
target_link_libraries(vpuid PRIVATE "${RPIMEMMGR_LDFLAGS} ${MAILBOX_CFLAGS}")
