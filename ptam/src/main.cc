// Copyright 2008 Isis Innovation Limited
// This is the main extry point for PTAM
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <exception>

#include <gvars3/instances.h>
#include "ptam/System.h"
#include <ptam/Params.h>

#include <std_msgs/Empty.h>
#include "ros/ros.h"

using namespace std;
using namespace GVars3;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ptam");
  ROS_INFO("starting ptam with node name %s", ros::this_node::getName().c_str());

  cout << "  Welcome to PTAM " << endl;
  cout << "  --------------- " << endl;
  cout << "  Parallel tracking and mapping for Small AR workspaces" << endl;
  cout << "  Copyright (C) Isis Innovation Limited 2008 " << endl;
  cout << endl;

  ros::NodeHandle nh_;
  ros::Publisher pub_planner_reset = nh_.advertise<std_msgs::Empty>("/vslam/started",1);
  
  GUI.StartParserThread(); // Start parsing of the console input
  atexit(GUI.StopParserThread);
  try
  {
    std::cout<<"Gui is "<<(PtamParameters::fixparams().gui ? "on" : "off")<<std::endl; //make the singleton instantiate
   // System *s = new System;
    /*void *s;
    s= (System *) malloc(sizeof(System));
    FILE * pFile;
    pFile = fopen ("PTAM_SAVEFILE.bin", "rb");
    if (pFile!=NULL)
    {
      fread (s,sizeof(System),1,pFile);
      //cout<<r->x<<endl;
    }
    ((System * )s)->Run();
    cout<<"K BYE."<<endl;
    FILE * pFile1;
    pFile1 = fopen ("PTAM_SAVEFILE.bin", "rb");
    
    fwrite (s , sizeof(System), 1, pFile1);
    fclose (pFile);
    fclose (pFile1);*/
    System s;
    pub_planner_reset.publish(std_msgs::Empty());
    s.Run();
  }
catch(exception& e)
  {
    cout.flush();
    cout << endl;
    cout << " PTAM CRASHED Exception was: " << endl;
    cout << e.what() << endl;
    pub_planner_reset.publish(std_msgs::Empty());
  }
}










