INCLUDE_DIRECTORIES(
        BEFORE .
        "${PROJECT_SOURCE_DIR}/Source/XTool"
)

SET(PlayOgg_SRCS
        PlayOgg.cpp
)

ADD_LIBRARY(PlayOgg STATIC ${PlayOgg_SRCS})


IF(Vorbis_FOUND)
    ADD_DEFINITIONS(-DHAS_VORBIS)
    INCLUDE_DIRECTORIES(${VORBIS_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(PlayOgg ${VORBIS_LIBRARIES})
ELSE()
    MESSAGE("Vorbis library not found! No music available")
ENDIF()
