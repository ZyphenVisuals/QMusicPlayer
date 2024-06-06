import QtCore

import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Effects

import com.teamcex.FileManager
import com.teamcex.Player
import com.teamcex.SongModel
import com.teamcex.Playlist

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
                onTriggered: {
                    fileDialog.open()
                }
            }
            Action {
                text: qsTr("Exit")
                onTriggered: {
                    Qt.quit()
                }
            }
        }

        Menu {
            title: qsTr("Playback")
            Action {
                text: qsTr("Play")
                onTriggered: {
                    Player.play()
                }
            }
            Action {
                text: qsTr("Pause")
                onTriggered: {
                    Player.pause()
                }
            }
        }

        Menu {
            title: qsTr("View")
            Action {
                text: qsTr("All songs")
            }
            Action {
                text: qsTr("Albums")
            }
            Action {
                text: qsTr("Artists")
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

    // 2 sides
    RowLayout {
        anchors.fill: parent
        width: parent.width
        height: parent.height

        // left collumn
        Item{
            id: leftcolumn
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width/5 * 3

            ListView{
                id: songlist
                width: leftcolumn.width - 40
                x: 20
                height: leftcolumn.height
                clip: true
                spacing: 30
                snapMode: ListView.SnapToItem

                model: SongModel {
                    playlist: Playlist
                }

                header: Item {
                    width: songlist.width
                    height: 100

                    Text {
                        text: "All songs (" + Playlist.count + ")"
                        anchors.centerIn: parent
                        color: "white"
                        font.pointSize: 24
                    }
                }

                delegate:  Rectangle{
                    width: songlist.width
                    height: 100
                    x: 20
                    color: "#1f1f1f"
                    border.color: "white"
                    border.width: 1
                    radius: 10

                    RowLayout {
                        spacing: 0
                        anchors.fill: parent

                        Rectangle{
                            color: "transparent"
                            id: rect1
                            Layout.preferredHeight: parent.height
                            Layout.preferredWidth: parent.height

                            Image {
                                id: songCover
                                source: model.cover
                                anchors.centerIn: rect1
                                width: rect1.width * 0.8
                                height: rect1.height * 0.8
                                visible: false
                            }

                            MultiEffect {
                                source: songCover
                                anchors.fill: songCover
                                maskEnabled: true
                                maskSource: mask
                            }

                            Item {
                                id: mask
                                width: songCover.width
                                height: songCover.height
                                visible: false
                                // @disable-check M16
                                layer.enabled: true

                                Rectangle {
                                    width: songCover.width
                                    height: songCover.height
                                    radius: 10
                                    color: "white"
                                }
                            }

                        }
                        Rectangle{
                            color: "transparent"
                            id: rect2
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            ColumnLayout{
                                anchors.fill: parent
                                spacing: 0
                                Rectangle{
                                    color: "transparent"
                                    Layout.preferredHeight: parent.height * 0.55
                                    Layout.fillWidth: true
                                    clip: true
                                    Text{
                                        text: model.title
                                        anchors.bottom: parent.bottom
                                        anchors.left: parent.left
                                        anchors.bottomMargin: 2
                                        anchors.leftMargin: 10
                                        color: "white"
                                        font.pointSize: 18
                                        elide: Text.ElideLeft
                                    }
                                }
                                Rectangle{
                                    color: "transparent"
                                    Layout.preferredHeight: parent.height * 0.45
                                    Layout.fillWidth: true
                                    clip: true
                                    Text{
                                        text: {model.artist + " - " + model.album}
                                        anchors.top: parent.top
                                        anchors.left: parent.left
                                        anchors.topMargin: 2
                                        anchors.leftMargin: 10
                                        font.pointSize: 10
                                        color: "white"
                                        elide: Text.ElideLeft
                                    }

                                }
                            }
                        }

                        Rectangle{
                            color: "transparent"
                            Layout.preferredHeight: parent.height
                            Layout.preferredWidth: parent.height
                            Text{
                                anchors.centerIn: parent
                                text:  "0:00"
                                font.pointSize: 14
                                color: "white"
                            }
                        }

                    }
                }
            }

            Rectangle{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                width: parent.width
                height: 100

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "transparent" }
                    GradientStop { position: 1.0; color: "black" }
                }
            }
        }

        ColumnLayout{
            id: rightcolumn
            Layout.fillWidth: false
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width/5 * 2
            Layout.alignment: Qt.AlignTop


        }
    }

    FileDialog {
        id: fileDialog
        title: "Open song"
        currentFolder: StandardPaths.standardLocations(StandardPaths.MusicLocation)[0]
        onAccepted: {
            FileManager.openFile(fileDialog.selectedFile)
        }
    }
}
