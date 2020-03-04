cmake_minimum_required( VERSION 3.0 )

project( uPowerSimulator )

include_directories( ./include ./src )
add_executable( upowersim ./src/uPowerSim.c )
