#include "ResourceManager.h"
#include "Frame.h"
#include "LogManager.h"

#include <fstream>
#include <cstdlib>
#include <iostream>

ResourceManager::ResourceManager()
{
    m_sound_count = 0;
    m_music_count = 0;
    m_sprite_count = 0;
}

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

int ResourceManager::startUp()
{
    return 0;
}

void ResourceManager::shutDown()
{
}
int ResourceManager::loadSprite(
    std::string filename,
    std::string label)
{
    // Check if room in array.
    if (m_sprite_count >= MAX_SPRITES)
    {
        std::cout << "ERROR: Sprite array full." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): sprite array full."
        );

        return -1;
    }

    // Open file.
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "ERROR: Could not open file: "
            << filename << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): could not open file."
        );

        return -1;
    }

    std::cout << "File opened successfully." << std::endl;

    std::string line;

    // Read sprite header.
    if (!std::getline(file, line))
    {
        std::cout << "ERROR: Missing frame count." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): missing frame count."
        );

        return -1;
    }

    int frames = std::atoi(line.c_str());

    std::cout << "Frames: " << frames << std::endl;

    if (frames <= 0)
    {
        std::cout << "ERROR: Invalid frame count." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): invalid frame count."
        );

        return -1;
    }

    if (!std::getline(file, line))
    {
        std::cout << "ERROR: Missing width." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): missing width."
        );

        return -1;
    }

    int width = std::atoi(line.c_str());

    std::cout << "Width: " << width << std::endl;

    if (width <= 0)
    {
        std::cout << "ERROR: Invalid width." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): invalid width."
        );

        return -1;
    }

    if (!std::getline(file, line))
    {
        std::cout << "ERROR: Missing height." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): missing height."
        );

        return -1;
    }

    int height = std::atoi(line.c_str());

    std::cout << "Height: " << height << std::endl;

    if (height <= 0)
    {
        std::cout << "ERROR: Invalid height." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): invalid height."
        );

        return -1;
    }

    if (!std::getline(file, line))
    {
        std::cout << "ERROR: Missing slowdown." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): missing slowdown."
        );

        return -1;
    }

    int slowdown = std::atoi(line.c_str());

    std::cout << "Slowdown: " << slowdown << std::endl;

    if (slowdown <= 0)
    {
        std::cout << "ERROR: Invalid slowdown." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): invalid slowdown."
        );

        return -1;
    }

    if (!std::getline(file, line))
    {
        std::cout << "ERROR: Missing color." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): missing color."
        );

        return -1;
    }

    std::cout << "Color: [" << line << "]" << std::endl;

    Color color = COLOR_DEFAULT;

    if (line == "black")
    {
        color = BLACK;
    }
    else if (line == "red")
    {
        color = RED;
    }
    else if (line == "green")
    {
        color = GREEN;
    }
    else if (line == "yellow")
    {
        color = YELLOW;
    }
    else if (line == "blue")
    {
        color = BLUE;
    }
    else if (line == "magenta")
    {
        color = MAGENTA;
    }
    else if (line == "cyan")
    {
        color = CYAN;
    }
    else if (line == "white")
    {
        color = WHITE;
    }
    else
    {
        std::cout << "ERROR: Invalid color." << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): invalid color."
        );

        return -1;
    }

    // Make new Sprite.
    Sprite* p_sprite = new Sprite(frames);

    p_sprite->setWidth(width);
    p_sprite->setHeight(height);
    p_sprite->setSlowdown(slowdown);
    p_sprite->setColor(color);

    std::cout << "Sprite created." << std::endl;

    // Read and add frames to Sprite.
    for (int f = 0; f < frames; f++)
    {
        std::string frame_string = "";

        std::cout << "Reading frame "
            << f
            << std::endl;

        for (int h = 0; h < height; h++)
        {
            if (!std::getline(file, line))
            {
                std::cout << "ERROR: Missing frame data."
                    << std::endl;

                LogManager::getInstance().writeLog(
                    "ResourceManager::loadSprite(): "
                    "missing frame data."
                );

                delete p_sprite;
                return -1;
            }

            std::cout << "  Line: [" << line << "]"
                << std::endl;

            if (static_cast<int>(line.length()) != width)
            {
                std::cout
                    << "ERROR: Frame row has incorrect width."
                    << std::endl;

                LogManager::getInstance().writeLog(
                    "ResourceManager::loadSprite(): "
                    "frame row has incorrect width."
                );

                delete p_sprite;
                return -1;
            }

            frame_string += line;
        }

        Frame frame;

        frame.setString(frame_string);
        frame.setHeight(height);
        frame.setWidth(width);

        if (p_sprite->addFrame(frame) != 0)
        {
            std::cout << "ERROR: Could not add frame."
                << std::endl;

            LogManager::getInstance().writeLog(
                "ResourceManager::loadSprite(): "
                "could not add frame."
            );

            delete p_sprite;
            return -1;
        }
    }
    // Check for extra data after the final frame.
    if (std::getline(file, line))
    {
        std::cout
            << "ERROR: Extra data after final frame."
            << std::endl;

        LogManager::getInstance().writeLog(
            "ResourceManager::loadSprite(): "
            "extra data after final frame."
        );

        delete p_sprite;
        return -1;
    }

    // Close file.
    file.close();
    

    // Add sprite to resource manager.
    p_sprite->setLabel(label);

    m_p_sprite[m_sprite_count] = p_sprite;
    m_sprite_count++;

    std::cout << "Sprite loaded successfully."
        << std::endl;

    return 0;
}

