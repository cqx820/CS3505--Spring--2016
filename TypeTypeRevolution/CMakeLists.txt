cmake_minimum_required(VERSION 3.5)
project(TypeTypeRevolution)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BUILD_DIR "${PROJECT_SOURCE_DIR}/buildGW")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(QT_PATH "/usr/local/Cellar/qt5")
set(BOX2D_PATH "/usr/local/Cellar/box2d")


set(CMAKE_PREFIX_PATH ${QT_PATH})
set(CMAKE_PREFIX_PATH ${BOX2D_PATH})

#Libraries to link to. The :: is for convenience
set(QT_LIBRARIES
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Test)
#Libraries required. Probably the same as above minus the '::'. find_package() will be called on these
set(QT_LIBRARIES_REQUIRED
        Qt5Core
        Qt5Widgets
        Qt5Gui
        Qt5Test)

#find packages
foreach(QT_LIBRARIES_REQUIRED ${QT_LIBRARIES_REQUIRED})
    find_package( ${QT_LIBRARIES_REQUIRED} REQUIRED )
endforeach()

#sfml
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

#Box2d
find_package(Box2D)

## THIS IS THE IMPORTANT PART ##
add_custom_target(qtMakefile COMMAND make -C ${BUILD_DIR})
##        (that was it)       ##

include_directories(${BUILD_DIR} ${INCLUDE_DIR} ${TOOL_INCLUDE_DIR})

set(SOURCE_FILES
        ${BUILD_DIR}/moc_chooselessondialog.cpp
        ${BUILD_DIR}/moc_keyboardhandler.cpp
        ${BUILD_DIR}/moc_serverconnectdialog.cpp
        ${BUILD_DIR}/moc_typetypecontroller.cpp
        ${BUILD_DIR}/moc_typetypegui.cpp
        ${BUILD_DIR}/moc_typetypemenu.cpp
        ${BUILD_DIR}/moc_wordbox.cpp


        ${INCLUDE_DIR}/buoyancy.h
        ${INCLUDE_DIR}/buoyancylogic.h
        ${INCLUDE_DIR}/callbackfunctor.h
        ${INCLUDE_DIR}/chooselessondialog.h
        ${INCLUDE_DIR}/crate.h
        ${INCLUDE_DIR}/entity.h
        ${INCLUDE_DIR}/fallingcanvas.h
        ${INCLUDE_DIR}/keyboardhandler.h
        ${INCLUDE_DIR}/mycontactlistener.h
        ${INCLUDE_DIR}/networkcontroller.h
        ${INCLUDE_DIR}/qsfmlcanvas.h
        ${INCLUDE_DIR}/richtext.h
        ${INCLUDE_DIR}/serverconnectdialog.h
        ${INCLUDE_DIR}/timecanvas.h
        ${INCLUDE_DIR}/typetypecallbackserver.h
        ${INCLUDE_DIR}/typetypecontroller.h
        ${INCLUDE_DIR}/typetypegui.h
        ${INCLUDE_DIR}/typetypemenu.h
        ${INCLUDE_DIR}/wordbox.h


        ${SRC_DIR}/buoyancy.cpp
        ${SRC_DIR}/buoyancylogic.cpp
        ${SRC_DIR}/chooselessondialog.cpp
        ${SRC_DIR}/crate.cpp
        ${SRC_DIR}/entity.cpp
        ${SRC_DIR}/fallingcanvas.cpp
        ${SRC_DIR}/keyboardhandler.cpp
        ${SRC_DIR}/mycontactlistener.cpp
        ${SRC_DIR}/networkcontroller.cpp
        ${SRC_DIR}/qsfmlcanvas.cpp
        ${SRC_DIR}/richtext.cpp
        ${SRC_DIR}/serverconnectdialog.cpp
        ${SRC_DIR}/timecanvas.cpp
        ${SRC_DIR}/typetypecallbackserver.cpp
        ${SRC_DIR}/typetypecontroller.cpp
        ${SRC_DIR}/typetypegui.cpp
        ${SRC_DIR}/typetypemain.cpp
        ${SRC_DIR}/typetypemenu.cpp
        ${SRC_DIR}/wordbox.cpp
        )

add_executable(TypeTypeRevolution ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
if (SFML_FOUND)
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
