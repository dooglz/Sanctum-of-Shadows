#include <irrlicht.h>
#include <btBulletCollisionCommon.h>

namespace GameEngine{
	/*! \brief Irrlicht interface for Bullet debug Rendering.
	 *
	 * http://irrlicht.sourceforge.net/forum/viewtopic.php?t=38289
	 *  \ingroup  Engine
	 */
	class DebugDraw : public btIDebugDraw
	{
		public:
			//! Constructor.
			DebugDraw(irr::IrrlichtDevice* const device) :
				mode(DBG_NoDebug), driver(device->getVideoDriver()), logger(device->getLogger()){}

			//! Draw a line.
			void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

			//! Draw a Point.
			void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

			//! Report Error.
			void reportErrorWarning(const char* text);

			//! Draw a line.
			void draw3dText(const btVector3& location, const char* text) { }

			//! Set the debug mode.
			void setDebugMode(int mode)
			{
				this->mode = mode;
			}

			//! Get the debug mode.
			int getDebugMode() const {
				return this->mode;
			}

		private:
			
			//! current Mode.
			int mode;
			
			//! Pointer to the Irrlicht driver
			irr::video::IVideoDriver* const driver;
			
			//TODO investigate irr::ILogger, it sounds cool.
			//! Pointer to the Irrlicht Logger
			irr::ILogger* logger;
	};
}