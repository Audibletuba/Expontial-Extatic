#include "DisplayManager.h"
#include "WorldManager.h"

DisplayManager::DisplayManager()
{
    m_p_window = nullptr;

    m_window_horizontal_pixels =
        WINDOW_HORIZONTAL_PIXELS_DEFAULT;

    m_window_vertical_pixels =
        WINDOW_VERTICAL_PIXELS_DEFAULT;

    m_window_horizontal_chars =
        WINDOW_HORIZONTAL_CHARS_DEFAULT;

    m_window_vertical_chars =
        WINDOW_VERTICAL_CHARS_DEFAULT;
}

DisplayManager& DisplayManager::getInstance()
{
    static DisplayManager instance;
    return instance;
}

int DisplayManager::startUp()
{
    // check if window already exists.
    if (m_p_window != nullptr)
    {
        return 0;
    }

    // Create SFML 3 window.
    sf::VideoMode video_mode(
        sf::Vector2u(
            static_cast<unsigned int>(m_window_horizontal_pixels),
            static_cast<unsigned int>(m_window_vertical_pixels)
        ),
        32
    );

    m_p_window = new sf::RenderWindow(
        video_mode,
        WINDOW_TITLE_DEFAULT,
        WINDOW_STYLE_DEFAULT

    );

    // Create Window
    if (!m_p_window->isOpen())
    {
        delete m_p_window;
        m_p_window = nullptr;
        return -1;
    }

    // Hide mouse cursor.
    m_p_window->setMouseCursorVisible(false);

    // Synchronize with monitor refresh rate.
    m_p_window->setVerticalSyncEnabled(true);

    // Load Dragonfly font.
    if (!m_font.openFromFile(FONT_FILE_DEFAULT))
    {
        m_p_window->close();

        delete m_p_window;
        m_p_window = nullptr;

        return -1;
    }

    Manager::startUp();

    return 0;
}

void DisplayManager::shutDown()
{
    if (m_p_window != nullptr)
    {
        m_p_window->close();

        delete m_p_window;
        m_p_window = nullptr;
    }

    Manager::shutDown();
}

sf::RenderWindow* DisplayManager::getWindow() const
{
    return m_p_window;
}

int DisplayManager::getHorizontal() const
{
    return m_window_horizontal_chars;
}

int DisplayManager::getVertical() const
{
    return m_window_vertical_chars;
}

int DisplayManager::getHorizontalPixels() const
{
    return m_window_horizontal_pixels;
}

int DisplayManager::getVerticalPixels() const
{
    return m_window_vertical_pixels;
}

int DisplayManager::swapBuffers()
{
    if (m_p_window == nullptr)
    {
        return -1;
    }

    m_p_window->display();
    m_p_window->clear();

    return 0;
}

Vector DisplayManager::spacesToPixels(Vector world_pos) const
{
    int pixel_x =
        world_pos.getX() * charWidth();

    int pixel_y =
        world_pos.getY() * charHeight();

    return Vector(pixel_x, pixel_y);
}

int DisplayManager::charWidth() const
{
    return m_window_horizontal_pixels /
        m_window_horizontal_chars;
}

int DisplayManager::charHeight() const
{
    return m_window_vertical_pixels /
        m_window_vertical_chars;
}

int DisplayManager::drawString(
    Vector pos,
    std::string str,
    Justification just,
    Color color) const
{
    // Get starting position.
    Vector starting_pos = pos;

    switch (just)
    {
    case CENTER_JUSTIFIED:
        starting_pos.setX(
            pos.getX() - static_cast<int>(str.size()) / 2
        );
        break;

    case RIGHT_JUSTIFIED:
        starting_pos.setX(
            pos.getX() - static_cast<int>(str.size())
        );
        break;

    case LEFT_JUSTIFIED:
    default:
        break;
    }

    // Draw string character by character.
    for (int i = 0; i < static_cast<int>(str.size()); i++)
    {
        Vector temp_pos(
            starting_pos.getX() + i,
            starting_pos.getY()
        );

        drawCh(temp_pos, str[i], color);
    }

    // All is well.
    return 0;
}

int DisplayManager::drawCh(Vector world_pos, char ch, Color color) const

{
    Vector view_pos = worldToView(world_pos);


    // Make sure window is allocated.
    if (m_p_window == nullptr)
    {
        return -1;
    }

    // Convert world position to pixel position.
    Vector pixel_pos = spacesToPixels(world_pos);

    // Draw background rectangle because SFML text
    // is transparent.
    sf::RectangleShape rectangle;

    rectangle.setSize(
        sf::Vector2f(
            static_cast<float>(charWidth()),
            static_cast<float>(charHeight())
        )
    );

    rectangle.setFillColor(
        WINDOW_BACKGROUND_COLOR_DEFAULT
    );

    rectangle.setPosition(
        sf::Vector2f(
            static_cast<float>(
                pixel_pos.getX() - charWidth() / 10
                ),
            static_cast<float>(
                pixel_pos.getY() + charHeight() / 5
                )
        )
    );

    m_p_window->draw(rectangle);

    // Create text.
    sf::Text text(
        m_font,
        std::string(1, ch)
    );

    // Make character bold.
    text.setStyle(sf::Text::Bold);

    // Set character size.
    if (charWidth() < charHeight())
    {
        text.setCharacterSize(
            static_cast<unsigned int>(
                charWidth() * 2
                )
        );
    }
    else
    {
        text.setCharacterSize(
            static_cast<unsigned int>(
                charHeight() * 2
                )
        );
    }

    // Set SFML color based on Dragonfly color.
    switch (color)
    {
    case YELLOW:
        text.setFillColor(sf::Color::Yellow);
        break;

    case RED:
        text.setFillColor(sf::Color::Red);
        break;

    case GREEN:
        text.setFillColor(sf::Color::Green);
        break;

    case BLUE:
        text.setFillColor(sf::Color::Blue);
        break;

    case MAGENTA:
        text.setFillColor(sf::Color::Magenta);
        break;

    case CYAN:
        text.setFillColor(sf::Color::Cyan);
        break;

    case WHITE:
        text.setFillColor(sf::Color::White);
        break;

    case BLACK:
        text.setFillColor(sf::Color::Black);
        break;

    default:
        text.setFillColor(sf::Color::White);
        break;
    }

    // Set text position.
    text.setPosition(
        sf::Vector2f(
            static_cast<float>(pixel_pos.getX()),
            static_cast<float>(pixel_pos.getY())
        )
    );

    // Draw character.
    m_p_window->draw(text);

    return 0;
}

Vector DisplayManager::worldToView(Vector world_pos) const
{
    Vector view_origin =
        WorldManager::getInstance().getView().getCorner();

    float view_x = view_origin.getX();
    float view_y = view_origin.getY();

    Vector view_pos(
        world_pos.getX() - view_x,
        world_pos.getY() - view_y
    );

    return view_pos;
}