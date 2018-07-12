/** 
 * Author: Dennis Leroy Wigand
 * Date:   10 Jul 2018
 *
 */

#include "Sender.hpp"
#include <rtt/Component.hpp> // needed for the macro at the end of this file

#include <stdio.h>

Sender::Sender(std::string const &name) : RTT::TaskContext(name), portsArePrepared(false), out_Sender_var(0)
{
}

bool Sender::configureHook()
{
	counter = 0;
	if (!portsArePrepared)
	{
		preparePorts();
	}
	return true;
}

bool Sender::startHook()
{
	startTime = this->getSimulationTime();
	RTT::log(RTT::Warning) << this->getName() << "started" << RTT::endlog();
	return true;
}

void Sender::updateHook()
{
	// startUpdateTime = getSimulationTime();
	RTT::log(RTT::Warning)
		<< this->getName() << "update start" << RTT::endlog();
	// while ((getSimulationTime() - startUpdateTime) < 0.5)
	// {
	// 	// RTT::log(RTT::Warning) << this->getName() << " 0.3 >= " << (getSimulationTime() - startUpdateTime) << RTT::endlog();
	// }
	// out_Sender_var = getSimulationTime();
	counter++;
	if (counter >= 10)
	{
		counter = 0;
	}
	out_Sender_var = counter;
	out_Sender_port.write(out_Sender_var);
	RTT::log(RTT::Warning) << this->getName() << "   SEND > " << out_Sender_var << RTT::endlog();
	RTT::log(RTT::Warning) << this->getName() << "update end" << RTT::endlog();
}

void Sender::stopHook()
{
}

void Sender::cleanupHook()
{
}

void Sender::preparePorts()
{
	out_Sender_port.setName("out_port");
	out_Sender_port.doc("Output port Sender");
	ports()->addPort(out_Sender_port);

	out_Sender_port.setDataSample(out_Sender_var);

	portsArePrepared = true;
}

double Sender::getSimulationTime()
{
	return 1E-9 * RTT::os::TimeService::ticks2nsecs(
					  RTT::os::TimeService::Instance()->getTicks());
}

// This macro, as you can see, creates the component. Every component should have this!
ORO_LIST_COMPONENT_TYPE(Sender)
