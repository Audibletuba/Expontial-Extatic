#include "Event.h"

// Create default Event
Event::Event()
{
    m_event_type = UNDEFINED_EVENT;
}

// Destroy Event
Event::~Event()
{
}

// Set event type
void Event::setType(std::string new_type)
{
    m_event_type = new_type;
}

// Get event type
std::string Event::getType() const
{
    return m_event_type;
}
