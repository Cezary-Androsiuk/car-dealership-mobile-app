cmake_minimum_required(VERSION 3.16)

project(CarDealershipMobileApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Concurrent)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appCarDealershipMobileApp
    source/main.cpp
)

qt_add_qml_module(appCarDealershipMobileApp
    URI CarDealershipMobileApp
    VERSION 1.0
    QML_FILES qml/Main.qml
    QML_FILES
    SOURCES source/Backend.h source/Backend.cpp
    QML_FILES
    QML_FILES qml/DataErrorView.qml
    QML_FILES qml/DataView.qml
    SOURCES source/DataObject.h source/DataObject.cpp
    SOURCES source/Data.h source/Data.cpp
    SOURCES source/NetworkDownlaoder.h source/NetworkDownlaoder.cpp
    SOURCES source/DataParser.h source/DataParser.cpp
    SOURCES source/utils.h
    QML_FILES qml/Toast.qml
    SOURCES
    SOURCES source/DataDetails.h source/DataDetails.cpp
    SOURCES source/DataEngine.h source/DataEngine.cpp
    SOURCES source/DataBuilder.h source/DataBuilder.cpp
    QML_FILES qml/RefreshListView.qml
    QML_FILES qml/Loading.qml
    QML_FILES qml/Settings.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCarDealershipMobileApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCarDealershipMobileApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCarDealershipMobileApp
    PRIVATE Qt6::Quick Qt6::Concurrent
)
target_link_libraries(appCarDealershipMobileApp PRIVATE Qt6::Core)
target_link_libraries(appCarDealershipMobileApp PRIVATE Qt6::Core)
target_link_libraries(appCarDealershipMobileApp PRIVATE Qt6::Core)
target_link_libraries(appCarDealershipMobileApp PRIVATE Qt6::Core)
target_link_libraries(appCarDealershipMobileApp PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appCarDealershipMobileApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
