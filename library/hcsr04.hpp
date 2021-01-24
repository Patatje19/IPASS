#ifndef HCSR04_HPP
#define HCSR04_HPP

#include <hwlib.hpp>


/// @file

/// \brief
/// Default HC-SR04 class
/// \details
/// Class to control the HC-SR04 distance sensor
class hcsr04 {
private:
	hwlib::pin_out & trigger_pin;
	hwlib::pin_in  & echo_pin;

	int time_total = 0;

protected:
	/// \brief
	/// Let the method pause for a variable time in microseconds
	/// \details
	/// @param Time
	/// The time in microseconds the methods needs to pause
	void wait_us( const int & time );


	/// \brief
	/// Let the method pause for a variable time in miliseconds
	/// \details
	/// @param Time
	/// The time in miliseconds the methods needs to pause
	void wait_ms( const int & time );


	/// \brief
	/// Starts the trigger_pin with a 10 microsecond burst
	/// \details
	/// You only need to supply a short 10 microseconds pulse to the trigger
	/// input to start the ranging, and then the module will send out an 8 cycle
	/// burst of ultrasound at 40 kHz and raise its echo
	void trigger_start();


	/// \brief
	/// Calculate echo_pin puls in microseconds
	/// \details
	/// Measure the length of echo signal, which is equal to the time needed
	/// for sound to go there and back
	void echo_time();

public:
	/// \brief
	/// Default contstructor of the HC-SR04 class
	/// \details
	/// @param Trigger_pin
	/// Digital pin that is used for controlling the sensor (output)
	/// @param Echo_pin
	/// Digital pin that is used to get information from sensor (input)
	hcsr04 ( hwlib::pin_out & trigger_pin, hwlib::pin_in & echo_pin ) :
		trigger_pin( trigger_pin ), echo_pin( echo_pin )
	{};


	/// \brief
	/// Measures distance by sending ultrasonic waves and measuring the time
	/// it takes them to return
	/// \details
	/// Measures the distance in centimeters
	/// @returns
	/// Distance in centimeters,
	/// or negative value if distance is equal to 0 or greater than 400cm
	int distance_cm();


	/// \brief
	/// Measures distance by sending ultrasonic waves and measuring the time
	/// it takes them to return
	/// \details
	/// Measures the distance in inches
	/// @returns
	/// Distance in inches,
	/// or negative value if distance is equal to 0 or greater than 400cm
	int distance_inch();

};


#endif //HCSR04_HPP
