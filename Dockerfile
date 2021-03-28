# This script constitutes the reproducible build environment for EVEmu.
# Always build EVEmu binaries using docker in a reproducible fashion for issue reporting.
# Author: jdhirst
FROM quay.io/fedora/fedora:33-x86_64 as base
RUN dnf groupinstall -y "Development Tools" && dnf install -y cmake git zlib-devel mariadb-devel boost-devel tinyxml-devel utf8cpp-devel podman buildah mariadb

FROM base as app-build
ADD CMakeLists.txt /src/
ADD config.h.in /src/
ADD /cmake/ /src/cmake
ADD /dep/ /src/dep
ADD /src/ /src/src
Add /utils/ /src/utils
RUN ls -al /src
RUN mkdir -p /src/build /app /app/logs /app/server_cache /app/image_cache
WORKDIR /src/build
RUN cmake -DCMAKE_INSTALL_PREFIX=/app -DCMAKE_BUILD_TYPE=Debug ..
RUN make -j$(nproc)
RUN make install

FROM base as app
LABEL description="EVEmu Server"
COPY --from=app-build /src/utils/ /src/utils
ADD /sql/ /src/sql
COPY --from=app-build /app/ /app
CMD /src/utils/container-scripts/start.sh
