import QtQuick 2.6
import Sailfish.Silica 1.0
import "./components"
import "./components/style"

Panel {
    function startGame() {
        imageChooser.shouldStartGame = true
        imageChooser.close()
    }

    function sanitizePath(path) {
        path = decodeURI(path);

        // Take care of some weird cases
        if (/^file\:\/\/\/[A-Za-z]\:/.test(path)) {
            // We're on Windows and the URI looks like file:///C:/whatever
            // but, the C++ parts don't understand file:///, so remove it
            path = path.substring("file:///".length);
        }
        else if (path.indexOf("file://") === 0) {
            // We're possibly on a UNIX-like system and the URI looks like file:///home/user/whatever
            // so we still need one / at the beginning of the path
            path = path.substring("file://".length);
        }
        return path;
    }

    property string selectedImagePath: ""
    property int columnNumber: 3
    property variant fileSelectorDialog: null
    property bool canAddCustomImage: (typeof(fileSelectorDialog) !== "undefined" && fileSelectorDialog !== null) || appEventHandler.showPlatformFileDialog()

    signal accepted

    id: imageChooser
    color: "#a909a7"
    radius: 15

    onCanAddCustomImageChanged: {
        var addImageItem = null;

        for (var i = 0; i < imagesModel.count; i++) {
            var item = imagesModel.get(i);
            if (item.specialThing === "add-image" && item.isBuiltIn === true) {
                console.log("aaaa");
                addImageItem = item;
                break;
            }
        }

        if (canAddCustomImage && addImageItem === null) {
            imagesModel.insert(0, { path: ":/pics/add-image.png", specialThing: "add-image", isBuiltIn: true });
        }
        else if (!canAddCustomImage && addImageItem !== null) {
            imagesModel.remove(0, 1);
        }
    }

    Keys.onEscapePressed: {
        if (areYouSureToQuitDialog.visible)
            areYouSureToQuitDialog.close();
        else
            areYouSureToQuitDialog.open();
    }

    Component.onCompleted: {
        var selectorComponent = null

        if (appEventHandler.showPlatformFileDialog()) {
            console.log("The platform's native file selector dialog will be used to add custom images");
        }
        else {
            if (allowGalleryModel) {
                console.log("ImageChooser: trying to load GallerySelectorDialog")
                selectorComponent = Qt.createComponent("GallerySelectorDialog.qml")
            }
            if (selectorComponent === null || selectorComponent.status === Component.Error || selectorComponent.status === Component.Null) {
                fileSelectorDialog = filePicker;
            }
            else {
                fileSelectorDialog = selectorComponent.createObject(imageChooser)
            }
        }
    }
    Rectangle {
        id: imageChooserTop
        height: 60 * uiScalingFactor
        color: "transparent"
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        TextEdit {
            text: qsTr("Welcome! Choose an image.")
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            horizontalAlignment: TextEdit.AlignHCenter
            verticalAlignment: TextEdit.AlignVCenter
            font.pixelSize: 30 * textScalingFactor
            color: "#ffffff"
            activeFocusOnPress: false
        }
        Button {
            id: appSwitcherButton
            visible: appEventHandler.showAppSwitcherButton()
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 6
            width: 100
            height: 100
            text: ""
            style: purpleButtonStyle
            onClicked: {
                appEventHandler.displayAppSwitcher()
            }
            Rectangle {
                color: "#FFFFFF"
                border.color: "#7DB72F"
                border.width: 1
                width: 25 * uiScalingFactor
                height: 25 * uiScalingFactor
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -5
                anchors.horizontalCenterOffset: -5
            }
            Rectangle {
                color: "#FFFFFF"
                border.color: "#7DB72F"
                border.width: 1
                width: 25 * uiScalingFactor
                height: 25 * uiScalingFactor
                anchors.centerIn: parent
                anchors.verticalCenterOffset: 5
                anchors.horizontalCenterOffset: 5
            }
        }
        MenuButton {
            id: menuButton
            anchors {
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 7 * uiScalingFactor
            }
            width: 100 * uiScalingFactor
            height: 60 * uiScalingFactor
            style: purpleButtonStyle
            onClicked: menuDialog.open()
        }
    }
    Item {
        anchors {
            top: imageChooserTop.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        clip: true

//        Image {
//            anchors.fill: parent
//            source: "qrc:/pics/background.jpg"
//            fillMode: Image.Tile
//        }
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            gradient: Gradient {
                GradientStop { color: "#99000000"; position: 0.0 }
                GradientStop { color: "#00000000"; position: 1.0 }
            }
            height: 70
        }

        GridView {
            id: imageSelectorGrid
            focus: true
            cacheBuffer: allowScrollbars ? initialSize.height * 3 : initialSize.height
            anchors {
                top: parent.top
                bottom: parent.bottom
                topMargin: 15
                bottomMargin: 5
                horizontalCenter: parent.horizontalCenter
                horizontalCenterOffset: - imageSelectorGridScrollBar.width / 2
            }
            cellWidth: (imageChooser.width - imageSelectorGridScrollBar.width) / imageChooser.columnNumber - 5
            cellHeight: imageSelectorGrid.cellWidth / imageChooser.width * imageChooser.height
            width: imageSelectorGrid.cellWidth * imageChooser.columnNumber
            currentIndex: -1
            flickableDirection: Flickable.VerticalFlick
            interactive: true
            model: ListModel {
                property int initialImageCount: 0

                id: imagesModel
                Component.onCompleted: {
                    // These are the built-in images
//                    imagesModel.append({ path: ":/pics/image1.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image4.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image16.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image18.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image10.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image3.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image6.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image5.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image11.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image17.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image12.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image13.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image7.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image8.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image9.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image14.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image15.jpg", isBuiltIn: true });
//                    imagesModel.append({ path: ":/pics/image2.jpg", isBuiltIn: true });

                    // Set initial count
                    imagesModel.initialImageCount = imagesModel.count;
                    // Load custom images
                    var paths = appSettings.loadCustomImages();
                    for (var i = 0; i < paths.length; i++) {
                        imagesModel.insert(canAddCustomImage ? 1 : 0, { path: paths[i] });
                    }
                }
            }
            delegate: Item {
                width: imageSelectorGrid.cellWidth
                height: imageSelectorGrid.cellHeight

                Rectangle {
                    color: "#ffffff"
                    anchors.fill: delegateImage
                    anchors.margins: -5
                    border.width: 3
                    border.color: "#33000000"
                    visible: typeof(model.specialThing) === "undefined"
                }

                Image {
                    id: delegateImage
                    asynchronous: false
                    fillMode: Image.PreserveAspectCrop
                    width: 100
                    height: 100
                    clip: true
                    anchors.centerIn: parent
                    source:  "/usr/share/harbour-elzzup/images/add.png"
                    sourceSize {
                        width: 100
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {

                        var selected = imagesModel.get(index);
                        if (selected.specialThing === "add-image") {
                            menuDialog.close()
                            if (appEventHandler.showPlatformFileDialog()) {
                                appEventHandler.displayPlatformFileDialog();
                            }
                            else if (typeof(fileSelectorDialog) !== 'undefined' && fileSelectorDialog !== null) {
                                fileSelectorDialog.open();
                            }
                        }
                        else {
                            imageSelectorGrid.currentIndex = index;
                            imageChooser.accepted();
                        }
                    }
                }
                Button {
                    style: redButtonStyle
                    text: "-"
                    width: 50 * uiScalingFactor
                    height: 50 * uiScalingFactor
                    font.pixelSize: 25 * textScalingFactor
                    anchors {
                        bottom: parent.bottom
                        right: parent.right
                    }
                    visible: !model.isBuiltIn
                    onClicked: {
                        var selected = imagesModel.get(index);
                        appSettings.removeCustomImage(decodeURI(selected.path));
                        imagesModel.remove(index);
                    }
                }
            }
            onCurrentIndexChanged: {
                var selected = imagesModel.get(imageSelectorGrid.currentIndex);
                imageChooser.selectedImagePath = selected.path;
            }
        }
        VerticalScrollBar {
            id: imageSelectorGridScrollBar
            visibleWhen: allowScrollbars
            enableScrolling: allowScrollbars
            flickable: imageSelectorGrid
            anchors.right: parent.right
            anchors.rightMargin: 7
        }
    }
    Dialog {
        id: youMustChooseDialog
        title: qsTr("Please choose")
        text: qsTr("You must choose an image before continuing.")
        acceptButtonText: qsTr("Ok")
    }
    Dialog {
        id: menuDialog
        title: qsTr("Puzzle Master")
        contentHeight: menuDialogColumn.height
        contentWidth: menuDialogColumn.width
        content: Column {
            id: menuDialogColumn
            spacing: 10 * uiScalingFactor

            Button {
                width: 500 * uiScalingFactor
                text: qsTr("About")
                onClicked: {
                    menuDialog.close()
                    aboutDialog.open()
                }
            }
            Button {
                width: 500 * uiScalingFactor
                text: qsTr("Quit")
                style: redButtonStyle
                onClicked: {
                    menuDialog.close()
                    areYouSureToQuitDialog.open()
                }
            }
        }
    }
    Connections {
        target: fileSelectorDialog ? fileSelectorDialog : null
        onAccepted: {
            var path = fileSelectorDialog.selectedImagePath || (fileSelectorDialog.fileUrl && fileSelectorDialog.fileUrl.toString()) || "";
            if (path) {
                path = sanitizePath(path);
                console.log("Trying to add custom image", path);
                if (appSettings.addCustomImage(path)) {
                    imagesModel.insert(canAddCustomImage ? 1 : 0, { path: path });
                }
            }
            else {
                console.log("No custom image specified.")
            }
        }
    }
    Connections {
        target: appEventHandler
        onPlatformFileDialogAccepted: {
            if (appSettings.addCustomImage(decodeURI(filePath)))
                imagesModel.insert(canAddCustomImage ? 1 : 0, { path: filePath })
        }
    }
}
