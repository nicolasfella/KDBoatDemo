# Boat Demo Exercise

This application demonstrates a UI concept for a sailing boat. It is currently based on Qt5 and we are going to port it to Qt6.

## 0. Build the project against Qt5

Open the project in an IDE/Editor of your choice and built it.

The project consists of two executables. A small `listmusic` executable that parses a file with music information and prints it, and the `KDABBoatDemo` GUI application.

Run the project and play around with it.

## 1. Build System

Adjust the CMake code to make it configure against Qt6 while keeping compatibility with Qt5.

Do not attempt to build the project yet.

## 2. C++ Code

Make the C++ code build against Qt6 while keeping compatibility with Qt5.

## 3. QML Code

Adjust the QML code so that the app runs with Qt6. Make sure the music playlist works as expected.

## 4. Modernization

Modernize the QML code based on what you just learned. You can use `qmllint` as a guide.
