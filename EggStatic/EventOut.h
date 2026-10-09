#pragma once

#include "Event.h"

const std::string OUT_EVENT = "df::out";

class EventOut : public Event
{
public:
    EventOut();
};