enable_testing()

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Test)
find_package(KF5 REQUIRED COMPONENTS KIO)

cmake_policy(SET CMP0063 NEW)
add_executable(TestAppImageThumbnailCreator

        ../src/AppImageThumbnailCreator.cpp
        ../src/AppImageThumbnailCreator.h
        TestAppImageThumbnailCreator.cpp
        TestAppImageThumbnailCreator.h)

target_link_libraries(TestAppImageThumbnailCreator PRIVATE
        Qt5::Test
        KF5::KIOWidgets
        libappimage)

target_compile_definitions(TestAppImageThumbnailCreator PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/")

add_test(TestAppImageThumbnailCreator TestAppImageThumbnailCreator)