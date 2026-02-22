# ==============================================================================
# RDSK Monitoring Server CMake File
# ==============================================================================

# program objects --------------------------------------------------------------
SET(PROG_SRC
        RDSKRegisterOptions.cpp
        RDSKRegister.cpp
        DatagramSender.cpp
        RDSKStatDatagram.cpp
        )

# final build ------------------------------------------------------------------
ADD_EXECUTABLE(rdsk-register ${PROG_SRC})

TARGET_LINK_LIBRARIES(rdsk-register ${ALL_LIBS})

INSTALL(TARGETS
            rdsk-register
        DESTINATION
            bin
        )

