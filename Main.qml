import QtCore

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Dialogs

import com.teamcex.FileManager

ApplicationWindow {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World")
    Universal.theme: Universal.Dark

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action {
                text: qsTr("Open folder")
                onTriggered: {
                    folderDialog.open()
                }
            }
        }
    }

    Text {
        text: "Hello world!"
        color: "#ffffff"
    }

    FolderDialog {
            id: folderDialog
            currentFolder: StandardPaths.standardLocations(StandardPaths.MusicLocation)[0]
            onAccepted: FileManager.scanFolderContents(selectedFolder)
    }
}
