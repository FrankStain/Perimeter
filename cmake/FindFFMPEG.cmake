# Locate the FFmpeg libraries
# This module defines
# {AVUTIL,AVCODEC,AVFORMAT}_INCLUDE_DIR
# {AVUTIL,AVCODEC,AVFORMAT}_LIBRARY
# FFMPEG_INCLUDE_DIRS
# FFMPEG_LIBRARIES
#

SET(FFMPEG_SEARCH_PATHS
		/usr/pkg/include/ffmpeg3/
		/local/bin
		/bin
		${FFMPEG_SEARCH_PATHS}
		${LIBRARY_SEARCH_PATHS}
)

FIND_PATH(AVUTIL_INCLUDE_DIR
	NAMES
		libavutil/avutil.h
	PATHS
		${FFMPEG_SEARCH_PATHS}
	PATH_SUFFIXES
		include
		include/ffmpeg
		ffmpeg
)

FIND_PATH(AVCODEC_INCLUDE_DIR
	NAMES
		libavcodec/avcodec.h
	PATHS
		${FFMPEG_SEARCH_PATHS}
	PATH_SUFFIXES
		include
		include/ffmpeg
		ffmpeg
)

FIND_PATH(AVFORMAT_INCLUDE_DIR
	NAMES
		libavformat/avformat.h
	PATHS
		${FFMPEG_SEARCH_PATHS}
	PATH_SUFFIXES
		include
		include/ffmpeg
		ffmpeg
)

FIND_LIBRARY(AVUTIL_LIBRARY
	NAMES
		avutil
		avutil-55
		avutil-56
	PATHS
		${FFMPEG_SEARCH_PATHS}
	PATH_SUFFIXES
		lib64
		lib
		lib64/ffmpeg
		lib/ffmpeg
)

FIND_LIBRARY(AVCODEC_LIBRARY
	NAMES
		avcodec
		avcodec-57
		avcodec-58
	PATHS
		${FFMPEG_SEARCH_PATHS}
	PATH_SUFFIXES
		lib64
		lib
		lib64/ffmpeg
		lib/ffmpeg
)

FIND_LIBRARY(AVFORMAT_LIBRARY
	NAMES
		avformat
		avformat-57
		avformat-58
	PATHS
		${FFMPEG_SEARCH_PATHS}
	PATH_SUFFIXES
		lib64
		lib
		lib64/ffmpeg
		lib/ffmpeg
)

get_filename_component(FFMPEG_PARENT_DIR ${AVCODEC_INCLUDE_DIR} DIRECTORY)

SET(FFMPEG_INCLUDE_DIRS
	${AVUTIL_INCLUDE_DIR}
	${AVCODEC_INCLUDE_DIR}
	${AVFORMAT_INCLUDE_DIR}
	${FFMPEG_PARENT_DIR}
)

SET(FFMPEG_LIBRARIES)

IF(AVUTIL_LIBRARY)
	SET(FFMPEG_LIBRARIES
		${FFMPEG_LIBRARIES}
		${AVUTIL_LIBRARY}
	)
ENDIF(AVUTIL_LIBRARY)

IF(AVCODEC_LIBRARY)
	SET(FFMPEG_LIBRARIES
		${FFMPEG_LIBRARIES}
		${AVCODEC_LIBRARY}
	)
ENDIF(AVCODEC_LIBRARY)

IF(AVFORMAT_LIBRARY)
	SET(FFMPEG_LIBRARIES
		${FFMPEG_LIBRARIES}
		${AVFORMAT_LIBRARY}
	)
ENDIF(AVFORMAT_LIBRARY)


INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(FFMPEG REQUIRED_VARS AVUTIL_LIBRARY AVCODEC_LIBRARY AVFORMAT_LIBRARY AVUTIL_INCLUDE_DIR AVCODEC_INCLUDE_DIR AVFORMAT_INCLUDE_DIR)
