#include <iostream>
#include <fstream>
#include <Eigen/Geometry>
#include <vector>

// 1: Hand
// 2: Other hand
// 3: Object?

int main( int argc, char* argv[] ) {

  // 1. Read file
  if( argc < 3 ) { printf("Syntax: ./rotation_diff_liberty FILE INDEX \n"); return 0; }
  char* name = argv[1];
  int num = atoi( argv[2] );

  // 2. Read
  std::ifstream input( name, std::ifstream::in );

  // 2. Calculate the rotation incremental difference
  int n; double x, y, z, qw, qx, qy, qz;
  int i = 0;
  int N = 3; // Number of sensor readings
  std::vector<Eigen::Vector3d> ps[N];
  std::vector<Eigen::Quaterniond> qs[N];

  while( !input.eof() ) {
    input >>  x >> y >> z >> qw >> qx >> qy >> qz >> n;
    if( input.peek() == EOF ) {break; }
    //printf("Line [%d] n: %d p: %f %f %f r: %f %f %f %f \n", i, n, x, y, z, qw, qx, qy, qz);
    ps[n-1].push_back( Eigen::Vector3d(x,y,z) );
    qs[n-1].push_back( Eigen::Quaterniond( qw, qx, qy, qz ) );    
    i++;
  }

  input.close();

  // Get rotation from object from step to step (NOW W.R.T. FIRST)
  Eigen::Quaterniond q;
  double ang; double dist;
  char output_name[100]; sprintf( output_name, "angle_%d.txt", num );
  char output_dist_name[100]; sprintf( output_dist_name, "dist_%d.txt", num );
  std::ofstream output( output_name, std::ofstream::out );
  std::ofstream output_dist( output_dist_name, std::ofstream::out );

  for( int i = 1; i < qs[0].size(); ++i ) {
    ang = qs[0][i-1].angularDistance( qs[0][0] );
    dist = (ps[0][i] - ps[0][0]).norm();
    output << ang*180.0/3.1416 << std::endl;
    output_dist << dist << std::endl;
    printf("Diff [%d] %f \n", i, ang*180.0/3.1416);
  }
  output.close();
  output_dist.close();

  return 0;
}
