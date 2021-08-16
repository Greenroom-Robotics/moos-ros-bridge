#include <chrono>
#include <functional>
#include <memory>
#include <string>


// ROS TYPES
// Note: Add includes here to handle new data type conversion
#include "std_msgs/msg/int32.h"
#include "std_msgs/msg/int64.h"
#include "std_msgs/msg/float32.h"
#include "std_msgs/msg/float64.h"
#include "std_msgs/msg/string.h"

// MOOS Includes
#include <MOOS/libMOOS/App/MOOSApp.h>
#include <moos-ros-bridge/MOOSNode.h>
#include <moos-ros-bridge/MsgContainer.h>

// BOOST Includes
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

// RapidXML Parser
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "moos-ros-bridge/MsgContainer.h"

#define FAIL 1
#define SUCCESS 0

using namespace std::chrono_literals;

class ROSNode : public rclcpp::Node
{
  public:
    ROSNode(std::string node_name)
    : Node(node_name)
    {}

    int CreateROSPubSub(rapidxml::xml_node<> *node, vector<IMsgContainer> *pubVec, vector<IMsgContainer> *subVec);


  private:
   
};