/** 
 * Author: Dennis Leroy Wigand
 * Date:   10 Jul 2018
 *
 */

#include "Receiver.hpp"
#include <rtt/Component.hpp> // needed for the macro at the end of this file

#include <stdio.h>

Receiver::Receiver(std::string const &name) : RTT::TaskContext(name), portsArePrepared(false), in_var(-1)
{
	startTime = 0.0;
}

bool Receiver::configureHook()
{

	return true;
}

bool Receiver::startHook()
{
	startTime = this->getSimulationTime();
	return true;
}

void Receiver::updateHook()
{
	in_flow = in_port.read(in_var);
}

void Receiver::stopHook()
{
}

void Receiver::cleanupHook()
{
}

void Receiver::preparePorts()
{
	in_port.setName("in_port");
	in_port.doc("Input port");
	ports()->addPort(in_port);
	in_flow = RTT::NoData;

	portsArePrepared = true;
}

double Receiver::getSimulationTime()
{
	return 1E-9 * RTT::os::TimeService::ticks2nsecs(
					  RTT::os::TimeService::Instance()->getTicks());
}

// This macro, as you can see, creates the component. Every component should have this!
ORO_LIST_COMPONENT_TYPE(Receiver)
