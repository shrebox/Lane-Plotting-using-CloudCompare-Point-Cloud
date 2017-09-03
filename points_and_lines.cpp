#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <cmath>
#include <fstream>

using namespace std;

int main( int argc, char** argv )
{
  float x1 = 2;
  float y1 = 7;

  float x2 = 3;
  float y2 = 9;

  float slope, intercept;
  //float x1, y1, x2, y2;
  float dx, dy;

  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  ros::Rate r(30);

  float f = 0.0;
  while (ros::ok())
  {

    visualization_msgs::Marker points, line_strip, line_list;
    points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "/my_frame";
    points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
    points.ns = line_strip.ns = line_list.ns = "points_and_lines";
    points.action = line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 0;
    points.pose.orientation.y = line_strip.pose.orientation.y = line_list.pose.orientation.y = 0;
    points.pose.orientation.z = line_strip.pose.orientation.z = line_list.pose.orientation.z = 0;
    points.pose.orientation.x = line_strip.pose.orientation.x = line_list.pose.orientation.x = 0;




    //points.id = 0;
    line_strip.id = 1;
    line_list.id = 2;



    //points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_list.type = visualization_msgs::Marker::LINE_LIST;



    // POINTS markers use x and y scale for width/height respectively
    //points.scale.x = 0.2;
    //points.scale.y = 0.2;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    line_strip.scale.x = 0.1;
    line_list.scale.x = 0.1;



    // Points are green
    //points.color.g = 1.0f;
    //points.color.a = 1.0;

    // Line strip is blue
    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;

    // Line list is red
    line_list.color.r = 1.0;
    line_list.color.a = 1.0;

    std::ifstream infile("lanes_000000.asc");
   	std::string line;
   	std::vector< std::vector<int> > all_integers;
   	while ( getline( std::infile, line ) ) 
   	{
    	  std::istringstream is( line );
    	  all_integers.push_back( std::vector<int>( std::istream_iterator<int>(is),std::istream_iterator<int>() ) );
   	}

   	for(int i=0;i<all_integers.size();i++)
   	{
   		cout << all_integers[i] << " ";
   	}

   	cout << endl;


    dx = x2 - x1;
    dy = y2 - y1;
 
    slope = dy / dx;

    intercept = y1 - slope * x1;  

    int flag = 0;

    // Create the vertices for the points and lines
    for (uint32_t i = 0; i < 10; ++i)
    {
      //float y = 5 * sin(f + i / 100.0f * 2 * M_PI);
      //float z = 5 * cos(f + i / 100.0f * 2 * M_PI);
      float y = slope*i + intercept;

      geometry_msgs::Point p;
      p.x = (int32_t)i ;
      p.y = y;
      //p.z = z;

      cout << (int32_t)i << " " << y << " " << slope << " " << intercept << endl;  

      //points.points.push_back(p);
      //line_strip.points.push_back(p);

      // The line list needs two points for each line
      line_list.points.push_back(p);
      //p.z += 1.0;

      if(i>0 && i<9)
      {
        line_list.points.push_back(p);
      }

      // p.y+=1.0;
      // line_list.points.push_back(p);

      flag=1;

    }

    /*for (uint32_t i = 1; i <= 10; ++i)
    {

      geometry_msgs::Point p;
      p.x = i;
      p.y= i;
      // The line list needs two points for each line
      line_list.points.push_back(p);

     if(i>1 && i<10)
      {
        line_list.points.push_back(p);
      }
      //p.z += 1.0;
      //p.y+=1.0;
      //line_list.points.push_back(p);

      //flag=1;

    }
*/


    //marker_pub.publish(points);
    //marker_pub.publish(line_strip);
    marker_pub.publish(line_list);

    r.sleep();

    f += 0.04;
  }
}