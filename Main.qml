import QtCore

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Dialogs

ApplicationWindow {
    width: 1280
    height: 720
    minimumHeight: 720
    minimumWidth: 1280
    visible: true
    title: qsTr("QMusicPlayer")
    Universal.theme: Universal.Dark
    id: root

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action {
                text: qsTr("Open song")
            }
            Action {
                text: qsTr("Exit")
                onTriggered: {
                    Qt.quit()
                }
            }
        }

        Menu {
            title: qsTr("Options")
            Action {
                text: qsTr("Import folders")
                onTriggered: {
                    var component = Qt.createComponent("settings.qml")
                    var window    = component.createObject(root)
                    window.show()
                }
            }
            Action {
                text: qsTr("Audio settings")
            }
        }
    }

    Text {
        text: "Hello world!"
        color: "#ffffff"
    }
}
