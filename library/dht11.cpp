#include "dht11.hpp"

/******************************************************************************/

void dht11::wait_us( const int & time ) {
	hwlib::wait_us( time );

}


void dht11::wait_ms( const int & time ) {
	hwlib::wait_ms( time );

}

/******************************************************************************/

void dht11::data_pin_start() {
	data_pin.direction_set_output();
	data_pin.direction_flush();

	data_pin.write(0);
	data_pin.flush();

	wait_ms(18);

	data_pin.write(1);
	data_pin.flush();

	data_pin.direction_set_input();
	data_pin.direction_flush();

	wait_us(40);

}


void dht11::acknowledge_signal() {
	while( data_pin.read() == 0 ) {};
	while( data_pin.read() == 1 ) {};
	while( data_pin.read() == 0 ) {};

}


void dht11::reading_40bits() {
	int bit_counter = 0;

	for( int byte_index = 0; byte_index < 5; byte_index++ ) {
		for( int byte = 0; byte < 7; byte++ ) {
			wait_us(50);

			if( data_pin.read() == 0 ) {
				bit_counter <<= 1;

			}

			else {
				bit_counter++;
				bit_counter <<= 1;

				while( data_pin.read() == 1 ) {};

			}

			while( data_pin.read() == 0 ) {};

		}

		wait_us(50);

		if( data_pin.read() == 1 ) {
			bit_counter += 1;
			while( data_pin.read() == 1 ) {};

		}

		while( data_pin.read() == 0 ) {};

		bits[byte_index] = bit_counter;

	}

}

/******************************************************************************/

void dht11::read_sensor() {
	data_pin_start();

	acknowledge_signal();

	reading_40bits();

}


int dht11::get_humidity() {
	int humidity = bits[0];

	return humidity;

}


int dht11::get_temperature() {
	int temperature = bits[2];

	return temperature;

}
