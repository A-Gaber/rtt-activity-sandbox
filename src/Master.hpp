/** 
 * Author: Dennis Leroy Wigand
 * Date:   10 Jul 2018
 *
 */

#pragma once

#include <rtt/Port.hpp>
#include <rtt/TaskContext.hpp>
#include <string>

#include <boost/lexical_cast.hpp>

class Master : public RTT::TaskContext
{
  public:
    Master(std::string const &name);

    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

    double getSimulationTime();
    void preparePorts();
    bool portsArePrepared;

  private:
    RTT::InputPort<bool> in_A_port;
    RTT::InputPort<bool> in_B_port;

    RTT::FlowStatus in_A_flow;
    RTT::FlowStatus in_B_flow;

    RTT::OutputPort<bool> out_nAB_port;

    bool in_A_var;
    bool in_B_var;

    bool out_nAB_var;

    double startTime;
};
