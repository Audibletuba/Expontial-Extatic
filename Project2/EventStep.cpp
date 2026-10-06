#include "EventStep.h"

// Create default step event
EventStep::EventStep()
{
    setType(STEP_EVENT);
    m_step_count = 0;
}

// Create step event with count
EventStep::EventStep(int init_step_count)
{
    setType(STEP_EVENT);
    m_step_count = init_step_count;
}

// Set step count
void EventStep::setStepCount(int new_step_count)
{
    m_step_count = new_step_count;
}

// Get step count
int EventStep::getStepCount() const
{
    return m_step_count;
}
