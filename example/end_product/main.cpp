#include <hwlib.hpp>

#include "dht11.hpp"
#include "hcsr04.hpp"


int main() {
	// Initialize pins

	auto trigger_pin = hwlib::target::pin_out    ( hwlib::target::pins::d4 );
	auto echo_pin    = hwlib::target::pin_in     ( hwlib::target::pins::d5 );

	auto data_pin    = hwlib::target::pin_in_out ( hwlib::target::pins::d7 );

	auto buzzer      = hwlib::target::pin_out    ( hwlib::target::pins::d8 );

	auto green_led   = hwlib::target::pin_out    ( hwlib::target::pins::d10 );
	auto red_led     = hwlib::target::pin_out    ( hwlib::target::pins::d12 );

	auto scl         = hwlib::target::pin_oc     ( hwlib::target::pins::scl );
	auto sda         = hwlib::target::pin_oc     ( hwlib::target::pins::sda );

	// Initialize display

	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda ( scl, sda );

	auto oled    = hwlib::glcd_oled        ( i2c_bus, 0x3C );

	auto font    = hwlib::font_default_8x8 ();
	auto display = hwlib::terminal_from    ( oled, font );

	// Create sensor objects

	hcsr04 distance_sensor   ( trigger_pin, echo_pin );

	dht11 temperature_sensor ( data_pin );

	int distance_cm   = -1;
	int distance_inch = -1;

	int humidity      = -1;
	int temperature   = -1;

	buzzer.write( 0 ); green_led.write( 1 ); red_led.write( 0 );
	buzzer.flush(); green_led.flush(); red_led.flush();

	for( ;; ) {
		hwlib::wait_ms( 2000 );

		// Store sensor values

		distance_cm   = distance_sensor.distance_cm   ();
		distance_inch = distance_sensor.distance_inch ();

		temperature_sensor.read_sensor();

		humidity      = temperature_sensor.get_humidity    ();
		temperature   = temperature_sensor.get_temperature ();

		// Print sensor values

		display
			<< "\f" << "HC-SR04:"
			<< "\n" << "DIST: " << distance_cm   << " CM"
			<< "\n" << "DIST: " << distance_inch << " INCH"
			<< hwlib::flush;

		hwlib::wait_ms( 5000 );

		display
			<< "\f" << hwlib::flush;

		hwlib::wait_ms( 1000 );

		display
			<< "\f" << "DHT11:"
			<< "\n" << "HUMI: " << humidity    << " %"
			<< "\n" << "TEMP: " << temperature << " *C"
			<< hwlib::flush;

		hwlib::wait_ms( 5000 );

		display 
			<< "\f" << hwlib::flush;

		hwlib::wait_ms( 1000 );

		// Tamper detection

		if ( distance_cm < 5 ) {
			buzzer.write( 1 ); green_led.write( 0 ); red_led.write( 1 );

			buzzer.flush(); green_led.flush(); red_led.flush();

			hwlib::wait_ms( 1000 );

			buzzer.write( 0 ); buzzer.flush();

		}

		else {
			green_led.write( 1 ); green_led.flush();

		}

	}

}
