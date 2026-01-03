
# 🎬 CQtMedia

A full-featured **C++/Qt 6 media player** with AI-powered chapter detection, intro/outro skipping, fuzzy search, and recommendations.

## ✨ Features
- Play **MP3, MP4, WAV** (and more with codecs installed)
- Playlist management (add files/folders, next/prev)
- Playback controls (play/pause, seek, speed, mute)
- **AI chapter detection** with a polished chapter bar
- Skip intro/outro automatically
- Fuzzy search in playlist
- Session persistence (remembers last playlist, position, volume)
- Snapshot current frame to PNG

## 🚀 Build Instructions
```bash
# Install Qt6 and GStreamer plugins (Linux example)
sudo apt install qt6-base-dev qt6-multimedia-dev gstreamer1.0-libav gstreamer1.0-plugins-good

# Build
cmake -B build -S .
cmake --build build

# Run
./build/CQtMedia
