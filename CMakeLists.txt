cmake_minimum_required(VERSION 3.5)

project(DavidPharmacyEleven VERSION 0.1 LANGUAGES CXX)

# Auto UIC, MOC, and RCC (Qt macros)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt libraries
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# List all your source and header files
set(PROJECT_SOURCES
    main.cpp

    #DTOs
    DTOs/doctordto.h

    # Repositories - Database Communications
    Repositories/PostgresQSqlRepositories/doctorrepository.cpp
    Repositories/PostgresQSqlRepositories/doctorrepository.h

    # Services - Business Logic
    Services/doctorservice.cpp
    Services/doctorservice.h

    # Utilities
    Utilities/sortingutils.h

    # Windows
    UI/MainWindow/mainwindow.cpp
    UI/MainWindow/mainwindow.h
    UI/MainWindow/mainwindow.ui

    UI/ManageDoctorsWindow/managedoctorswindow.cpp
    UI/ManageDoctorsWindow/managedoctorswindow.h
    UI/ManageDoctorsWindow/managedoctorswindow.ui

    # Custom Dialogs
    UI/CustomDialogs/DoctorDialogs/doctoreditdialog.h
    UI/CustomDialogs/DoctorDialogs/doctoreditdialog.cpp
)

# Create executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DavidPharmacyEleven
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(DavidPharmacyEleven SHARED ${PROJECT_SOURCES})
    else()
        add_executable(DavidPharmacyEleven ${PROJECT_SOURCES}
            Repositories/IRepositories/idoctorrepository.h)
    endif()
endif()

# Link Qt libraries
target_link_libraries(DavidPharmacyEleven PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Include directories (so all headers are found properly)
target_include_directories(DavidPharmacyEleven PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/DTOs
    ${CMAKE_CURRENT_SOURCE_DIR}/Repositories
    ${CMAKE_CURRENT_SOURCE_DIR}/Services
    ${CMAKE_CURRENT_SOURCE_DIR}/Utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/UI/ManageDoctorsWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/UI/MainWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/UI/CustomDialogs/DoctorDialogs
)

# macOS bundle identifier (for Mac/iOS if needed)
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DavidPharmacyEleven)
endif()

set_target_properties(DavidPharmacyEleven PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation
include(GNUInstallDirs)
install(TARGETS DavidPharmacyEleven
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt 6 finalization
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DavidPharmacyEleven)
endif()
