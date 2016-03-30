#include <iostream>
#include <fstream>

#include <aoi/grasp/Grasp.h>
#include <map>
#include <vector>
#include <aoi/GraspitCommUnit.h>
#include <dart/math/Geometry.h>

//std::string allTxt("/home/ana/Research/thesis-data/sq_shapes_data/all_objects_graspfiles.txt");
std::string allTxt("/home/ana/Research/thesis-data/ch3_9_data/all_objects_graspfiles.txt");

struct GEI {
 GraspEvaluation ge;
 std::string name;
};

std::map<std::string, std::vector<GEI> > data;


void readGE( std::string _filename, GraspEvaluation &_ge ) {

   std::ifstream input( _filename.c_str(), std::ifstream::in );

  _ge.g = new Grasp();
  std::vector<size_t> dummy(8);
  _ge.g->setFingerDofs(dummy);
  _ge.g->readGrasp(input);
  input >> _ge.epsilon;
  input >> _ge.volume;
  input >> _ge.skewness;
  input >> _ge.numberSamples;
  input >> _ge.numFailures;
  input >> _ge.numSuccesses;
  input >> _ge.avg_epsilon;
  input >> _ge.avg_volume;

  double v;
  for( int i = 0; i < _ge.numSuccesses; ++i ) {
    input >> v;
    _ge.epsilon_samples.push_back(v); 
  }
//  if( _ge.epsilon < 0.001 ) { std::cout << "Here a bad boy: "<< _filename << std::endl; }
  for( int i = 0; i < _ge.numSuccesses; ++i ) {
    input >> v;
    _ge.volume_samples.push_back(v); 
  }
  input.close();
}

/****/
void readDirectory( std::string _file, std::vector<GEI> &_ges ) {

  // Open file
  std::string grasp_filename;
  std::ifstream input( _file.c_str(), std::ifstream::in );
  while( !input.eof() ) {
   
    // Get file name
    input >> grasp_filename;
    if( input.eof() ) { break; }
    // Get info in a specific ge
    GEI gei;
    readGE( grasp_filename, gei.ge );
    gei.name = grasp_filename;
    _ges.push_back(gei);
  }

  std::cout << "Total number of files per this file: "<< _ges.size() << std::endl;
  input.close();
}

/**
 *
 */
int main( int argc, char* argv[] ) {

  // Read files
  std::ifstream input( allTxt.c_str(), std::ifstream::in );

  // Read
  std::string name, directory;
  int count; double mean_success; double stdev_success;

  while( !input.eof() ) {
    input >> name >> directory;
    if( input.eof() ) { break; }
    std::cout << std::endl;
    std::cout << "Name: "<< name << " directory: "<< directory << std::endl;

    std::vector<GEI> ges;
    readDirectory(directory, ges);
    data[name] = ges; 

    double maxPf = 0; int maxPfIndex = 0;
    double maxAvgEpsilon = 0; int maxAvgIndex;    double maxEpsilon = 0; int maxIndex = 0;

    count = 0; mean_success = 0; stdev_success = 0;

    std::vector<double> probs; double pf;
    for( int i = 0; i < ges.size(); ++i ) {
 
      if( ges[i].ge.epsilon > 0.001 ) { 
         pf = ges[i].ge.numSuccesses/(double)ges[i].ge.numberSamples;
         probs.push_back( pf );
         count++; mean_success += pf; 
       }
       if( ges[i].ge.avg_epsilon > maxAvgEpsilon ) { maxAvgEpsilon = ges[i].ge.avg_epsilon; maxAvgIndex = i; }       
       if( ges[i].ge.epsilon > maxEpsilon ) { maxEpsilon = ges[i].ge.epsilon; maxIndex = i; }
       if( pf > maxPf ) { maxPf = pf; maxPfIndex = i; } 
   }

   // Calculate average success
   mean_success = mean_success / count;
   // Calculate standard deviation
   for( int i = 0; i < count; ++i ) {
     stdev_success += pow( (probs[i] - mean_success), 2 );     
   }   
   stdev_success = stdev_success/count;
   stdev_success = sqrt( stdev_success );

   // Calculate standard deviation

    std::cout << " Successes in all grasps for "<< name << ": "<< count<<"/"<< ges.size()<<"( "<< (double)count/ges.size() <<") avg success: "<< mean_success << " stdev: "<< stdev_success << std::endl;
    std::cout << "Max avg epsilon: ("<<maxAvgIndex<<"): "<< maxAvgEpsilon << " pf: "<<ges[maxAvgIndex].ge.numSuccesses/(double)ges[maxAvgIndex].ge.numberSamples<< ", skewness: "<< ges[maxAvgIndex].ge.skewness << std::endl; 
    std::cout << "Max     epsilon: ("<<maxIndex<<"): "<< maxEpsilon << " pf: "<<ges[maxIndex].ge.numSuccesses/(double)ges[maxIndex].ge.numberSamples<< ", skewness: "<< ges[maxIndex].ge.skewness << std::endl; 
    std::cout << "Max Pf: ("<< maxPfIndex<<"): "<< maxPf << " epsilon: "<< ges[maxPfIndex].ge.epsilon << " avg epsilon: "<< ges[maxPfIndex].ge.avg_epsilon << ", skewness: "<< ges[maxPfIndex].ge.skewness << std::endl;

    Eigen::Isometry3d mt; mt = ges[maxPfIndex].ge.g->getToh().matrix();
    std::cout << "Translation: "<< mt.translation().transpose() << std::endl;
    Eigen::Vector3d rpy; rpy = dart::math::matrixToEulerXYZ( mt.linear() );
    std::cout << "RPY: "<< (180.0/3.1416)*rpy.transpose() << std::endl;
  }
  input.close();



}
