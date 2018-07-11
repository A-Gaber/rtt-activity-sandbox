/** 
 * Author: Dennis Leroy Wigand
 * Date:   10 Jul 2018
 *
 */

#pragma once

#include <rtt/Port.hpp>
#include <rtt/TaskContext.hpp>
#include <string>

class Receiver : public RTT::TaskContext
{
public:
  Receiver(std::string const &name);

  bool configureHook();
  bool startHook();
  void updateHook();
  void stopHook();
  void cleanupHook();

  double getSimulationTime();
  void preparePorts();
  bool portsArePrepared;

private:
  RTT::InputPort<double> in_port;

  RTT::FlowStatus in_flow;

  double in_var;

  double startTime;
};
