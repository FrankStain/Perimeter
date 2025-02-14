#!/bin/bash

set -e

mkdir -p build

echo "Triplet: ${CROSS_TRIPLE}"
if [[ $CROSS_TRIPLE == *shared ]]; then
  LIB_SUFFIX=.dll.a
else
  LIB_SUFFIX=.a
fi
if [[ $CROSS_TRIPLE == x86_64* ]]; then
  IS_64=1
fi

#rm -rf build/${CROSS_TRIPLE}

BASE_DIR="/usr/lib/mxe/usr/${CROSS_TRIPLE}"

${CROSS_TRIPLE}-cmake \
-B"build/${CROSS_TRIPLE}" \
-H. \
-G"Ninja" \
-DLIBRARY_SEARCH_PATHS=$BASE_DIR \
-DBoost_INCLUDE_DIR="/usr/local/include" \
-DOGG_INCLUDE_DIR="${BASE_DIR}/include" \
-DVORBIS_INCLUDE_DIR="${BASE_DIR}/include" \
-DSDL2_INCLUDE_DIR="${BASE_DIR}/include/SDL2" \
-DSDL2_IMAGE_INCLUDE_DIR="${BASE_DIR}/include/SDL2-image" \
-DSDL2_NET_INCLUDE_DIR="${BASE_DIR}/include/SDL2-net" \
-DOFF_AVUTIL_INCLUDE_DIR="${BASE_DIR}/include" \
-DOFF_AVCODEC_INCLUDE_DIR="${BASE_DIR}/include" \
-DOFF_AVFORMAT_INCLUDE_DIR="${BASE_DIR}/include" \
-DOGG_LIBRARY="${BASE_DIR}/lib/libogg${LIB_SUFFIX}" \
-DVORBIS_LIBRARY="${BASE_DIR}/lib/libvorbis${LIB_SUFFIX}" \
-DVORBISFILE_LIBRARY="${BASE_DIR}/lib/libvorbisfile${LIB_SUFFIX}" \
-DSDL2_LIBRARY="${BASE_DIR}/lib/libSDL2${LIB_SUFFIX}" \
-DSDL2_IMAGE_LIBRARY="${BASE_DIR}/lib/libSDL2_image${LIB_SUFFIX}" \
-DSDL2_NET_LIBRARY="${BASE_DIR}/lib/libSDL2_net${LIB_SUFFIX}" \
-DOFF_AVUTIL_LIBRARY="${BASE_DIR}/lib/libavutil${LIB_SUFFIX}" \
-DOFF_AVCODEC_LIBRARY="${BASE_DIR}/lib/libavcodec${LIB_SUFFIX}" \
-DOFF_AVFORMAT_LIBRARY="${BASE_DIR}/lib/libavformat${LIB_SUFFIX}" \
-DOPTION_LINKER_LLD=OFF \
$@

cd build/${CROSS_TRIPLE}

ninja -j$(nproc --all)

mkdir -p output

cp Source/perimeter.exe output
#cp /usr/lib/mxe/usr/${CROSS_TRIPLE}/bin/SDL2.dll output
cp -fv /usr/lib/mxe/usr/${CROSS_TRIPLE}/bin/libogg*.dll output
cp -fv /usr/lib/mxe/usr/${CROSS_TRIPLE}/bin/libvorbis*.dll output
cp -fv /usr/lib/mxe/usr/${CROSS_TRIPLE}/bin/libvorbisfile*.dll output
cp -fv /usr/lib/mxe/usr/${CROSS_TRIPLE}/bin/libstdc*.dll output
cp -fv /usr/lib/mxe/usr/${CROSS_TRIPLE}/bin/libgcc*.dll output
cp -fv /usr/lib/mxe/usr/${CROSS_TRIPLE}/bin/libwinpthread-*.dll output

exit 0
