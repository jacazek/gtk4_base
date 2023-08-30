//
// Created by jacob on 7/12/23.
//

#include "state_machine.h"

state transition(state currentState, state_machine_event_t event) {
    // how do we know we are actually transitioning?
    // should we instead register a callback to be invoked when transition actually occurs
    if (NULL != currentState.exitAction)
        currentState.exitAction(
                (action_arguments_t) {.currentState = currentState, .event = event, .actionData = currentState.exitData});
    state newState = currentState.handleEvent(event, currentState);
    if (NULL != newState.entryAction)
        newState.entryAction(
                (action_arguments_t) {.currentState = newState, .event = event, .actionData = newState.entryData});
    return newState;
}

bool eventTypeMatches(state_machine_event_t eventInstance, const char *eventType) {
    return !strcmp(eventInstance.type, eventType);
}
