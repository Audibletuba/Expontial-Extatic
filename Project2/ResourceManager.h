#include <string>

#include "Manager.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"

const int MAX_SPRITES = 500;
const int MAX_SOUNDS = 50;
const int MAX_MUSICS = 50;

class ResourceManager : public Manager
{
private:
    ResourceManager();

    ResourceManager(ResourceManager const&);
    void operator=(ResourceManager const&);

    Sprite* m_p_sprite[MAX_SPRITES];
    int m_sprite_count;

    Sound m_sound[MAX_SOUNDS];       // Array of sound buffers.
    int m_sound_count;               // Count of number of loaded sounds.

    Music m_music[MAX_MUSICS];       // Array of music buffers.
    int m_music_count;               // Count of number of loaded musics.

public:
    static ResourceManager& getInstance();

    int startUp();
    void shutDown();

    int loadSprite(std::string filename, std::string label);

    int unloadSprite(std::string label);

    Sprite* getSprite(std::string label) const;

    // Load Sound from file.
    // Return 0 if ok, else -1.

    int loadSound(std::string filename, std::string label);

    // Remove Sound with indicated label.
    // Return 0 if ok, else -1.
    int unloadSound(std::string label);

    // Find Sound with indicated label.
    // Return pointer to it if found, else NULL.
    Sound* getSound(std::string label);

    // Associate file with Music.
    // Return 0 if ok, else -1.
    int loadMusic(std::string filename, std::string label);

    // Remove label for Music with indicated label.
    // Return 0 if ok, else -1.
    int unloadMusic(std::string label);

    // Find Music with indicated label.
    // Return pointer to it if found, else NULL.
    Music* getMusic(std::string label);

};