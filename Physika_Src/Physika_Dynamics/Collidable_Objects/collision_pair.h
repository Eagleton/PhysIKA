/*
 * @file  collision_pair.h
 * @pairs of colliding elementaries
 * @author Tianxiang Zhang
 * 
 * This file is part of Physika, a versatile physics simulation library.
 * Copyright (C) 2013 Physika Group.
 *
 * This Source Code Form is subject to the terms of the GNU General Public License v2.0. 
 * If a copy of the GPL was not distributed with this file, you can obtain one at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 */

#ifndef PHYSIKA_DYNAMICS_COLLIDABLE_OBJECTS_COLLISION_PAIR_H_
#define PHYSIKA_DYNAMICS_COLLIDABLE_OBJECTS_COLLISION_PAIR_H_

#include "Physika_Geometry/Surface_Mesh/surface_mesh.h"
#include "Physika_Dynamics/Collidable_Objects/collidable_object.h"

namespace Physika{

template <typename Scalar,int Dim> class CollisionPairBase;
template <typename Scalar,int Dim> class CollidableObject;
template <typename Scalar,int Dim> class MeshBasedCollidableObject;


//CollisionPair contains colliding elements (e.g. faces of meshes) and objects.
//It's different from ContactPoint, which contains position and normal of contact points.
//ContactPoint should be generated from CollisionPair. This process is called "contact sampling".
//Notice that contact sampling is not a bijection.
template <typename Scalar,int Dim>
class CollisionPairBase
{
public:
	CollisionPairBase();
	virtual ~CollisionPairBase();

    virtual typename CollidableObject<Scalar, Dim>::ObjectType objectTypeLhs() const = 0;
    virtual typename CollidableObject<Scalar, Dim>::ObjectType objectTypeRhs() const = 0;

	//Functions for getting objects and faces of a mesh-to-mesh collision pair, corresponding to class CollisionPairMeshToMesh
	virtual const CollidableObject<Scalar, Dim>* objectLhs() const = 0;
	virtual CollidableObject<Scalar, Dim>* objectLhs() = 0;
	virtual const CollidableObject<Scalar, Dim>* objectRhs() const = 0;
	virtual CollidableObject<Scalar, Dim>* objectRhs() = 0;
	virtual const MeshBasedCollidableObject<Scalar, Dim>* meshObjectLhs() const = 0;
	virtual MeshBasedCollidableObject<Scalar, Dim>* meshObjectLhs() = 0;
	virtual const MeshBasedCollidableObject<Scalar, Dim>* meshObjectRhs() const = 0;
	virtual MeshBasedCollidableObject<Scalar, Dim>* meshObjectRhs() = 0;
	virtual const Face<Scalar>* faceLhsPtr() const = 0;
	virtual Face<Scalar>* faceLhsPtr() = 0;
	virtual const Face<Scalar>* faceRhsPtr() const = 0;
	virtual Face<Scalar>* faceRhsPtr() = 0;
	virtual unsigned int faceLhsIdx() const = 0;
	virtual unsigned int faceRhsIdx() const = 0;
	virtual unsigned int objectLhsIdx() const = 0;
	virtual unsigned int objectRhsIdx() const = 0;

	//If other kinds of collision pairs need to be defined, e.g. mesh-to-implicit pairs, add corresponding functions here
};

//Face pair of a mesh-to-mesh collision
template <typename Scalar,int Dim>
class CollisionPairMeshToMesh : public CollisionPairBase<Scalar, Dim>
{
public:
	CollisionPairMeshToMesh(unsigned int object_lhs_index, unsigned int object_rhs_index,
							MeshBasedCollidableObject<Scalar, Dim>* object_lhs, MeshBasedCollidableObject<Scalar, Dim>* object_rhs,
							unsigned int face_lhs_index, unsigned int face_rhs_index);
	~CollisionPairMeshToMesh();

    typename CollidableObject<Scalar, Dim>::ObjectType objectTypeLhs() const;
    typename CollidableObject<Scalar, Dim>::ObjectType objectTypeRhs() const;

	const CollidableObject<Scalar, Dim>* objectLhs() const;
	CollidableObject<Scalar, Dim>* objectLhs();
	const CollidableObject<Scalar, Dim>* objectRhs() const;
	CollidableObject<Scalar, Dim>* objectRhs();
	const MeshBasedCollidableObject<Scalar, Dim>* meshObjectLhs() const;
	MeshBasedCollidableObject<Scalar, Dim>* meshObjectLhs();
	const MeshBasedCollidableObject<Scalar, Dim>* meshObjectRhs() const;
	MeshBasedCollidableObject<Scalar, Dim>* meshObjectRhs();
	const Face<Scalar>* faceLhsPtr() const;
	Face<Scalar>* faceLhsPtr();
	const Face<Scalar>* faceRhsPtr() const;
	Face<Scalar>* faceRhsPtr();
	unsigned int faceLhsIdx() const;
	unsigned int faceRhsIdx() const;
	unsigned int objectLhsIdx() const;
	unsigned int objectRhsIdx() const;

protected:
	unsigned int object_lhs_index_;
	unsigned int object_rhs_index_;
	MeshBasedCollidableObject<Scalar, Dim>* object_lhs_;
	MeshBasedCollidableObject<Scalar, Dim>* object_rhs_;
	unsigned int face_lhs_index_;
	unsigned int face_rhs_index_;
	Face<Scalar>* face_lhs_;
	Face<Scalar>* face_rhs_;
};

}  //end of namespace Physikas

#endif  //PHYSIKA_DYNAMICS_COLLIDABLE_OBJECTS_COLLISION_PAIR_H_