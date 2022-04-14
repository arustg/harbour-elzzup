#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QByteArray>
#include <QStringList>

#include "../helpers/util.h"

// Setting property
#define SETTINGPROPERTY(type, name, settername, signalname, settingKey, defaultValue) \
    inline type name() const { return _backend.value(settingKey, defaultValue).value<type>(); } \
    inline void settername (const type &value) { _backend.setValue(settingKey, value); emit signalname (); }

class QSettings;

class AppSettings : public QObject
{
    Q_OBJECT
    GENPROPERTY_R(bool, _areSettingsDeleted, areSettingsDeleted)
    Q_PROPERTY(bool areSettingsDeleted READ areSettingsDeleted NOTIFY areSettingsDeletedChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(int snapDifficulty READ snapDifficulty WRITE setSnapDifficulty NOTIFY snapDifficultyChanged)
    Q_PROPERTY(bool advancedMode READ advancedMode WRITE setAdvancedMode NOTIFY advancedModeChanged)

    QSettings _backend;

public:
    explicit AppSettings(QObject *parent = 0);

    SETTINGPROPERTY(int, rows, setRows, rowsChanged, "rows", 3)
    SETTINGPROPERTY(int, columns, setColumns, columnsChanged, "columns", 3)
    SETTINGPROPERTY(int, snapDifficulty, setSnapDifficulty, snapDifficultyChanged, "snapDifficulty", 1)
    SETTINGPROPERTY(QByteArray, customImageListData, setCustomImageListData, customImageListDataChanged, "customImageListData", QByteArray())
    SETTINGPROPERTY(bool, advancedMode, setAdvancedMode, advancedModeChanged, "advancedMode", false)

    Q_INVOKABLE QStringList loadCustomImages();
    Q_INVOKABLE bool addCustomImage(const QString &url);
    Q_INVOKABLE bool removeCustomImage(const QString &url);

signals:
    void areSettingsDeletedChanged();
    void rowsChanged();
    void columnsChanged();
    void snapDifficultyChanged();
    void advancedModeChanged();
    void customImageListDataChanged();
    void customImageAlreadyAdded(const QString &url);

};

#endif // APPSETTINGS_H
