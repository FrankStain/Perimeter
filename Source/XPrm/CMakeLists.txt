INCLUDE_DIRECTORIES(
    BEFORE .
    "${PROJECT_SOURCE_DIR}/Source/XTool"
    "${PROJECT_SOURCE_DIR}/Source/Util"
)

SET(XPrm_SRCS
    StdAfx.cpp
    Token.cpp
)

SET(XPrm_LINK_LIBS XTool ${SDL2_LIBRARY})

IF(PERIMETER_DEBUG)
    SET(XPrm_SRCS ${XPrm_SRCS} RunTimeCompiler.cpp)
ENDIF()
IF(PERIMETER_EXODUS)
    SET(XPrm_LINK_LIBS ${XPrm_LINK_LIBS} Exodus)
ENDIF()

ADD_EXECUTABLE(XPrm ${XPrm_SRCS} XPrm.cpp)
TARGET_LINK_LIBRARIES(XPrm ${XPrm_LINK_LIBS})

IF(PERIMETER_DEBUG)
    ADD_LIBRARY(XPrmLib STATIC ${XPrm_SRCS})
    TARGET_LINK_LIBRARIES(XPrmLib ${XPrm_LINK_LIBS})
ENDIF()
