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
import com.teamcex.ThemeManager

ApplicationWindow {
    width: 1280
    height: 720
    minimumHeight: 720
    minimumWidth: 1280
    visible: true
    title: qsTr("QMusicPlayer")
    Universal.theme: Universal.Dark
    Universal.accent: ThemeManager.accentColor === -1 ? Universal.Cobalt : ThemeManager.accentColor
    id: root

    property string filterType: ""

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
                onTriggered: {
                    filterType = ""
                    Player.order = "all"
                }
            }
            Action {
                text: qsTr("Albums")
                onTriggered: {
                    filterType = "album"
                    Player.order = "album"
                }
            }
            Action {
                text: qsTr("Artists")
                onTriggered: {
                    filterType = "artist"
                    Player.order = "artist"
                }
            }
        }

        Menu {
            title: qsTr("Options")
            Action {
                text: qsTr("Settings")
                onTriggered: {
                    var component = Qt.createComponent("settings.qml")
                    var window    = component.createObject(root)
                    window.show()
                }
            }
            Action {
                text: qsTr("About")
                onTriggered: {
                    var component = Qt.createComponent("about.qml")
                    var window    = component.createObject(root)
                    window.show()
                }
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
                width: leftcolumn.width - 30
                x: 30
                height: leftcolumn.height
                clip: true
                spacing: 30
                currentIndex: -1

                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }

                model: SongModel {
                    playlist: Playlist
                    orderBy: filterType
                }

                section.property: filterType
                section.criteria: ViewSection.FullString
                section.delegate: Item {
                    width: songlist.width - 30
                    height: 100

                    Text {
                        text: section
                        anchors.centerIn: parent
                        color: "white"
                        font.pointSize: 16
                    }
                }

                /* - bugs out text, maybe later
                highlight: Rectangle {
                    color: "transparent"
                    width: songlist.currentItem.width
                    height: songlist.currentItem.height
                    x: songlist.currentItem.x
                    y: songlist.currentItem.y
                    border.color: "red"
                    border.width: 2
                    radius: 10
                    z: 2
                }

                highlightRangeMode: ListView.ApplyRange
                highlightMoveDuration: 300
                preferredHighlightBegin: songlist.top
                preferredHighlightEnd: songlist.bottom
                */

                header: Item {
                    width: songlist.width - 30
                    height: 100

                    Text {
                        text: "All songs (" + Playlist.count + ")"
                        anchors.centerIn: parent
                        color: "white"
                        font.pointSize: 24
                    }
                }

                delegate:  Rectangle{
                    width: songlist.width - 30
                    height: 100
                    x: 20
                    color: "#1f1f1f"
                    border.color: (Player.currentSong === null || model.song.source !== Player.currentSong.source) ? "white" : Universal.accent
                    border.width: 2
                    radius: 10

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(Player.playing && Player.currentSong.source === model.song.source) {
                                Player.pause()
                            } else if (!Player.playing && Player.currentSong && Player.currentSong.source === model.song.source) {
                                Player.play()
                            } else {
                                Player.open(model.song)
                                songlist.currentIndex = index
                            }
                        }
                    }

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
                                fillMode: Image.PreserveAspectCrop
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
                                text:  {
                                    var duration = model.duration / 1000
                                    var minutes = Math.floor(duration / 60)
                                    var seconds = Math.floor(duration % 60)
                                    if (seconds < 10) {
                                        seconds = "0" + seconds
                                    }
                                    minutes + ":" + seconds
                                }

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
            Layout.preferredHeight: parent.height

            visible: Player.currentSong !== null

            Item {
                Layout.fillHeight: true
            }

            Rectangle{
                color:"transparent"
                Layout.preferredHeight: Math.min(parent.width*0.8, parent.height * 0.6)
                Layout.preferredWidth: Math.min(parent.width*0.8, parent.height * 0.6)
                Layout.alignment: Qt.AlignCenter
                id: songImageContainer
                Image {
                    id: songImage
                    source: Player.currentSong.coverUrl
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                }
            }
            Rectangle{
                color:"transparent"
                Layout.preferredWidth: songImageContainer.width
                Layout.preferredHeight: 35
                Layout.alignment: Qt.AlignCenter
                clip: true
                Label{
                    text: Player.currentSong.title
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 18
                    width: songImageContainer.width
                    elide: Text.ElideRight
                }
            }
            Rectangle{
                color:"transparent"
                Layout.preferredWidth: songImageContainer.width
                Layout.preferredHeight: 20
                Layout.alignment: Qt.AlignCenter
                clip: true
                Label{
                    text: Player.currentSong.artist + " - " + Player.currentSong.album
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 10
                    width: songImageContainer.width
                    elide: Text.ElideRight
                }
            }
            Slider {
                Layout.preferredWidth: songImageContainer.width
                Layout.preferredHeight: 40
                Layout.alignment: Qt.AlignCenter
                value: Player.timecode
                from: 0
                to: Player.currentSong.duration

                onMoved: {
                    Player.timecode = value
                }
            }
            RowLayout{
                spacing: 0
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: songImageContainer.width
                Layout.preferredHeight: 50


                RoundButton {
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.height
                    Layout.alignment: Qt.AlignHCenter
                    radius: width/2
                    icon.source: "qrc:/static/repeat.svg"
                    background: Item{}
                    Universal.foreground: Player.loop ? Universal.accent : "white"

                    onClicked: {
                        Player.loop = !Player.loop
                    }
                }

                RoundButton {
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.height
                    Layout.alignment: Qt.AlignHCenter
                    radius: width/2
                    icon.source: "qrc:/static/play-skip-back.svg"
                    background: Item{}

                    onClicked: {
                        Player.previous()
                    }
                }
                RoundButton {
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.height
                    Layout.alignment: Qt.AlignHCenter
                    radius: width/2
                    icon.source: Player.playing ? "qrc:/static/pause.svg" : "qrc:/static/play.svg"
                    onClicked: {
                        if(Player.playing) {
                            Player.pause()
                        } else {
                            Player.play()
                        }
                    }
                }
                RoundButton {
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.height
                    Layout.alignment: Qt.AlignHCenter
                    radius: width/2
                    icon.source: "qrc:/static/play-skip-forward.svg"
                    background: Item{}

                    onClicked: {
                        Player.next()
                    }
                }

                Item{
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.height
                    Layout.alignment: Qt.AlignHCenter

                    RoundButton {
                        id: volumeButton
                        anchors.fill: parent
                        radius: width/2
                        icon.source: {
                            if (Player.audioOutput.muted){
                                "qrc:/static/volume-mute.svg"
                            } else if (Player.audioOutput.volume === 0) {
                                "qrc:/static/volume-off.svg"
                            } else if (Player.audioOutput.volume < 0.3) {
                                "qrc:/static/volume-low.svg"
                            } else if (Player.audioOutput.volume < 0.7) {
                                "qrc:/static/volume-medium.svg"
                            } else {
                                "qrc:/static/volume-high.svg"
                            }
                        }

                        background: Item{}

                        onClicked: {
                            Player.audioOutput.muted = !Player.audioOutput.muted
                        }

                    }

                    Rectangle {
                        id: volumeSlider
                        height: 100
                        width: 35
                        anchors.bottom: parent.top
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: volumeButton.hovered || volume.hovered || volume.pressed
                        color: "#1f1f1f"
                        border.color: "white"
                        border.width: 1
                        radius: 5

                        Slider {
                            id: volume
                            anchors.fill: parent
                            orientation: Qt.Vertical
                            from: 0
                            to: 1
                            value: Player.audioOutput.volume
                            onMoved: {
                                Player.audioOutput.volume = value
                            }
                            onPressedChanged: {
                                if (!pressed) {
                                    Player.saveVolume()
                                }
                            }
                        }
                    }
                }
            }

            Item {
                Layout.fillHeight: true
            }
        }

        Item {
            visible: Player.currentSong === null
            Layout.fillHeight: true
            Layout.fillWidth: true

            Label{
                anchors.centerIn: parent
                text: "No song selected"
                font.pointSize: 24
            }
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
