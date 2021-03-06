/***********************************************************************/
/*                             Target.cpp                              */
/***********************************************************************/
/* -VERSION: ROS_Ubuntu 14.04                                          */
/* -AUTHOR:  GUILLAUME Sylvain                                         */
/* -LAST_MODIFICATION: 12/2017                                         */
/***********************************************************************/
# include "Target.hpp"
# include <math.h>
# include "Color.hpp"


//Constructor
	Target::Target(int id,int type, vector<float> pos, vector<float> orien)
	{
		id_ =id;
		type_=type;
		position_=pos;
		orientation_ = orien;
		switch (type) {
			case 0: color_=color_blue(); break;
			case 1: color_=color_magenta(); break;
			case 2: color_=color_red(); break;
			case 3: color_=color_orange(); break;
			default : color_=color_black(); break;
		}
	}

//Create_MSG_Marker
//this fonction creates a visualization_msg  of the target
	visualization_msgs::Marker Target::create_MSG_Marker ()
	{
		visualization_msgs::Marker marker;
		marker.header.frame_id = "/map";
		marker.header.stamp = ros::Time::now();
		marker.ns = "Target";
		marker.id = id_;
		marker.type = visualization_msgs::Marker::CUBE;
		marker.action = visualization_msgs::Marker::ADD;
		marker.pose.position.x = position_[0];
		marker.pose.position.y = position_[1];
		marker.pose.position.z = position_[2];
		marker.pose.orientation.x = orientation_[0];
		marker.pose.orientation.y = orientation_[1];
		marker.pose.orientation.z = orientation_[2];
		marker.pose.orientation.w = orientation_[3];
		marker.scale.x = SCALE_X_TARGET;
		marker.scale.y = SCALE_Y_TARGET;
		marker.scale.z = SCALE_Z_TARGET;
		marker.color.a = 1.0; // Don't forget to set the alpha!
		marker.color.r = color_[0];
		marker.color.g = color_[1];
		marker.color.b = color_[2];
		marker.lifetime = ros::Duration();

		return marker;
	}

	// add_son
	// add the id of the son to the sons of this Target
	// id: the id of the son to add
	void Target::add_Son(int id){
		sons_.push_back(id);
	}

	bool Target::remove_Son(int id){
		for(int i=0; i<sons_.size(); ++i){
			if(sons_[i] == id){
				sons_.erase(sons_.begin()+i);
				return true;
			}
		}
		return false;
	}

	// euclidean_Distance
	// Return the euclidean distance between this target and a target given
	// t: the target from wich we want to calculate the distance with the current
	float Target::euclidean_Distance(Target &t){
		vector<float> t_Position = t.get_Position();
		float x_T = t_Position[0];
		float y_T = t_Position[1];
		return (sqrt((x_T-position_[0])*(x_T-position_[0])+(y_T-position_[1])*(y_T-position_[1])));
	}

	// equals
	// Return true if this target is the same as the given Target (same id)
	// t: the Target from wich we want to verify the equality with
	bool Target::equals(Target &t){
		return (t.get_Id() == id_);
	}

	// equals
	// Return true if this target id is the same as the given id
	// id_Target: the id of the Target from wich we want to verify the equality with
	bool Target::equals(int id_Target){
		return (id_Target == id_);
	}

//Getter

	vector<float> Target::get_Position (){return position_;}
	vector<float> Target::get_Orientation (){return orientation_;}
	vector<float> Target::get_Color (){return color_;}
	int Target::get_Id (){return id_;}
	int Target::get_Type(){return type_;}
	vector<int> Target::get_Sons(){return sons_;}

//Setter
	void Target::set_Id_Failure(){id_ = -1;}
	void Target::set_Position (vector<float> pos){position_=pos;}
	void Target::set_Orientation (vector<float> orien){orientation_=orien;}
	void Target::set_Color (vector<float> color){color_=color;}

