#ifndef __SCAN_GET_H
#define __SCAN_GET_H
#include <iostream>
#include <stdlib.h>
#include <string.h>

 struct scan_data
{
  // std::string  frame_id;
    char frame_id[10];
    float  angle_min;       
    float angle_max;        
    float angle_increment;  
    float time_increment;                                                  
    float scan_time;       
    float range_min;      
    float range_max; 
    float ranges[897];
    float intensities[897];
};     
 
 struct scan_data scan_data_buf;



 //  scan_data scan_data_buf={"hokuyo",123.0,345.897};


#endif
