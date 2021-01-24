#include <hwlib.hpp>

#include "dht11.hpp"


int main() {
	auto data_pin = hwlib::target::pin_in_out ( hwlib::target::pins::d7 );

	dht11 sensor_test( data_pin );

	int humidity    = -1;
	int temperature = -1;

	// Checking if DHT11 functions in normal conditions
	for( ;; ) {
		hwlib::wait_ms( 2000 );

		sensor_test.read_sensor();

		humidity    = sensor_test.get_humidity    ();
		temperature = sensor_test.get_temperature ();

		if ( humidity < 20 || humidity > 90 ) {
			hwlib::cout << "TEST FAILED" << "\n";

		}

		else {
			hwlib::cout << "TEST SUCCESFULL" << "\n";

		}

		if ( temperature < 1 || temperature > 50 ) {
			hwlib::cout << "TEST FAILED" << "\n";

		}

		else {
			hwlib::cout << "TEST SUCCESFULL" << "\n";

		}

	}

}
