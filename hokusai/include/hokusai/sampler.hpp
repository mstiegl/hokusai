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

#ifndef HOKUSAI_SAMPLER_HPP
#define HOKUSAI_SAMPLER_HPP

#include "Vec.hpp"
#include "triMesh.hpp"
#include <vector>

namespace hokusai
{

bool LineLineIntersect(const Vec3<double>& p1, const Vec3<double>& p2, const Vec3<double>& p3, const Vec3<double>& p4, Vec3<double>& pa, Vec3<double>& pb,double & mua, double & mub);
bool LineIntersect(const Vec2<double>& p1, const Vec2<double>& p2, const Vec2<double>& p3, const Vec2<double>& p4, Vec2<double>& p);
bool LineIntersect(const Vec3<double>& p1, const Vec3<double>& p2, const Vec3<double>& p3, const Vec3<double>& p4, Vec3<double>& p);

//Surface sampling
bool AkinciTriangleSampling( const Vec3<double>& p1, const Vec3<double>& p2, const Vec3<double>& p3, const double& particleDiameter, std::vector< Vec3<double> >& samples);
bool AkinciEdgeSampling( const Vec3<double>& p1, const Vec3<double>& p2, const double& particleDiameter, std::vector< Vec3<double> >& samples);
bool AkinciMeshSampling(const TriMesh& mesh, const double &particleDiameter, std::vector<Vec3f>& samples);
bool AkinciFullTriangleSampling( const Vec3<double>& p1, const Vec3<double>& p2, const Vec3<double>& p3, const double& particleDiameter, std::vector< Vec3<double> >& samples);



std::vector<Vec3<double> > getDiskSampling(const Vec3<double>& center, double radius, double spacing);
std::vector<Vec3<double> > getSphereSampling(const Vec3<double>& center, double radius, double spacingX, double spacingY);
std::vector<Vec3<double> > getHemiSphereSampling(const Vec3<double>& center, double radius, double spacingX, double spacingY);

std::vector<Vec3<double> > getEllipsoidSampling(const Vec3<double>& center, double axis_1, double axis_2, double axis_3, double spacingX, double spacingY);
std::vector< Vec3<double> > getTorusSampling(const Vec3<double>& center, double tubeRadius, double innerRadius, double spacingX, double spacingY);

std::vector< Vec3<double> > getConeSampling(const Vec3<double>& center, double height, double stopHeight, double baseRadius, double spacingX, double spacingY);
std::vector<Vec3<double> > getPyramidSampling(const Vec3<double>& _center, double base, double height, double spacing);
std::vector< Vec3<double> > getCylinderSampling(const Vec3<double>& center, double height, double baseRadius, double spacingX, double spacingY);
std::vector<Vec3<double> > getCapsuleSampling(const Vec3<double>& center, double radius, double height, double spacingX, double spacingY);

}
#endif
