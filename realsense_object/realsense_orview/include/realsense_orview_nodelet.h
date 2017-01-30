/******************************************************************************
ClassifyImage	INTEL CORPORATION PROPRIETARY INFORMATION
	This software is supplied under the terms of a license agreement or nondisclosure
	agreement with Intel Corporation and may not be copied or disclosed except in
	accordance with the terms of that agreement
	Copyright(c) 2011-2015 Intel Corporation. All Rights Reserved.
*******************************************************************************/

#pragma once
# ifndef RS_ORVIEW_NODELET
# define RS_ORVIEW_NODELET

///////////////////////////////////////////////
/// Dependencies
///////////////////////////////////////////////

#include <nodelet/nodelet.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

#include "../../utils/GUI_utils.h"

#include <message_filters/time_synchronizer.h>

//typedef message_filters::TimeSynchronizer<sensor_msgs::Image, realsense_msgs::ObjectsInBoxes> trackingSynchronizer;
//typedef message_filters::TimeSynchronizer<sensor_msgs::Image, sie_common::RecogRsObjectTracker> sonySynchronizer;

namespace realsense
{
	///////////////////////////////////////////////
	///	CTracking - 
	///////////////////////////////////////////////
	class COrView
	{
	public :
		//===================================
		//	Interface
		//===================================
	  	void getParams(ros::NodeHandle& nh);
		void getParams(const std::vector<std::string> & argv);
		void init(ros::NodeHandle& nh);
  
		COrView();
		virtual ~COrView();

	private:
		//===================================
		//	Member Functions
		//===================================

		int initialize();
		int unInitialize();
		//Static member functions:
		void localizedTrackedObjectsCallback(const sensor_msgs::ImageConstPtr& color,const realsense_msgs::ObjectsInBoxes::ConstPtr& msg);
		
		//===================================
		//	Member Variables
		//===================================

		std::unique_ptr<message_filters::Subscriber<sensor_msgs::Image>>			mColorSubscriber;

		std::unique_ptr<message_filters::Subscriber<realsense_msgs::ObjectsInBoxes>> 		mTrackingSubscriber;
		
		std::unique_ptr<message_filters::TimeSynchronizer<sensor_msgs::Image, realsense_msgs::ObjectsInBoxes>> mTimeSynchronizer;
		
		ros::Publisher m_UI_pub;
		ros::NodeHandle m_nh;
		
		GUI_utils gui;
		
		cv::Mat m_imageColor;

	};
	
#ifdef RUN_AS_NODELET
	///////////////////////////////////////////////
	///	COrViewNodelet 
	///////////////////////////////////////////////
	class COrViewNodelet : public nodelet::Nodelet
	{
	public:
		//===================================
		//	Interface
		//===================================
		virtual void onInit();

		~COrViewNodelet();

	private:
		//===================================
		//	Member Functions
		//===================================

		//===================================
		//	Member Variables
		//===================================

		COrView m_ViewNodelet;

	};
#endif
	
};

#endif //RS_ORVIEW_NODELET 
