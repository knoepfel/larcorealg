/**
 * @file   larcorealg/Geometry/GeoVectorLocalTransformation.tcc
 * @brief  Specialization of local-to-world transformations for ROOT GenVector
 *         (template implementation).
 * @author Gianluca Petrillo (petrillo@slac.stanford.edu)
 * @date   January 31, 2019
 * @see    `GeoVectorLocalTransformation.h`
 *
 * This file is expected to be included directly in the header.
 *
 */

#ifndef LARCOREALG_GEOMETRY_GEOVECTORLOCALTRANSFORMATION_TCC
#define LARCOREALG_GEOMETRY_GEOVECTORLOCALTRANSFORMATION_TCC

// LArSoft libraries
#include "larcorealg/Geometry/geo_vectors_utils.h" // geo::vect::fillCoords()...

// framework libraries
#include "cetlib_except/exception.h"

// ROOT
#include "TGeoNode.h"
#include "TGeoMatrix.h"

// CLHEP
#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Vector/Rotation.h" // CLHEP::HepRotation
#include "CLHEP/Vector/RotationInterfaces.h" // CLHEP::HepRep3x3
#include "CLHEP/Vector/ThreeVector.h" // CLHEP::Hep3Vector

// C standard library
#include <cassert>



//------------------------------------------------------------------------------
template <>
struct geo::details::TransformationMatrixConverter
  <ROOT::Math::Transform3D, TGeoMatrix>
{
  static ROOT::Math::Transform3D convert(TGeoMatrix const& trans);
};


//------------------------------------------------------------------------------
template <>
template <typename DestPoint, typename SrcPoint>
DestPoint geo::LocalTransformation<ROOT::Math::Transform3D>::WorldToLocalImpl
  (SrcPoint const& world) const
{
  // need inverse transformation
  using geo::vect::convertTo;
  return geo::vect::convertTo<DestPoint>(
    fGeoMatrix.ApplyInverse
      (convertTo<typename TransformationMatrix_t::Point>(world))
    );
} // geo::LocalTransformation::WorldToLocal()


//......................................................................
template <>
template <typename DestVector, typename SrcVector>
DestVector
geo::LocalTransformation<ROOT::Math::Transform3D>::WorldToLocalVectImpl
  (SrcVector const& world) const
{
  // need inverse transformation
  using geo::vect::convertTo;
  return geo::vect::convertTo<DestVector>(
    fGeoMatrix.ApplyInverse
      (convertTo<typename TransformationMatrix_t::Vector>(world))
    );
} // geo::LocalTransformation::WorldToLocalVect()


//......................................................................
template <>
template <typename DestPoint, typename SrcPoint>
DestPoint geo::LocalTransformation<ROOT::Math::Transform3D>::LocalToWorldImpl
  (SrcPoint const& local) const
{
  // need direct transformation
  using geo::vect::convertTo;
  return convertTo<DestPoint>
    (fGeoMatrix(convertTo<typename TransformationMatrix_t::Point>(local)));
  
} // geo::LocalTransformation::LocalToWorld()

  
//......................................................................
template <>
template <typename DestVector, typename SrcVector>
DestVector
geo::LocalTransformation<ROOT::Math::Transform3D>::LocalToWorldVectImpl
  (SrcVector const& local) const
{
  // need direct transformation
  using geo::vect::convertTo;
  return convertTo<DestVector>
    (fGeoMatrix(convertTo<typename TransformationMatrix_t::Vector>(local)));
} // geo::LocalTransformation::LocalToWorldVect()


//------------------------------------------------------------------------------

#endif // LARCOREALG_GEOMETRY_GEOVECTORLOCALTRANSFORMATION_TCC

// Local variables:
// mode: c++
// End:
