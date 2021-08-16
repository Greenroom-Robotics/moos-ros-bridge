//* The MOOS ROS Bridge
/**
 * 
 * @file
 *
 * @author Kevin DeMarco <kevin.demarco@gtri.gatech.edu>
 *
 * @version 1.0
 *
 * @date May 25th, 2012
 * 
 * @section LICENSE
 * 
 * Georgia Tech Research Institute (GTRI)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The MOOS ROS Bridge allows for communication between a 
 * MOOS Database and a ROS Core.  
 */

#ifndef _MSG_CONTAINER_H_ 
#define _MSG_CONTAINER_H_

#include "rclcpp/rclcpp.hpp"
#include <string.h>

using std::placeholders::_1;
using namespace std;

class IMsgContainer
{
	public:
		string moosName;
		string rosName;
		string moosType;
		string rosType;


		template <class T>
		void callback(T msg){}

};

template<class MessageT>
class ContainerBase : public IMsgContainer
{
public:
	// from MOOS to ROS
	ContainerBase(
		rclcpp::Node::SharedPtr node,
		string new_moosName, 
		string new_rosName, 
		string new_moosType, 
		string new_rosType
		)
	{
		pub = node->create_publisher<MessageT>(
			new_rosName,
			10
		);

	}

	// from ROS to MOOS
	ContainerBase(
		rclcpp::Subscription<MessageT>::SharedPtr (*create_sub)(std::string),
		// rclcpp::Node::SharedPtr node, 
		string new_moosName, 
		string new_rosName
		)
	{
		moosName = new_moosName;
		rosName  = new_rosName;
		sub = create_sub("Nalks");
		// sub = node->create_subscription<MessageT>(
		// 	rosName,
		// 	10,
		// 	this->callback<MessageT>
		// );
	}

	typename rclcpp::Publisher<MessageT>::SharedPtr pub;
	typename rclcpp::Subscription<MessageT>::SharedPtr sub;

	// string moosName;
	// string rosName;
	// string moosType;
	// string rosType;

};

#endif
