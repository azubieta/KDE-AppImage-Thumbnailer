cmake_minimum_required(VERSION 3.2)
project(AppImageThumbs)
set(PROJECT_VERSION 1.0) 

set(CMAKE_CXX_STANDARD 11)

set(QT_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(FeatureSummary)
include(WriteBasicConfigVersionFile)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

include(third-party/libappimage.cmake)
include(pack/cpack_deb.cmake)

add_subdirectory(src)
add_subdirectory(tests)
