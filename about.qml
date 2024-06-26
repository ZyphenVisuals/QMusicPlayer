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
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
        }

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

        Item {
            Layout.preferredHeight: 20
        }

        Label {
            text: "Built with passion, caffeine and sleep deprivation by *Team CEX*,"
            textFormat: "MarkdownText"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }

        Label{
            text: "as well as some magic from *The Qt Company*.";
            textFormat: "MarkdownText"
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            Layout.fillHeight: true
        }

        Label {
            text: "Icons from *Ionicons* by *Ionic*. Default album art from *Unsplash* by *Andrea Cipriani*."
            textFormat: "MarkdownText"
            font.pixelSize: 10
            Layout.alignment: Qt.AlignHCenter
        }

        Item {
            Layout.preferredHeight: 5
        }

    }
}
