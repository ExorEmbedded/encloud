modeqcc {
    !splitdeps {
        exor {
            PRODUCT_SRC = $$SRCBASEDIR/../jmconnect
        } else {  # endian, panda
            PRODUCT_SRC = $$SRCBASEDIR/../connectapp
        }
        include($${PRODUCT_SRC}/defines.pri)
    } else {
        # special case for Yocto - currently we use QCC mode also on devices
        PRODUCT_DIR="Encloud"
    }
} else:modeece {
    PRODUCT_DIR="Encloud"
} else:modesece {
    PRODUCT_DIR="SECE"
} else:modevpn {
    PRODUCT_DIR="OVPN"
} else {
    error("a mode must be defined (CONFIG += modeqcc|modeece|modesece)!")
}
