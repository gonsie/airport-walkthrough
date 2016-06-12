#include "model.h"

// default value
int g_total_airplanes = 1;

void airplane_init(airplane_state *s, tw_lp *lp) {
    s->status = GROUND;
    s->current_airport = tw_rand_integer(lp->rng, 0, g_total_airports);
    s->destination_airport = tw_rand_integer(lp->rng, 0, g_total_airports);
}

void airplane_pre_run(airplane_state *s, tw_lp *lp) {
}

void airplane_event(airplane_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {

}

void airplane_reverse(airplane_state *s, tw_bf *bf, message *in_msg, tw_lp *lp) {

}

void airplane_final(airplane_state *s, tw_lp *lp) {

}

