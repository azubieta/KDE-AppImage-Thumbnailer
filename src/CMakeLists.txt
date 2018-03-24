find_package(KF5 REQUIRED COMPONENTS KIO)

add_library(appimagethumbnail MODULE
        AppImageThumbnailCreator.cpp
        AppImageThumbnailCreator.h)

target_link_libraries(appimagethumbnail
    PRIVATE KF5::KIOWidgets
    PRIVATE libappimage)

include(KDEInstallDirs)

install(TARGETS appimagethumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES appimagethumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})



