#include "model.h"

#define RUNWAY_TIME 1
#define FLIGHT_TIME 10
#define GROUND_TIME 5

// default value
int g_total_airplanes = 1;

void airplane_init(airplane_state *s, tw_lp *lp) {
    s->status = GROUND;
    s->current_airport = tw_rand_integer(lp->rng, 0, g_total_airports);
    s->destination_airport = tw_rand_integer(lp->rng, 0, g_total_airports);
}

void airplane_pre_run(airplane_state *s, tw_lp *lp) {
    // Request runway for takeoff from current airport
    double jitter = (tw_rand_unif(lp->rng)) * GROUND_TIME;
    tw_event *init_event = tw_event_new(s->current_airport, jitter, lp);
    message *msg = tw_event_data(init_event);
    msg->type = RUNWAY_REQUEST;
    tw_event_send(init_event);
}

void airplane_event(airplane_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
    if (in_msg->type != RUNWAY_GRANT) {
        tw_error(TW_LOC, "Airplane unrecognized message type\n");
    }

    if (s->status == GROUND) {
        // free runway after takeoff
        tw_event *e = tw_event_new(s->current_airport, RUNWAY_TIME, lp);
        message *msg = tw_event_data(e);
        msg->type = RUNWAY_FREE;
        tw_event_send(e);

        // update airplane status
        s->status = FLIGHT;

        // request runway for landing at destination
        tw_event *e2 = tw_event_new(s->destination_airport, FLIGHT_TIME, lp);
        message *msg2 = tw_event_data(e2);
        msg2->type = RUNWAY_REQUEST;
        tw_event_send(e2);
    } else if (s->status == FLIGHT) {
        // free runway after landing
        tw_event *e = tw_event_new(s->destination_airport, RUNWAY_TIME, lp);
        message *msg = tw_event_data(e);
        msg->type = RUNWAY_FREE;
        tw_event_send(e);

        // update airplane status
        s->status = GROUND;
        s->current_airport = s->destination_airport;
        s->destination_airport = tw_rand_integer(lp->rng, 0, g_total_airports);

        // request runway for takeoff
        tw_event *e2 = tw_event_new(s->current_airport, GROUND_TIME, lp);
        message *msg2 = tw_event_data(e2);
        msg2->type = RUNWAY_REQUEST;
        tw_event_send(e2);
    }
}

void airplane_reverse(airplane_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {
    return;
}

void airplane_final(airplane_state *s, tw_lp *lp) {

}

