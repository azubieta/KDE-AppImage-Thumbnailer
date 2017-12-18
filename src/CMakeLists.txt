find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui)
find_package(KF5 REQUIRED COMPONENTS KIO)

add_library(AppImageThumbs MODULE
        AppImageThumbnailCreator.cpp
        AppImageThumbnailCreator.h)

target_link_libraries(AppImageThumbs PRIVATE
        Qt5::Core
        Qt5::Gui
        KF5::KIOWidgets)

install(TARGETS AppImageThumbs DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES AppImageThumbs.desktop DESTINATION ${SERVICES_INSTALL_DIR})



enable_testing()

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Test)

cmake_policy(SET CMP0063 NEW)
add_executable(TestAppImageThumbnailCreator

        AppImageThumbnailCreator.cpp
        AppImageThumbnailCreator.h
        TestAppImageThumbnailCreator.cpp
        TestAppImageThumbnailCreator.h)

target_link_libraries(TestAppImageThumbnailCreator PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Test
        KF5::KIOWidgets)


add_test(TestAppImageThumbnailCreator TestAppImageThumbnailCreator)