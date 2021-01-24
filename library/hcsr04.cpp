#include "hcsr04.hpp"

/******************************************************************************/

void hcsr04::wait_us( const int & time ) {
	hwlib::wait_us( time );

}


void hcsr04::wait_ms( const int & time ) {
	hwlib::wait_ms( time );

}

/******************************************************************************/

void hcsr04::trigger_start() {
	trigger_pin.write( 0 );
	trigger_pin.flush();

	wait_us( 2 );

	trigger_pin.write( 1 );
	trigger_pin.flush();

	wait_us( 10 );

	trigger_pin.write( 0 );
	trigger_pin.flush();

}


void hcsr04::echo_time() {
	int time_begin = 0;
	int time_end   = 0;

	while( echo_pin.read() == false ) {}

	time_begin = hwlib::now_us();

	while( echo_pin.read() == true  ) {}

	time_end   = hwlib::now_us();

	time_total = time_end - time_begin;

}

/******************************************************************************/

int hcsr04::distance_cm() {
	trigger_start();

	echo_time();

	int distance_cm = time_total / 58;

	if ( distance_cm < 2 || distance_cm > 400 ) {
		return -1;

	}

	else {
		return distance_cm;

	}

}


int hcsr04::distance_inch() {
	trigger_start();

	echo_time();

	int distance_inch = time_total / 148;

	if ( distance_inch < 1 || distance_inch > 155 ) {
		return -1;

	}

	else {
		return distance_inch;

	}

}
