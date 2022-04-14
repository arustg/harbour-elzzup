import QtQuick 2.6
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Page {
    id: gamePage
    allowedOrientations: Orientation.Portrait

    property string backImageFilePath : ""

    property bool diffLevel

SilicaFlickable {
    anchors.fill: parent

    PullDownMenu {
        MenuItem {
                text: qsTr("About")
                onClicked: pageStack.animatorPush(Qt.resolvedUrl("AboutPage.qml"))}
    }



    Component {
        id: imagePickerPage
        ImagePickerPage {
            onSelectedContentPropertiesChanged: {
                backImageFilePath = selectedContentProperties.filePath
                idBackImageLoaded.source = encodeURI(backImageFilePath)
                getScaleOnImageLoad()
            }
        }
    }

    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        source: "/usr/share/harbour-elzzup/images/add.png"
        MouseArea {
             anchors.fill: parent
             onClicked: {pageStack.push(imagePickerPage)
             }
        }
    }

    Row {
        spacing: Theme.itemSizeMedium
        anchors.horizontalCenter: parent.horizontalCenter
        y: 1500
        Switch {
            automaticCheck: false
            checked: !diffLevel
            onClicked: diffLevel = false
           Label {
               anchors.horizontalCenter: parent.horizontalCenter
                text: "3 x 3"
                font.pixelSize: Theme.fontSizeLarge
                y: -70
            }
        }
        Switch {
            automaticCheck: false
            checked: diffLevel
            onClicked: diffLevel = true
           Label {
               anchors.horizontalCenter: parent.horizontalCenter
                text: "6 x 6"
                font.pixelSize: Theme.fontSizeLarge
                y: -70
            }
        }
    }

  }
}

