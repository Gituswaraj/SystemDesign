/*
 * MusicPlayerApp/
│
├── main.cpp                          # Composition root and entry point
├── MusicPlayerFacade.hpp               # Facade class (orchestrator)
├── MusicPlayerApplication.hpp          # High-level application/demo runner
│
├── core/                          
│   └── AudioEngine.hpp                 # Playback engine          
│
├── enums/                              # All shared enum types
│   ├── DeviceType.hpp                  # enum class DeviceType { BLUETOOTH, WIRED, HEADPHONES }
│   └── PlayStrategyType.hpp            # enum class PlayStrategyType { SEQUENTIAL, RANDOM, CUSTOM_QUEUE }
│
├── models/
│   ├── Song.hpp
│   └── Playlist.hpp
│
├── managers/
│   ├── PlaylistManager.hpp
│   ├── DeviceManager.hpp
|   └── StrategyManager.hpp
│
├── strategies/
│   ├── PlayStrategy.hpp
│   ├── SequentialPlayStrategy.hpp
│   ├── RandomPlayStrategy.hpp
│   └── CustomQueueStrategy.hpp
│
├── device/                            # Audio device interfaces & adapters
│   ├── IAudioOutputDevice.hpp
│   ├── BluetoothSpeakerAdapter.hpp
│   ├── WiredSpeakerAdapter.hpp
│   └── HeadphonesAdapter.hpp
|
├── external/                           # External devices
│   ├── BluetoothSpeakerAPI.hpp
│   ├── HeadphonesAPI.hpp
│   └── WiredSpeakerAPI.hpp
│
        └── DeviceFactory.hpp               # Creates IAudioOutputDevice instances
    */