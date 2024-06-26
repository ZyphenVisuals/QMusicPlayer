import QtCore

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Layouts
import QtQuick.Dialogs

import com.teamcex.FileManager
import com.teamcex.ThemeManager

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("Settings - QMusicPlayer")
    Universal.theme: Universal.Dark
    id: root

    ColumnLayout{
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        id: settingsLayout

        Text {
            text: qsTr("Personalization")
            color: "white"
            font.pixelSize: 32
            font.bold: true
        }

        RowLayout{
            Text {
                text: qsTr("Accent color")
                color: "white"
                font.pixelSize: 16
            }
            ComboBox{
                Component.onCompleted: currentIndex = indexOfValue(ThemeManager.accentColor)

                model: ListModel{
                    ListElement{
                        name: "Cobalt (Default)"
                        value: Universal.Cobalt
                    }
                    ListElement{
                        name: "Emerald"
                        value: Universal.Emerald
                    }
                    ListElement{
                        name: "Violet"
                        value: Universal.Violet
                    }
                    ListElement{
                        name: "Crimson"
                        value: Universal.Crimson
                    }
                }

                textRole: "name"
                valueRole: "value"

                onActivated: {
                    ThemeManager.accentColor = model.get(currentIndex).value
                }
            }
        }

        Text {
            text: qsTr("Folder paths")
            color: "white"
            font.pixelSize: 32
            font.bold: true
        }

        Item {
          id:listviewrec
          implicitWidth: settingsLayout.width
          implicitHeight: settingsLayout.height * 0.5
          visible: true

          ListView{
            id:modlistview
            width: listviewrec.width
            height: listviewrec.height
            clip: true
            boundsBehavior: Flickable.DragOverBounds
            spacing:0
            model:FileManager.folders
            delegate: Item {
                width: listviewrec.width
                height: 50
                Text {
                    text: {
                        modelData.toString().replace("file:///", "")
                    }
                    color: "white"
                    font.pixelSize: 16
                    width: listviewrec.width * 0.95
                    elide: Text.ElideRight
                    anchors.centerIn: parent
                }
                MouseArea{
                    width: parent.width
                    height: parent.height
                    onClicked: {
                        dialog.namedOpen(modelData)
                    }
                }
            }
            orientation: Qt.Vertical
            anchors.fill: listviewrec
          }

          Rectangle {
            border.color:"#5c5c5c"
            border.width: 2
            color: 'transparent'
            anchors.fill: parent
          }
        }

        Button{
            text: "Add folder"
            onClicked: folderDialog.open()
        }
    }

    FolderDialog {
            id: folderDialog
            title: "Select an import folder"
            currentFolder: StandardPaths.standardLocations(StandardPaths.MusicLocation)[0]
            onAccepted: {
                FileManager.addFolder(selectedFolder)
            }
    }

    Dialog {
        id: dialog

        property string folderName

        function namedOpen(folderName) {
            this.folderName = folderName
            open()
        }

        anchors.centerIn: parent
        title: "Are you sure you want to delete this folder?"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: FileManager.removeFolder(folderName)
    }
}
