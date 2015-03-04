#include "dev/rlink.h"
#include "dev/eggsensor.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include "robot_delay.h"

int main() {
	RLink r;
	std::cout << "constructed" << std::endl;
	r.initialise();
	std::cout << "initialised" << std::endl;

	EggSensor es(r, port::P1);

	while(1){
		auto reading = es.read();
		std::cout << reading << std::endl;
		delay(250);
	}
}