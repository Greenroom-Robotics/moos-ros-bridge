#include "moos-ros-bridge/ROSNode.h"


int ROSNode::CreateROSPubSub(rapidxml::xml_node<> *node, vector<IMsgContainer> *pubVec, vector<IMsgContainer> *subVec)
{
    // MOOS Publishers to ROS Subscribers
    if(strcmp(node->first_node("direction")->value(),"toROS") == SUCCESS)
    {
        RCLCPP_INFO(this->get_logger(), "Value of node '%s'", node->first_node("direction")->value());

        if(strcmp(node->first_node("rostype")->value(),"std_msgs/Int32") == SUCCESS)
        {
            RCLCPP_INFO(this->get_logger(), "STD MSG BABY");
        }
    }
    else if(strcmp(node->first_node("direction")->value(),"toMOOS") == SUCCESS)
    {
        if(strcmp(node->first_node("rostype")->value(),"std_msgs/Int32") == 0)
        {
            RCLCPP_INFO(this->get_logger(), "STD MSG BABY");
            auto msg_container = ContainerBase<std_msgs::msg::Int32>(
                this->create_subscription,
                node->first_node("moosname")->value(),
                node->first_node("rosname")->value()
            )
            subVec->push_back(msg_container);
            // ContainerBase(node->first_node("rosname")->value(),
            // 1000,this->callBack<std_msgs::Int32,std_msgs::Int32ConstPtr>,
            // node->first_node("moosname")->value(),
            // node->first_node("rosname")->value()));
        }
        RCLCPP_INFO(this->get_logger(), "Value of node '%s'", node->first_node("direction")->value());
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "ERROR PARSING XML CONFIG FILE\n");
        return FAIL;
    }

}