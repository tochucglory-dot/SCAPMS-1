
cmake_minimum_required(VERSION 3.16)

project(SCAPMS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    model/PatientRecord.h
    model/PatientRecord.cpp
    model/Appointable.h
    model/GeneralPatient.h
    model/GeneralPatient.cpp
    model/EmergencyPatient.h
    model/EmergencyPatient.cpp
    model/FollowUpPatient.h
    model/FollowUpPatient.cpp
    model/Appointment.h
    model/Appointment.cpp

    controller/ClinicDatabase.h
    controller/ClinicDatabase.cpp
    controller/SearchEngine.h
    controller/SearchEngine.cpp
    controller/SortEngine.h
    controller/SortEngine.cpp
    controller/ClinicManager.h
    controller/ClinicManager.cpp

    utils/FileHandler.h
    utils/FileHandler.cpp
    utils/IDGenerator.h

    gui/PatientPanel.h
    gui/PatientPanel.cpp
    gui/AppointmentPanel.h
    gui/AppointmentPanel.cpp
    gui/QueuePanel.h
    gui/QueuePanel.cpp
    gui/SearchSortPanel.h
    gui/SearchSortPanel.cpp
    gui/ReportsPanel.h
    gui/ReportsPanel.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SCAPMS
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(SCAPMS
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(SCAPMS PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)

install(TARGETS SCAPMS
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SCAPMS)
endif()
