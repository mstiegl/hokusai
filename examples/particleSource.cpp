#include <hokusai/system.hpp>
#include <hokusai/io.hpp>
#include <hokusai/particleSource.hpp>

#define timer   timer_class
#include <boost/progress.hpp>
#undef timer
#include <boost/timer/timer.hpp>

#include <iostream>
#include <algorithm>

using namespace std;
using namespace hokusai;

int main()
{
    int particleNumber = 20000; ///particle number
    HReal volume = 1.0; ///m3
    HReal restDensity = 1000.0; ///kg/m3
    HReal viscosity = 0.1;
    HReal cohesion = 0.05;
    FluidParams fluidParams(particleNumber, volume, restDensity, viscosity, cohesion);

    HReal adhesion=0.001;
    HReal friction=1.0;
    BoundaryParams boundaryParams(fluidParams.smoothingRadius()/2.0, adhesion, friction);

    HReal timeStep = 4e-3;
    int maxPressureSolveIterationNb = 2;
    HReal maxDensityError = 1.0;
    SolverParams solverParams(timeStep, maxPressureSolveIterationNb, maxDensityError);

    System sph(fluidParams, boundaryParams, solverParams);

    Vec3r  securityOffset(1.05*fluidParams.smoothingRadius());
    Vec3r  boundBox(2.0,2.5,1.0);
    boundBox += securityOffset;
    Vec3r  boundOffset(0,0,0);
    boundOffset -= securityOffset;
    sph.addBoundaryBox(boundOffset, boundBox);

    HReal startTime, endTime, delay, spacing;
    Vec3r  position, orientation, scale, velocity;

    startTime=0;
    endTime = 3.0;
    delay=0.02;
    spacing = 1.05*fluidParams.smoothingRadius();
    velocity = Vec3r(0.0,0.0,2.0);
    scale = Vec3r(0.15,0.15,0.15);

    position = Vec3r(0.25,1.0,0.5);
    orientation = Vec3r(0,M_PI/2.0,0);
    ParticleSource source1(startTime, endTime, delay, spacing, position, orientation, scale, velocity);
    sph.addParticleSource(source1);

    position = Vec3r(1.75,1.0,0.5);
    orientation = Vec3r(0,-M_PI/2.0,0);
    ParticleSource source2(startTime, endTime, delay, spacing, position, orientation, scale, velocity);
    sph.addParticleSource(source2);

    sph.init();

    double time = 10.0;
    int count=0;
    boost::timer::auto_cpu_timer t;
    boost::progress_display show_progress( std::floor(time/solverParams.timeStep()) );
    while(sph.getTime()<=time)
    {
        //Simulate
        sph.computeSimulationStep();


        //Output
        if( std::floor((sph.getTime()-solverParams.timeStep())/0.016) != std::floor(sph.getTime()/0.016) )
        {
            write_frame(sph, count);
            sph.exportState("./");
            ++count;
        }

        //Update progress bar
        ++show_progress;
    }
    std::cout << "Particle Number : " << sph.particleNumber() << std::endl;

    return 0;
}
