#pragma once
#include "core/AudioEngine.hpp"
#include "models/Playlist.hpp"
#include "models/Song.hpp"
#include "strategies/PlayStrategy.hpp"
#include "enums/DeviceType.hpp"
#include "enums/PlayStrategyType.hpp"
#include "managers/DeviceManager.hpp"
#include "managers/PlaylistManager.hpp"
#include "managers/StrategyManager.hpp"

using namespace std;

class MusicPlayerFacade {
private:
    static MusicPlayerFacade* instance;
    AudioEngine* audioEngine;#pragma once
#include "managers/PlaylistManager.hpp"
#include "MusicPlayerFacade.hpp"

using namespace std;

class MusicPlayerApplication {
private:
    static MusicPlayerApplication* instance;
    vector<Song*> songLibrary;
    MusicPlayerApplication() {}

public:
    static MusicPlayerApplication* getInstance() {
        if (!instance) {
            instance = new MusicPlayerApplication();
        }
        return instance;
    }

    void createSongInLibrary(const string& title, const string& artist,
                                const string& path) {
        Song* newSong = new Song(title, artist, path);
        songLibrary.push_back(newSong);
    }

    Song* findSongByTitle(const string& title) {
        for (Song* s : songLibrary) {
            if (s->getTitle() == title) {
                return s;
            }
        }
        return nullptr;
    }
    void createPlaylist(const string& playlistName) {
        PlaylistManager::getInstance()->createPlaylist(playlistName);
    }

    void addSongToPlaylist(const string& playlistName,
                            const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found in library.");
        }
        PlaylistManager::getInstance()
            ->addSongToPlaylist(playlistName, song);
    }

    void connectAudioDevice(DeviceType deviceType) {
        MusicPlayerFacade::getInstance()->connectDevice(deviceType);
    }

    void selectPlayStrategy(PlayStrategyType strategyType) {
        MusicPlayerFacade::getInstance()->setPlayStrategy(strategyType);
    }

    void loadPlaylist(const string& playlistName) {
        MusicPlayerFacade::getInstance()->loadPlaylist(playlistName);
    }

    void playSingleSong(const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found.");
        }
        MusicPlayerFacade::getInstance()->playSong(song);
    }

    void pauseCurrentSong(const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found.");
        }
        MusicPlayerFacade::getInstance()->pauseSong(song);
    }

    void playAllTracksInPlaylist() {
        MusicPlayerFacade::getInstance()->playAllTracks();
    }

    void playPreviousTrackInPlaylist() {
        MusicPlayerFacade::getInstance()->playPreviousTrack();
    }

    void queueSongNext(const string& songTitle) {
        Song* song = findSongByTitle(songTitle);
        if (!song) {
            throw runtime_error("Song \"" + songTitle + "\" not found.");
        }
        MusicPlayerFacade::getInstance()->enqueueNext(song);
    }
};

MusicPlayerApplication* MusicPlayerApplication::instance = nullptr;
    Playlist* loadedPlaylist;
    PlayStrategy* playStrategy;

    MusicPlayerFacade() {
        loadedPlaylist = nullptr;
        playStrategy   = nullptr;
        audioEngine = new AudioEngine();
    }

public:
    static MusicPlayerFacade* getInstance() {
        if (!instance) {
            instance = new MusicPlayerFacade();
        }
        return instance;
    }

    void connectDevice(DeviceType deviceType) {
        DeviceManager::getInstance()->connect(deviceType);
    }

    void setPlayStrategy(PlayStrategyType strategyType) {
        playStrategy = StrategyManager::getInstance()->getStrategy(strategyType);
    }

    void loadPlaylist(const string& name) {
        loadedPlaylist = PlaylistManager::getInstance()->getPlaylist(name);
        if (!playStrategy) {
            throw runtime_error("Play strategy not set before loading.");
        }
        playStrategy->setPlaylist(loadedPlaylist);
    }
    
    void playSong(Song* song) {
        if (!DeviceManager::getInstance()->hasOutputDevice()) {
            throw runtime_error("No audio device connected.");
        }
        IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
        audioEngine->play(device, song);
    }

    void pauseSong(Song* song) {
        if (audioEngine->getCurrentSongTitle() != song->getTitle()) {
            throw runtime_error("Cannot pause \"" + song->getTitle() + "\"; not currently playing.");
        }
        audioEngine->pause();
    }

    void playAllTracks() {
        if (!loadedPlaylist) {
            throw runtime_error("No playlist loaded.");
        }
        while (playStrategy->hasNext()) {
            Song* nextSong = playStrategy->next();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        cout << "Completed playlist: " << loadedPlaylist->getPlaylistName() << "\n";
    }

    void playNextTrack() {
        if (!loadedPlaylist) {
            throw runtime_error("No playlist loaded.");
        }
        if(playStrategy->hasNext()) {
            Song* nextSong = playStrategy->next();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, nextSong);
        }
        else {
            cout << "Completed playlist: " << loadedPlaylist->getPlaylistName() << "\n";
        }
    }

    void playPreviousTrack() {
        if (!loadedPlaylist) {
            throw runtime_error("No playlist loaded.");
        }
        if(playStrategy->hasPrevious()) {
            Song* prevSong = playStrategy->previous();
            IAudioOutputDevice* device = DeviceManager::getInstance()->getOutputDevice();
            audioEngine->play(device, prevSong);
        }
        else {
            cout << "Completed playlist: " << loadedPlaylist->getPlaylistName() << "\n";
        }
    }

    void enqueueNext(Song* song) {
        playStrategy->addToNext(song);
    }
};

MusicPlayerFacade* MusicPlayerFacade::instance = nullptr;
    