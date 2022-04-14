import QtQuick 2.6
import Sailfish.Silica 1.0

Page {
    id: about
    allowedOrientations: Orientation.Portrait

    SilicaListView {
        anchors.fill: parent

        Image {
            id: icon
            anchors.horizontalCenter: parent.horizontalCenter
            y: 500
            source: "/usr/share/icons/hicolor/172x172/apps/harbour-elzzup.png"
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            y: 750
            color: Theme.highlightColor
            text: "Elzzup 1.0.0"
        }

        Label {
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: Theme.horizontalPageMargin
                rightMargin: Theme.horizontalPageMargin
            }
            height: implicitHeight + Theme.paddingMedium
            color: Theme.highlightColor
            linkColor: Theme.primaryColor
            font.pixelSize: Theme.fontSizeSmall
            wrapMode: Text.WordWrap
            y: 850
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Picture puzzle game. This is an open source software which is distributed under the terms of the GNU GPLv3 License.")
        }

        Button {
            id: github
            anchors.horizontalCenter: parent.horizontalCenter
            y: 1250
            text: qsTr("Source code")
            onClicked: Qt.openUrlExternally("https://github.com/arustg/harbour-elzzup");
        }
    }
}
