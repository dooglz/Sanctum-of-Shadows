#include "BulletDebugDraw.h"
//bullet debug, http://irrlicht.sourceforge.net/forum/viewtopic.php?t=38289

namespace GameEngine{

	// Draw a line.
	void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		//workaround to bullet's inconsistent debug colors which are either from 0.0 - 1.0 or from 0.0 - 255.0
		irr::video::SColor newColor(255, (irr::u32)color[0], (irr::u32)color[1], (irr::u32)color[2]);
		if (color[0] <= 1.0 && color[0] > 0.0)
		newColor.setRed((irr::u32)(color[0]*255.0));
		if (color[1] <= 1.0 && color[1] > 0.0)
		newColor.setGreen((irr::u32)(color[1]*255.0));
		if (color[2] <= 1.0 && color[2] > 0.0)
		newColor.setBlue((irr::u32)(color[2]*255.0));
		this->driver->draw3DLine(
			irr::core::vector3df(from[0], from[1], from[2]),
			irr::core::vector3df(to[0], to[1], to[2]),
			newColor
		);
	}

	// Draw a Point.
	void DebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
		static const irr::video::SColor CONTACTPOINT_COLOR(255, 255, 255, 0); //bullet's are black :(
		//   this->drawLine(PointOnB, PointOnB + normalOnB*distance, CONTACTPOINT_COLOR);
		const btVector3 to(PointOnB + normalOnB*distance);
		this->driver->draw3DLine(
			irr::core::vector3df(PointOnB[0], PointOnB[1], PointOnB[2]),
			irr::core::vector3df(to[0], to[1], to[2]),
			CONTACTPOINT_COLOR
		);
	}

	// Report Error.
	void DebugDraw::reportErrorWarning(const char* text)
	{
		this->logger->log(text, irr::ELL_ERROR);
	}

}