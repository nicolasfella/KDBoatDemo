/*
  This file is part of the KDAB Nautical UI demo.

  SPDX-FileCopyrightText: 2013-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: MIT

  Contact info@kdab.com for more information about this software.
*/

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QGuiApplication>
#include <QCursor>
#include <QCommandLineParser>
#include <QApplication>
#include <QDesktopWidget>

#include "windowdata.h"
#include "musicmodel.h"

/**
 * KDAB Boat demo
 */

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("KDAB Nautical UI - concept of the next generation UI for sailing boats");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption quitOption(QStringList() << "q"
                                                << "quit",
                                  "Show quit button.");
    parser.addOption(quitOption);

    QCommandLineOption cursorDisableOption("no-cursor",
                                           "Make sure no pointer is hidden.");
    parser.addOption(cursorDisableOption);

    QCommandLineOption fullscreenOption("fullscreen",
                                        "Open the demo in fullscreen");
    parser.addOption(fullscreenOption);

    QCommandLineOption landscapeOption("landscape",
                                       "Open the demo in landscape mode (default: autodetect)");
    parser.addOption(landscapeOption);

    QCommandLineOption portraitOption("portrait",
                                      "Open the demo in portrait mode (default: autodetect)");
    parser.addOption(portraitOption);

    QCommandLineOption lowresOption("lowres",
                                    "Open the demo in low resolution");
    parser.addOption(lowresOption);

    parser.process(app);

    if (parser.isSet(cursorDisableOption))
        app.setOverrideCursor(QCursor(Qt::BlankCursor));

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    if (!primaryScreen)
        qFatal("Cannot determine the primary screen");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("_canCloseDemoFromUI", QVariant::fromValue(parser.isSet(quitOption)));
    engine.rootContext()->setContextProperty("_showFullscreen", QVariant::fromValue(parser.isSet(fullscreenOption)));

    if (parser.isSet(portraitOption) && parser.isSet(landscapeOption))
        qFatal("Cannot set both landscape and portrait at the same time");

    const bool portrait = [&]() {
        if (parser.isSet(portraitOption)) {
            return true;
        } else if (parser.isSet(landscapeOption)) {
            return false;
        } else {
            QSize screenSize = QApplication::desktop()->size();
            return (screenSize.height() > screenSize.width());
        }
    }();
    engine.rootContext()->setContextProperty("_portrait", QVariant::fromValue(portrait));

    qmlRegisterType<MusicModel>("com.kdab.boat", 1, 0, "MusicModel");
    qmlRegisterSingletonType<WindowData>("com.kdab.boat", 1, 0, "WindowData", [portrait](QQmlEngine *, QJSEngine *) -> QObject * {
        return new WindowData(portrait);
    });

    const QUrl url(QStringLiteral("qrc:/resources/Main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
