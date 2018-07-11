/** 
 * Author: Dennis Leroy Wigand
 * Date:   10 Jul 2018
 *
 */

#pragma once

#include <rtt/Port.hpp>
#include <rtt/TaskContext.hpp>
#include <string>

class Sender : public RTT::TaskContext
{
public:
  Sender(std::string const &name);

  bool configureHook();
  bool startHook();
  void updateHook();
  void stopHook();
  void cleanupHook();

  double getSimulationTime();
  void preparePorts();
  bool portsArePrepared;

private:
  RTT::OutputPort<double> out_Sender_port;

  double out_Sender_var;

  double startTime;
  double startUpdateTime;
};
