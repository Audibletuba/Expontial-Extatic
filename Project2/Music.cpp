#include "Music.h"

Music::Music()
{
    m_p_music = nullptr;
    m_label = "";
}

Music::~Music()
{
    if (m_p_music != nullptr)
    {
        delete m_p_music;
        m_p_music = nullptr;
    }
}

int Music::loadMusic(std::string filename)
{
    sf::Music* new_music = new sf::Music();

    if (!new_music->openFromFile(filename))
    {
        delete new_music;
        return -1;
    }

    if (m_p_music != nullptr)
    {
        delete m_p_music;
    }

    m_p_music = new_music;

    return 0;
}

void Music::setLabel(std::string new_label)
{
    m_label = new_label;
}

std::string Music::getLabel() const
{
    return m_label;
}

void Music::play(bool loop)
{
    if (m_p_music == nullptr)
    {
        return;
    }

    m_p_music->setLooping(loop);
    m_p_music->play();
}

void Music::stop()
{
    if (m_p_music == nullptr)
    {
        return;
    }

    m_p_music->stop();
}

void Music::pause()
{
    if (m_p_music == nullptr)
    {
        return;
    }

    m_p_music->pause();
}

sf::Music* Music::getMusic()
{
    return m_p_music;
}