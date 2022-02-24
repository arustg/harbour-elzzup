import QtQuick 2.6
import Sailfish.Silica 1.0

ApplicationWindow {
    initialPage: Qt.resolvedUrl("GamePage.qml")
    cover: Qt.resolvedUrl("CoverPage.qml")
    allowedOrientations: Orientation.Portrait
}
