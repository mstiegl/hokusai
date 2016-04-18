/*
* Copyright 2015 Pierre-Luc Manteaux
*
*This file is part of Hokusai.
*
*Hokusai is free software: you can redistribute it and/or modify
*it under the terms of the GNU General Public License as published by
*the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
*
*Hokusai is distributed in the hope that it will be useful,
*but WITHOUT ANY WARRANTY; without even the implied warranty of
*MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*GNU General Public License for more details.
*
*You should have received a copy of the GNU General Public License
*along with Hokusai.  If not, see <http://www.gnu.org/licenses/>.
*
* Author : Pierre-Luc Manteaux
* Contact : pierre-luc.manteaux@inria.fr
*/

#ifndef HOKUSAI_IISPH_SOLVER_HPP
#define HOKUSAI_IISPH_SOLVER_HPP

#include "./../particleIISPH.hpp"
#include "./../boundaryIISPH.hpp"
#include "./../particleContainer.hpp"
#include "./../boundaryContainer.hpp"

#include <memory>

namespace hokusai
{

class IISPHSolver
{
public:
    typedef ParticleIISPH Particle;
    typedef BoundaryIISPH Boundary;

    IISPHSolver();
    ~IISPHSolver();
    std::shared_ptr< ParticleContainer<Particle> > m_particles;
    std::shared_ptr< BoundaryContainer<Boundary> > m_boundaries;
};

}


#endif // HOKUSAI_IISPH_SOLVER_HPP
