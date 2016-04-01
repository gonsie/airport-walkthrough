#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <ross.h>

typedef enum {
	FLIGHT,
	RUNWAY,
	GROUND,
} airplane_status;

typedef struct {
	airplane_status status;
	tw_lpid current_airport;
	tw_lpid destination_airport;
} airplane_state;

typedef struct {
	int runway_free_flag;
	tw_lpid * airplanes_landing;
	tw_lpid * airplanes_taking_off;
} airport_state;

typedef enum {
	RUNWAY_REQUEST,
	RUNWAY_GRANT,
	RUNWAY_FREE,
} message_type;

typedef struct {
	message_type type;
} message;

#endif
