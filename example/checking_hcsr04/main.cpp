#include <hwlib.hpp>

#include "hcsr04.hpp"


int main() {
	auto trigger_pin = hwlib::target::pin_out ( hwlib::target::pins::d4 );
	auto echo_pin    = hwlib::target::pin_in  ( hwlib::target::pins::d5 );

	hcsr04 sensor_test( trigger_pin, echo_pin );

	int distance_cm   = -1;
	int distance_inch = -1;

	for( ;; ) {
		hwlib::wait_ms( 2000 );

		distance_cm   = sensor_test.distance_cm   ();
		distance_inch = sensor_test.distance_inch ();

		hwlib::cout << "AFSTAND: " << distance_cm   << " CM"   << "\n";
		hwlib::cout << "AFSTAND: " << distance_inch << " INCH" << "\n";

	}

}
