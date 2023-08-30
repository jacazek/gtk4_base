//
// Created by jacob on 7/12/23.
//

#ifndef STATE_MACHINE_STATE_MACHINE_H
#define STATE_MACHINE_STATE_MACHINE_H
#include <stdlib.h>
#include <string.h>

typedef struct state_machine_event {
    const char *type;
    void *payload;
} state_machine_event_t;

bool eventTypeMatches(state_machine_event_t eventInstance, const char *eventType);

struct state_t;


/**
 * Prototype for functions what handle events
 * @param event {char*} The event to handle
 * @param currentState {state_t} The current state
 * @returns {state_t} A new state if event could be handled, otherwise current state
 */
typedef struct state_t (*eventReducer)(state_machine_event_t event, struct state_t);

struct action_arguments;

typedef void (*entryAction)(struct action_arguments);

typedef void (*exitAction)(struct action_arguments);

typedef struct state_t {
    const char *name; // all states have a name... why?  probably don't need this
    // each state can handle events. Each state
    // defines its own event handler function
    entryAction entryAction;
    void *entryData;
    eventReducer handleEvent;
    void *exitData;
    exitAction exitAction;
    /**
     * Could make derived state types
     * Each derived type could contain additional information about the states
     * Such as
     * 1. set of objects to be rendered
     * 2. a function to render a set of objects
     * 3. Data to be consumed via rendering or processing
     *
     * Take a game for example:
     * A game runs in a continuous loop. The loop needs to
     * 1. process input
     * 2. update information
     * 3. render output
     *
     * The game consists of different states where processing of input, updating, and rendering output is needed such as:
     * 1. Game menu
     * 2. Game running
     * 3. Gam paused
     *
     *
     */
} state;

typedef struct action_arguments {
    state_machine_event_t event;
    struct state_t currentState;
    void *actionData;
} action_arguments_t;

/**
 * Dispatch the event for the given state.
 * @param currentState {state} The state from which to transition given the event
 * @param event {state_machine_event_t} The event triggering the transition
 * @returns {state} the new state after handling the event for the given state
 */
state transition(state currentState, state_machine_event_t event);

#endif //STATE_MACHINE_STATE_MACHINE_H
