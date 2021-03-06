#ifdef QT_QML_DEBUG
#include <QtQuick>
#include "puzzleboarditem.h"
#include "helpers/appsettings.h"
#include "helpers/appeventhandler.h"
#include "puzzle/puzzlegame.h"
#include <sailfishapp.h>
#endif
int main(int argc, char *argv[])
{
    return SailfishApp::main(argc, argv);
}


//#include <QSettings>
//#include <QLibraryInfo>
//#include <QElapsedTimer>
//#include <QGuiApplication>
//#include <QQuickView>
//#include <QScreen>
//#include <QQmlContext>
//#include <QQmlEngine>
//#include <QDebug>
//#include <QScopedPointer>
//#include <qqml.h>
//#if defined(FORCE_PLATFORM_FILE_DIALOG)
//#include <QApplication>
//#endif
//#if defined(USE_MDECLARATIVECACHE5)
//#include <mdeclarativecache5/MDeclarativeCache>
//#endif

//#include "puzzleboarditem.h"
//#include "helpers/appsettings.h"
//#include "helpers/appeventhandler.h"
//#include "puzzle/puzzlegame.h"

//#ifndef TEXT_SCALING_FACTOR
//#define TEXT_SCALING_FACTOR 1
//#endif
//#ifndef UI_SCALING_FACTOR
//#define UI_SCALING_FACTOR 1
//#endif
//#ifndef ENABLE_MOBILE_TWEAKS
//#define ENABLE_MOBILE_TWEAKS false
//#endif

////extern void loadTranslations();

//Q_DECL_EXPORT int main(int argc, char *argv[])
//{
//    QElapsedTimer *timer = new QElapsedTimer();
//    timer->start();

//    // Some settings

//    QCoreApplication::setApplicationName("Elzzup");
//    QCoreApplication::setApplicationVersion(QString(APP_VERSION));

//    // Initializing app and view

//#if defined(FORCE_PLATFORM_FILE_DIALOG)
//    QScopedPointer<QGuiApplication> app(new QApplication(argc, argv));
//#elif defined(USE_MDECLARATIVECACHE5)
//    QScopedPointer<QGuiApplication> app(MDeclarativeCache::qApplication(argc, argv));
//#else
//    QScopedPointer<QGuiApplication> app(new QGuiApplication(argc, argv));
//#endif

//#if defined(USE_MDECLARATIVECACHE5)
//    QQuickView *view = MDeclarativeCache::qQuickView();
//#else
//    QQuickView *view = new QQuickView();
//#endif

//    // Some wireup

//    AppEventHandler *appEventHandler = new AppEventHandler(view);
//    QObject::connect(view->engine(), SIGNAL(quit()), app.data(), SLOT(quit()));
//    qsrand((uint)QTime::currentTime().msec());
//    qmlRegisterType<PuzzleBoardItem>("Elzzup.puzzle", 1, 0, "PuzzleBoard");
//    qmlRegisterUncreatableType<PuzzleGame>("Elzzup.puzzle", 1, 0, "PuzzleGame", "This type should not be used from QML.");
//    qmlRegisterType<AppSettings>("Elzzup.puzzle", 1, 0, "AppSettings");

////    loadTranslations();

//    // Checking for rotation and touchscreen support

//    bool allowRotation = true, allowScrollbars = true;

//#if defined(DISABLE_ROTATION)
//    allowRotation = false;
//#endif

//#if defined(DISABLE_SCROLLBARS)
//    allowScrollbars = false;
//#endif

//    qDebug() << "Elzzup" << (allowRotation ? "enabled" : "disabled") << "rotation support";
//    qDebug() << "Scroll bars will" << (allowScrollbars ? "appear" : "not appear");

//    // Checking for QML gallery plugin support

//    bool allowGalleryModel = true;

//#if defined(DISABLE_QMLGALLERY)
//    allowGalleryModel = false;
//#endif

//    // Checking the size

//    QSize initialSize = view->screen()->size();
//    qDebug() << "initial size is" << initialSize;

//    // Check scaling factors

//    double uiScalingFactor = UI_SCALING_FACTOR;
//    double textScalingFactor = TEXT_SCALING_FACTOR;
//    bool enableMobileTweaks = ENABLE_MOBILE_TWEAKS;

//    // Setting up the view

//    view->setResizeMode(QQuickView::SizeRootObjectToView);
//    view->setTitle(QObject::tr("Puzzle Master"));

//    view->rootContext()->setContextProperty("initialSize", initialSize);
//    view->rootContext()->setContextProperty("allowRotation", allowRotation);
//    view->rootContext()->setContextProperty("allowScrollbars", allowScrollbars);
//    view->rootContext()->setContextProperty("allowGalleryModel", allowGalleryModel);
//    view->rootContext()->setContextProperty("appVersion", QString(APP_VERSION));
//    view->rootContext()->setContextProperty("appEventHandler", appEventHandler);
//    view->rootContext()->setContextProperty("uiScalingFactor", uiScalingFactor);
//    view->rootContext()->setContextProperty("textScalingFactor", textScalingFactor);
//    view->rootContext()->setContextProperty("enableMobileTweaks", enableMobileTweaks);

//    qDebug() << Q_FUNC_INFO << "initialization took" << timer->elapsed() << "ms";
//    timer->restart();
//    view->reportContentOrientationChange(Qt::LandscapeOrientation);

////#if defined(ROTATE_IN_QML)
////    view->setSource(QUrl("/usr/share/harbour-elzzup/qml/default/RotatedAppWindow.qml"));
////#else
//    view->setSource(QUrl("/usr/share/harbour-elzzup/qml/FirstPage_old.qml"));
////#endif
//    // NOTE: we no longer need to call show() here, the QML will take care of calling it
//    //view->showFullScreen();

//    qDebug() << Q_FUNC_INFO << "setting the qml source took" << timer->elapsed() << "ms";
//    delete timer;

//    // Launching the app

//    return app->exec();
//}
