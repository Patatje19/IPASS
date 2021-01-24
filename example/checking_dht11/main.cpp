#include <hwlib.hpp>

#include "dht11.hpp"


int main() {
	auto data_pin = hwlib::target::pin_in_out ( hwlib::target::pins::d7 );

	dht11 sensor_test( data_pin );

	int humidity    = -1;
	int temperature = -1;

	for( ;; ) {
		hwlib::wait_ms( 2000 );

		sensor_test.read_sensor();

		humidity    = sensor_test.get_humidity    ();
		temperature = sensor_test.get_temperature ();

		hwlib::cout << "HUMDITY: "     << humidity    << " PERCENT" << "\n";
		hwlib::cout << "TEMPERATURE: " << temperature << " DEGREES" << "\n";

	}

}
