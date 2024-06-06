import QtQuick

import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Universal

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    maximumWidth: 800
    maximumHeight: 600
    title: qsTr("About - QMusicPlayer")
    Universal.theme: Universal.Dark
    id: root

    ColumnLayout {
        anchors.centerIn: parent
        Layout.alignment: Qt.AlignTop

        Image {
            source: "qrc:/static/QMP.png"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 200
            Layout.preferredWidth: 200
        }

        Label {
            text: "QMusicPlayer"
            font.pixelSize: 32
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: "QMusicPlayer is a simple music player written in C++ and QML."
            textFormat: "MarkdownText"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: "Built with passion by *Team CEX* and magic from *The Qt Company*."
            textFormat: "MarkdownText"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }

    }
}
