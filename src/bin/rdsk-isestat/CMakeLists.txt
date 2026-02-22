# ==============================================================================
# RDSK Monitoring Server CMake File
# ==============================================================================

# program objects --------------------------------------------------------------
SET(PROG_SRC
        RDSKStatServerOptions.cpp
        RDSKStatServer.cpp
        RDSKStatDatagram.cpp
        ServerWatcher.cpp
        )

# final build ------------------------------------------------------------------
ADD_EXECUTABLE(rdsk-isestat ${PROG_SRC})

TARGET_LINK_LIBRARIES(rdsk-isestat ${ALL_LIBS})

INSTALL(TARGETS
            rdsk-isestat
        DESTINATION
            bin
        )

