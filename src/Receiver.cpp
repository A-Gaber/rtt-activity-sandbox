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
	if (!portsArePrepared)
	{
		preparePorts();
	}
	return true;
}

bool Receiver::startHook()
{
	startTime = this->getSimulationTime();
	RTT::log(RTT::Warning) << this->getName() << "started" << RTT::endlog();
	return true;
}

void Receiver::updateHook()
{
	startUpdateTime = getSimulationTime();
	RTT::log(RTT::Warning) << this->getName() << "update start" << RTT::endlog();

	in_flow = in_port.read(in_var);
	if (in_flow == RTT::NoData)
	{
		RTT::log(RTT::Warning) << this->getName() << "    1 NOO > " << RTT::endlog();
	}
	else if (in_flow == RTT::OldData)
	{
		RTT::log(RTT::Warning) << this->getName() << "    1 OLD > " << in_var << RTT::endlog();
	}
	else if (in_flow == RTT::NewData)
	{
		RTT::log(RTT::Warning) << this->getName() << "    1 NEW > " << in_var << RTT::endlog();
	}

	while ((getSimulationTime() - startUpdateTime) < 0.7)
	{
		// RTT::log(RTT::Warning) << this->getName() << " 0.3 >= " << (getSimulationTime() - startUpdateTime) << RTT::endlog();
	}

	in_flow = in_port.read(in_var);
	if (in_flow == RTT::NoData)
	{
		RTT::log(RTT::Warning) << this->getName() << "    2 NOO > " << RTT::endlog();
	}
	else if (in_flow == RTT::OldData)
	{
		RTT::log(RTT::Warning) << this->getName() << "    2 OLD > " << in_var << RTT::endlog();
	}
	else if (in_flow == RTT::NewData)
	{
		RTT::log(RTT::Warning) << this->getName() << "    2 NEW > " << in_var << RTT::endlog();
	}

	RTT::log(RTT::Warning) << this->getName() << "update end" << RTT::endlog();
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
	// Adding a callbaqck here does not make much sense, since user callbacks are only executed in the updateHook,
	// and since we do not consider the input as valid for triggering, the update will never be called, also because we are already in the updateHook()!
	ports()->addEventPort(in_port);
	in_flow = RTT::NoData;

	portsArePrepared = true;
}

double Receiver::getSimulationTime()
{
	return 1E-9 * RTT::os::TimeService::ticks2nsecs(
					  RTT::os::TimeService::Instance()->getTicks());
}

// ACCORDING TO THIS, A TRIGGER ONLY HAPPENS IF dataOnPortHook returns true
//
// void TaskContext::dataOnPort(PortInterface *port)
// {
// 	if (this->dataOnPortHook(port))
// 	{
// 		portqueue->enqueue(port);
// 		this->getActivity()->trigger();
// 	}
// }
bool Receiver::dataOnPortHook(RTT::base::PortInterface *port)
{
	//ONLY THE EVENT PORTS...
	RTT::log(RTT::Warning) << this->getName() << " RECEIVED DATA ON PORT " << port->getName() << RTT::endlog();
	return false; // Like this, we are going to ignore the input and do not trigger execution!
}

// This macro, as you can see, creates the component. Every component should have this!
ORO_LIST_COMPONENT_TYPE(Receiver)
