# This file is part of the KDAB Nautical UI demo.
#
# SPDX-FileCopyrightText: 2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
#
# SPDX-License-Identifier: MIT
#
# Contact info@kdab.com for more information about this software.
#

cmake_minimum_required(VERSION 3.9)
project(KDABBoatDemo)
find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Gui Quick Widgets Test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)

qt5_add_resources(RESOURCES imagesMaps.qrc imagesMaps2.qrc images.qrc data.qrc qml.qrc)

add_executable(KDABBoatDemo
  main.cpp
  windowdata.cpp
  musicmodel.cpp
  ${RESOURCES}
)

target_link_libraries(KDABBoatDemo Qt5::Core Qt5::Gui Qt5::Quick Qt5::Widgets)

add_executable(listmusic listmusic.cpp musicmodel.cpp data.qrc)

target_link_libraries(listmusic Qt5::Core Qt5::Test)

install(TARGETS KDABBoatDemo RUNTIME DESTINATION bin)
