find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui)
find_package(KF5 REQUIRED COMPONENTS KIO)

add_library(appimagethumbnail MODULE
        AppImageThumbnailCreator.cpp
        AppImageThumbnailCreator.h)

target_link_libraries(appimagethumbnail PRIVATE
        Qt5::Core
        Qt5::Gui
        KF5::KIOWidgets)

message(${PLUGIN_INSTALL_DIR})
install(TARGETS appimagethumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES appimagethumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})



