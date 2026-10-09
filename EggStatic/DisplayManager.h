#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Color.h"
#include "Manager.h"
#include "Vector.h"


enum Justification
{
    LEFT_JUSTIFIED,
    CENTER_JUSTIFIED,
    RIGHT_JUSTIFIED
};
// Default window settings.
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";

class DisplayManager : public Manager
{
private:
    DisplayManager();
    DisplayManager(DisplayManager const&);
    void operator=(DisplayManager const&);

    sf::Font m_font;
    sf::RenderWindow* m_p_window;

    int m_window_horizontal_pixels;
    int m_window_vertical_pixels;

    int m_window_horizontal_chars;
    int m_window_vertical_chars;

    // Convert Dragonfly world coordinates to pixel coordinates.
    Vector spacesToPixels(Vector world_pos) const;

    // Width of one character in pixels.
    int charWidth() const;

    // Height of one character in pixels.
    int charHeight() const;

public:
    static DisplayManager& getInstance();

    int startUp();

    void shutDown();

    int drawCh(Vector world_pos, char ch, Color color) const;

    int drawString(
        Vector pos,
        std::string str,
        Justification just,
        Color color
    ) const;

    int getHorizontal() const;

    int getVertical() const;

    int getHorizontalPixels() const;

    int getVerticalPixels() const;

    int swapBuffers();

    sf::RenderWindow* getWindow() const;

    Vector worldToView(Vector world_pos) const;
};