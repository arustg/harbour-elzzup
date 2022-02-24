import QtQuick 2.6
import Sailfish.Silica 1.0
import QtQuick.Dialogs 1.0

FileDialog {
    property variant appWindow: null
    property variant imageChooser: null
    property variant gameBoard: null

    id: filePicker
    title: qsTr("Welcome! Choose an image.")
    nameFilters: [ "Image files (*.jpg *.jpeg *.png *.bmp)", "All files (*)" ]
    onAccepted: {
        appEventHandler.activateAppWindow();

        if (appWindow.filePickerOnStart) {
            var url = imageChooser.sanitizePath(filePicker.fileUrl.toString());
            imageChooser.selectedImagePath = url;
            gameBoard.open();
            gameBoard.play();
        }
    }
    onRejected: {
        if (appWindow.filePickerOnStart) {
            console.log("User didn't choose an image, quitting.");
            Qt.quit();
        }
    }
}
