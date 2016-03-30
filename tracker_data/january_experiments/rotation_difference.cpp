#include <iostream>
#include <fstream>
#include <Eigen/Geometry>
#include <vector>

// 1: Hand
// 3: Bottle
// 4: Bowl

int main( int argc, char* argv[] ) {

  // 1. Read file
  char* name = argv[1];

  // 2. Read
  std::ifstream input( name, std::ifstream::in );

  // 2. Calculate the rotation incremental difference
  int n; double x, y, z, qw, qx, qy, qz;
  int i = 0;
  int N = 3; // Number of sensor readings
  std::vector<Eigen::Vector3d> ps[N];
  std::vector<Eigen::Quaterniond> qs[N];

  while( !input.eof() ) {
    input >> n >> x >> y >> z >> qw >> qx >> qy >> qz;
    if( input.peek() == EOF ) {break; }
    printf("Line [%d] n: %d p: %f %f %f r: %f %f %f %f \n", i, n, x, y, z, qw, qx, qy, qz);
    ps[n].push_back( Eigen::Vector3d(x,y,z) );
    qs[n].push_back( Eigen::Quaterniond( qw, qx, qy, qz ) );    
    i++;
  }

  input.close();

  // Get rotation from object from step to step
  Eigen::Quaterniond q;
  double ang;
  for( int i = 1; i < qs[1].size(); ++i ) {
    ang = qs[1][i-1].angularDistance( qs[1][i] );
    printf("Diff [%d] %f \n", i, ang);
  }


  return 0;
}
