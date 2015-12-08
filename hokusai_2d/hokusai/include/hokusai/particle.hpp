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

#ifndef HOKUSAI_PARTICLE_H
#define HOKUSAI_PARTICLE_H

#include "utility.hpp"
#include <vector>

/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */

namespace hokusai
{
    class Boundary
    {
        public :
        double psi; //density number
        Vec2d x,v; ///position and velocity

        public :
        Boundary()
        {
            psi=0.0;
            x=Vec2d(0.0,0.0);
            v=Vec2d(0.0,0.0);
        }

        Boundary(const Vec2d& _x, const Vec2d _v = Vec2d(0.0,0.0), const double _psi=0.0)
        {
            x=_x;
            v=_v;
            psi=_psi;
        }

        Boundary(const Boundary& b)
        {
            x=b.x;
            v=b.v;
            psi=b.psi;
        }

        ~Boundary(){}
    };

    class MovingBoundary
    {
    public :
        MovingBoundary()
        {
            m_id.clear();
            m_translation = Vec2d(0.0,0.0);
            m_increment = Vec2d(0.0,0.0);
            m_delta = Vec2d(0.0,0.0);
            m_oscillatory = true;
            m_tmpTranslation = Vec2d(0.0,0.0);
        }

        MovingBoundary(std::vector<int>& id, Vec2d& translation, bool& oscillatory, Vec2d& delta)
        {
            m_id = id;
            m_translation = translation;
            m_increment = Vec2d(0.0,0.0);
            m_delta = delta;
            m_oscillatory = oscillatory;
            m_tmpTranslation = m_translation;
        }

        MovingBoundary(const MovingBoundary& movingBoundary)
        {
            m_id = movingBoundary.m_id;
            m_translation = movingBoundary.m_translation;
            m_increment = movingBoundary.m_increment;
            m_delta = movingBoundary.m_delta;
            m_oscillatory = movingBoundary.m_oscillatory;
            m_tmpTranslation = movingBoundary.m_tmpTranslation;
        }

        void applyMotion(std::vector<Boundary>& boundaries)
        {
            if(m_oscillatory && m_increment[0] >= m_delta[0])
            {
                m_increment[0] = 0.0;
                m_tmpTranslation[0] = -m_tmpTranslation[0];
            }
            if(m_oscillatory && m_increment[1] >= m_delta[1])
            {
                m_increment[1] = 0.0;
                m_tmpTranslation[1] = -m_tmpTranslation[1];
            }

            for(const int & id : m_id)
            {
                applyMotion(boundaries[id].x);
            }

            m_increment[0] += std::abs(m_translation[0]);
            m_increment[1] += std::abs(m_translation[1]);
        }

        void applyMotion(Vec2d& position)
        {
            position[0] += m_tmpTranslation[0];
            position[1] += m_tmpTranslation[1];
        }

        std::vector< int > m_id;
        Vec2d m_translation;
        Vec2d m_delta;
        Vec2d m_increment;
        Vec2d m_tmpTranslation;
        bool m_oscillatory;
    };

    class Particle
    {
        public :
        double rho, rho_adv, rho_corr, p, p_l, previousP, aii;
        Vec2d x, v, v_adv, f_adv, f_p, dii_fluid, dii_boundary, sum_dij, n;
        Vec2d c;
        std::vector<int> fluidNeighbor;
        std::vector<int> boundaryNeighbor;

        public :
        Particle()
        {
            rho = rho_adv = rho_corr = p = p_l = previousP = aii = 0.0;
            x = v = v_adv = f_adv = f_p = dii_fluid = dii_boundary = sum_dij = n = Vec2d(0.0,0.0);
            c = Vec2d(0.0,0.0);
            fluidNeighbor.clear();
            boundaryNeighbor.clear();
        }

        Particle(const Vec2d& _x, const Vec2d& _v, const Vec2d _c)
        {
            x = _x;
            v = _v;
            c = _c;

            rho = rho_adv = rho_corr = p = p_l = previousP = aii = 0.0;
            v_adv = f_adv = f_p = dii_fluid = dii_boundary = sum_dij = n = Vec2d(0.0,0.0);
            fluidNeighbor.clear();
            boundaryNeighbor.clear();
        }

        Particle(const Particle& _p)
        {
            rho=_p.rho;
            rho_adv=_p.rho_adv;
            rho_corr=_p.rho_corr;
            p=_p.p;
            p_l=_p.p_l;
            previousP=_p.previousP;
            aii=_p.aii;

            x = _p.x;
            v = _p.v;
            v_adv = _p.v_adv;
            f_adv = _p.f_adv;
            f_p = _p.f_p;
            dii_fluid=_p.dii_fluid;
            dii_boundary=_p.dii_boundary;
            sum_dij=_p.sum_dij;
            n = _p.n;

            c = _p.c;

            fluidNeighbor=_p.fluidNeighbor;
            boundaryNeighbor=_p.boundaryNeighbor;
        }

        ~Particle(){}
    };
}
#endif
