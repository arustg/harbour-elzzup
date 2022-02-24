import QtQuick 2.6
import Sailfish.Silica 1.0
import QtDocGallery 5.0
import "./components"

Dialog
{
    property string selectedImagePath: ""

    onOpened: {
        console.log("Creating DocumentGalleryModel");
        if (!imageSelectorGrid.model) {
            imageSelectorGrid.model = modelComponent.createObject(fileSelectorDialog);
        }
    }

    id: fileSelectorDialog
    enableBackgroundClicking: false
    title: qsTr("Select a picture")
    acceptButtonText: imageSelectorGrid.currentIndex >= 0 ? qsTr("Select") : ""
    rejectButtonText: qsTr("Cancel")
    contentWidth: imageSelectorGrid.width
    contentHeight: imageSelectorGrid.height
    content: GridView {
        id: imageSelectorGrid
        cellWidth: imageSelectorGrid.width / 4 - 5
        cellHeight: imageSelectorGrid.cellWidth / fileSelectorDialog.width * fileSelectorDialog.height
        width: fileSelectorDialog.width * 4 / 5
        height: (fileSelectorDialog.height - 160) / uiScalingFactor
        clip: true
        focus: true
        cacheBuffer: imageSelectorGrid.height / 2
        currentIndex: -1
        highlightMoveDuration: 80

        delegate: Item {
            width: imageSelectorGrid.cellWidth
            height: imageSelectorGrid.cellHeight

            Image {
                id: imageItem
                asynchronous: true
                width: imageSelectorGrid.cellWidth - 10
                height: imageSelectorGrid.cellHeight - 10
                fillMode: Image.PreserveAspectCrop
                clip: true
                source: url
                sourceSize.width: imageSelectorGrid.cellWidth - 10
                anchors.centerIn: parent
            }
            TextEdit {
                activeFocusOnPress: false
                color: "#ffffff"
                text: "..."
                font.pixelSize: imageSelectorGrid.cellHeight / 3
                anchors.centerIn: imageItem
                visible: imageItem.status == Image.Loading
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    fileSelectorDialog.selectedImagePath = filePath;
                    imageSelectorGrid.currentIndex = index;
                }
            }
        }
        highlight: Rectangle {
            color: "#a909a7"
            radius: 2
        }

        TextEdit {
            id: modelLoadIndicator
            anchors.centerIn: parent
            font.pixelSize: 50
            color: "#ffffff"
            activeFocusOnPress: false
            text: "..."
        }

        Component {
            id: modelComponent

            DocumentGalleryModel {
                id: picsModel
                rootType: DocumentGallery.Image
                properties: [ 'url', 'filePath' ]
                sortProperties: [ '-dateTaken' ]
                autoUpdate: true
                onStatusChanged: {
                    if (status === DocumentGalleryModel.Idle || status === DocumentGalleryModel.Finished || status === DocumentGalleryModel.Canceled) {
                        modelLoadIndicator.visible = false;
                    }
                }
            }
        }
    }
}
