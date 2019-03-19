INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_TIMESVL timesvl)

FIND_PATH(
    TIMESVL_INCLUDE_DIRS
    NAMES timesvl/api.h
    HINTS $ENV{TIMESVL_DIR}/include
        ${PC_TIMESVL_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    TIMESVL_LIBRARIES
    NAMES gnuradio-timesvl
    HINTS $ENV{TIMESVL_DIR}/lib
        ${PC_TIMESVL_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TIMESVL DEFAULT_MSG TIMESVL_LIBRARIES TIMESVL_INCLUDE_DIRS)
MARK_AS_ADVANCED(TIMESVL_LIBRARIES TIMESVL_INCLUDE_DIRS)

