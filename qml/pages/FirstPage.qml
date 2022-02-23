import QtQuick 2.0
import Sailfish.Silica 1.0
import Sailfish.Pickers 1.0

Page {

    property bool diffLevel

SilicaFlickable {
    anchors.fill: parent

    PullDownMenu {
        MenuItem {
                text: qsTr("About")
                onClicked: pageStack.animatorPush(Qt.resolvedUrl("About.qml"))}
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

    Button {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("Puzzle Picture")
        onClicked: {pageStack.push(imagePickerPage)
        }
    }
    Row {
        spacing: Theme.itemSizeSmall
        anchors.horizontalCenter: parent.horizontalCenter
        y: 600
        Switch {
            automaticCheck: false
            checked: !diffLevel
            onClicked: diffLevel = false
           Label {
               anchors.horizontalCenter: parent.horizontalCenter
                text: "Easy"
                y: -30
            }
        }
    }
    Row {
        spacing: Theme.itemSizeSmall
        anchors.horizontalCenter: parent.horizontalCenter
        y: 1220
        Switch {
            automaticCheck: false
            checked: diffLevel
            onClicked: diffLevel = true
           Label {
               anchors.horizontalCenter: parent.horizontalCenter
                text: "Hard"
                y: -30
            }
        }
    }
  }
}

