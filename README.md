<p align="center">
  <img src="https://github.com/ZyphenVisuals/QMusicPlayer/assets/55757807/a196b258-fc9d-4a19-b5b7-bd36db63906b" width=300 alt="QMusicPlayer logo" >
</p>

# QMusicPlayer

QMusicPlayer is a simple music player written in C++ and QML. Built with passion, caffeine and sleep deprivation by *Team CEX*, as well as some magic from *The Qt Company*.

This project was created as part of an assignment from the West University of Timisoara.

## Dependencies

QMusicPlayer was built using the [Qt Framework](https://www.qt.io/product/framework).

The minimal installation needed to compile and run this project consists of:

- Qt 6.7.1 or higher
  - MinGW kit (Recommended, though other desktop kits like MSVC sould work too)
  - Qt Shader Tools
  - Additional Libraries
    - Qt Multimedia
- Developer and Designer Tools
    - Qt Creator (Optional, but strongle recommended)
    - CMake
    - Ninja

## Building

Since we provide no pre-built binaries, you will need to compile this program from scratch by following these steps:

1. Ensure you have a [kit configured](https://doc.qt.io/qtcreator/creator-targets.html) in Qt Creator
2. Clone this repository and open it in Qt Creator
3. Press "Run"
4. Enjoy the magic!

## Usage

### Playing a single song

1. Go to File>Open song
2. Find your favorite track
3. Magic!

### Importing folders

Selecting folders to import is done within the settings, since these are remembered across restarts.

1. Go to Options>Settings
2. In the "Folder paths" section, click on "Add folder"
3. Navigate to the folder that contains your favorite tracks
4. Magic!

### Organizing your media

QMediaPlayer is able tu automatically group your music by artist or by album.

1. Change the grouping mode using the View menu
2. Magic!

### Personalization

The settings also allow you to change the accent color of the application.

1. Go to Options>Settings
2. Under "Personalization" change "Accent color"
3. Magic!
