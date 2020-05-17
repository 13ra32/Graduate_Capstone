#include "rs_chauffeur/rs_chauffeur.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "rs_chauffeur");
  RsChauffeur rc;
  rc.ignite();
  return 0;
}