INCLUDE_DIRECTORIES(
    BEFORE .
)

SET(XTool_SRCS
    xmath.cpp
    XBUFFER/XBCNVIN.CPP
    XBUFFER/XBCNVOUT.CPP
    XBUFFER/XBCORE.CPP
    XBUFFER/XBSEARCH.CPP
    XSTREAM/XSCNVOUT.CPP
    XSTREAM/XSINPUT.CPP
    XSTREAM/XSSERV.CPP
    XSTREAM/XSRDWR.CPP
    XSTREAM/XSCNVIN.CPP
    XSTREAM/XSENLV.CPP
    XSTREAM/XSCORE.CPP
    XSTREAM/XSOUTPUT.CPP
    xerrhand.cpp
    XUTIL/XUTIL.CPP
    XUTIL/XClock.cpp
)

SET(XTool_LINK_LIBS)

IF(NOT MSVC_CL_BUILD)
    IF(PERIMETER_WINDOWS)
        #Use Backtrace in MinGW/MSYS
        FIND_PACKAGE(Backtrace)
        IF(Backtrace_FOUND)
            ADD_DEFINITIONS(-DBOOST_STACKTRACE_USE_BACKTRACE)
            SET(XTool_LINK_LIBS ${XTool_LINK_LIBS} ${Backtrace_LIBRARIES})
        ENDIF()
    ELSE()
        #Use ADDR2LINE in POSIX
        ADD_DEFINITIONS(-DBOOST_STACKTRACE_USE_ADDR2LINE)
        # dl is required for dladdr in stacktrace
        SET(XTool_LINK_LIBS ${XTool_LINK_LIBS} dl)
    ENDIF()
ENDIF()

ADD_LIBRARY(XTool STATIC ${XTool_SRCS})
TARGET_LINK_LIBRARIES(XTool ${XTool_LINK_LIBS})