int ResourceManager::unloadSprite(std::string label)
{
    for (int i = 0; i < m_sprite_count; i++)
    {
        if (m_p_sprite[i]->getLabel() == label)
        {
            delete m_p_sprite[i];

            for (int j = i; j < m_sprite_count - 1; j++)
            {
                m_p_sprite[j] = m_p_sprite[j + 1];
            }

            m_sprite_count--;

            return 0;
        }
    }

    return -1;
}

Sprite* ResourceManager::getSprite(std::string label) const
{
    for (int i = 0; i < m_sprite_count; i++)
    {
        if (m_p_sprite[i]->getLabel() == label)
        {
            return m_p_sprite[i];
        }
    }

    return nullptr;
}

int ResourceManager::loadSound(
    std::string filename,
    std::string label)
{
    // Check if room in array.
    if (m_sound_count >= MAX_SOUNDS)
    {
        LogManager::getInstance().writeLog(
            "Sound array full."
        );

        return -1;
    }

    if (m_sound[m_sound_count].loadSound(filename) != 0)
    {
        LogManager::getInstance().writeLog(
            "Unable to load from file"
        );

        return -1;
    }

    // All is well.
    m_sound[m_sound_count].setLabel(label);
    m_sound_count++;

    return 0;
}
// Remove Sound with indicated label.
// Return 0 if ok, else -1.
int ResourceManager::unloadSound(std::string label)
{
    for (int i = 0; i < m_sound_count; i++)
    {
        if (label == m_sound[i].getLabel())
        {
            // Scoot over remaining sounds.
            for (int j = i; j < m_sound_count - 1; j++)
            {
                m_sound[j] = m_sound[j + 1];
            }

            m_sound_count--;

            return 0;
        }
    }

    return -1; // Sound not found.
}

// Find Sound with indicated label.
// Return pointer to it if found, else NULL.
Sound* ResourceManager::getSound(std::string label)
{
    for (int i = 0; i < m_sound_count; i++)
    {
        if (label == m_sound[i].getLabel())
        {
            return &m_sound[i];
        }
    }

    return nullptr; // Sound not found.
}
int ResourceManager::loadMusic(std::string filename, std::string label)
{
    if (m_music_count >= MAX_MUSICS)
    {
        return -1;
    }

    for (int i = 0; i < MAX_MUSICS; i++)
    {
        if (m_music[i].getLabel() == "")
        {
            if (m_music[i].loadMusic(filename) != 0)
            {
                return -1;
            }

            m_music[i].setLabel(label);
            m_music_count++;

            return 0;
        }
    }

    return -1;
}

// Remove Music with indicated label.
// Return 0 if ok, else -1.
int ResourceManager::unloadMusic(std::string label)
{
    for (int i = 0; i < MAX_MUSICS; i++)
    {
        if (label == m_music[i].getLabel())
        {
            m_music[i].setLabel("");
            m_music_count--;

            return 0;
        }
    }

    return -1; // Music not found.
}

Music* ResourceManager::getMusic(std::string label)
{
    for (int i = 0; i < MAX_MUSICS; i++)
    {
        if (m_music[i].getLabel() == label)
        {
            return &m_music[i];
        }
    }

    return nullptr;
}