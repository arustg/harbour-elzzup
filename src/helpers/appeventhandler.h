#ifndef APPEVENTHANDLER_H
#define APPEVENTHANDLER_H

#include <QObject>
#include <QStringList>

class QTimer;

// This class handles platform differences and native events.
// It contains all the hacks necessary to make the app work on multiple platforms.

class AppEventHandler : public QObject
{
    Q_OBJECT

public:
    explicit AppEventHandler(QObject *parent = 0);
    ~AppEventHandler();
    static bool nativeEventFilter(void *message);
    bool eventFilter(QObject *obj, QEvent *event);
    Q_INVOKABLE bool showAppSwitcherButton();
    Q_INVOKABLE void displayAppSwitcher();
    Q_INVOKABLE bool showPlatformFileDialog();
    Q_INVOKABLE void displayPlatformFileDialog();
    Q_INVOKABLE void activateAppWindow();
    
signals:
    void windowActivated();
    void windowDeactivated();
    void platformFileDialogAccepted(QString filePath);

private slots:
    void filesSelected(QStringList files);
    
public slots:
    void adjustForPlaying();
    void adjustForUi();
    
};

#endif // APPEVENTHANDLER_H
