#pragma once
#include "Dynamics/ParticleSystem/ParticleSystem.h"

namespace PhysIKA
{
	template<typename> class ElasticityModule;
	template<typename> class PointSetToPointSet;

	/*!
	*	\class	TestParticleElasticBody
	*	\brief	Peridynamics-based elastic object.
	*/
	template<typename TDataType>
	class TestParticleElasticBody : public ParticleSystem<TDataType>
	{
		DECLARE_CLASS_1(TestParticleElasticBody, TDataType)
	public:
		typedef typename TDataType::Real Real;
		typedef typename TDataType::Coord Coord;

		TestParticleElasticBody(std::string name = "default");
		virtual ~TestParticleElasticBody();

		bool initialize() override;
		void advance(Real dt) override;
		void updateTopology() override;

		bool translate(Coord t) override;
		bool scale(Real s) override;

		void setElasticitySolver(std::shared_ptr<ElasticityModule<TDataType>> solver);
		std::shared_ptr<ElasticityModule<TDataType>> getElasticitySolver();
		void loadSurface(std::string filename);

		std::shared_ptr<PointSetToPointSet<TDataType>> getTopologyMapping();

		std::shared_ptr<Node> getSurfaceNode() { return m_surfaceNode; }

	public:
		VarField<Real> m_horizon;
		VarField<Coord> m_test;

	private:
		std::shared_ptr<Node> m_surfaceNode;
	};

#ifdef PRECISION_FLOAT
	template class TestParticleElasticBody<DataType3f>;
#else
	template class TestParticleElasticBody<DataType3d>;
#endif
}