#ifndef DHT11_HPP
#define DHT11_HPP

#include <hwlib.hpp>


/// @file

/// \brief
/// Default DHT11 class
/// \details
/// Class to control the DHT11 temperature sensor
class dht11{
private:
	hwlib::pin_in_out & data_pin;

	uint8_t bits[5] = { 0 };

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
	/// Start communication between MCU and DHT11
	/// \details
	/// When the communication between MCU and DHT11 begins the programme of the
	/// MCU will set data single-bus voltage level from high to low and this
	/// process must take at least 18 ms to ensure DHTs detection of MCUs signal
	/// then MCU will pull up voltage and wait 20-40us for DHTs response
	void data_pin_start();


	/// \brief
	/// Checking DHT11s low-voltage-level response signal
	/// \details
	/// Once DHT detects the start signal it will send out a low-voltage-level
	/// response signal which lasts 80us then the programme of DHT sets data
	/// single-bus voltage level from low to high and keeps it for 80us for
	/// DHTs preparation for sending data
	void acknowledge_signal();


	/// \brief
	/// Reading 40bit value from DHT11 and storing it
	/// \details
	/// After DHT11s low-voltage-level response signal is send the DHT11 will
	/// send 40bits of data to the MCU
	/// When DHT11 is sending data to the MCU every bit of data begins with
	/// the 50us low-voltage-level and the length of the following
	/// high-voltage-level signal determines whether the data bit is "0" or "1"
	void reading_40bits();

public:
	/// \brief
	/// Default contstructor of the DHT11 class
	/// \details
	/// @param Data_pin
	/// Digital pin that is used for controlling the sensor (in/output)
	dht11(hwlib::pin_in_out & data_pin): data_pin(data_pin) {};


	/// \brief
	/// Combining al protected methods for a more user friendly method
	/// \details
	/// This method combines data_pin_start() acknowledge_signal()
	/// reading_40bits() in a more user friendly method
	void read_sensor();


	/// \brief
	/// Taking bits value and returning it as a integer humidity value
	/// \details
	/// @returns
	/// humidity in percent value
	int get_humidity();


	/// \brief
	/// Taking bits value and returning it as a integer temperature value
	/// \details
	/// @returns
	/// Temperature in degrees celsius
	int get_temperature();

};


#endif //DHT11_HPP
