#include "Sound.h"

Sound::Sound()
{
    m_p_sound = nullptr;
    m_label = "";
}

Sound::~Sound()
{
    if (m_p_sound != nullptr)
    {
        delete m_p_sound;
        m_p_sound = nullptr;
    }
}

Sound::Sound(const Sound& other)
{
    m_p_sound = nullptr;
    m_label = other.m_label;
    m_sound_buffer = other.m_sound_buffer;

    if (other.m_p_sound != nullptr)
    {
        m_p_sound = new sf::Sound(m_sound_buffer);
    }
}

Sound& Sound::operator=(const Sound& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (m_p_sound != nullptr)
    {
        delete m_p_sound;
        m_p_sound = nullptr;
    }

    m_label = other.m_label;
    m_sound_buffer = other.m_sound_buffer;

    if (other.m_p_sound != nullptr)
    {
        m_p_sound = new sf::Sound(m_sound_buffer);
    }

    return *this;
}

int Sound::loadSound(std::string filename)
{
    if (!m_sound_buffer.loadFromFile(filename))
    {
        return -1;
    }

    if (m_p_sound != nullptr)
    {
        delete m_p_sound;
    }

    m_p_sound = new sf::Sound(m_sound_buffer);

    return 0;
}

void Sound::setLabel(std::string new_label)
{
    m_label = new_label;
}

std::string Sound::getLabel() const
{
    return m_label;
}

void Sound::play(bool loop)
{
    if (m_p_sound == nullptr)
    {
        return;
    }

    m_p_sound->setLooping(loop);
    m_p_sound->play();
}

void Sound::stop()
{
    if (m_p_sound == nullptr)
    {
        return;
    }

    m_p_sound->stop();
}

void Sound::pause()
{
    if (m_p_sound == nullptr)
    {
        return;
    }

    m_p_sound->pause();
}

sf::Sound Sound::getSound() const
{
    return *m_p_sound;
}