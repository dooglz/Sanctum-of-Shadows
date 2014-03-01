#include <irrlicht.h>
#include <btBulletCollisionCommon.h>

namespace GameEngine{
	//bullet debug, http://irrlicht.sourceforge.net/forum/viewtopic.php?t=38289

	class DebugDraw : public btIDebugDraw
	{
		public:
			DebugDraw(irr::IrrlichtDevice* const device) :
				mode(DBG_NoDebug), driver(device->getVideoDriver()), logger(device->getLogger()){}
			void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
			void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
			void reportErrorWarning(const char* text);
			void draw3dText(const btVector3& location, const char* text) { }
			void setDebugMode(int mode)
			{
				this->mode = mode;
			}
			int getDebugMode() const {
				return this->mode;
			}

		private:
			int mode;
			irr::video::IVideoDriver* const driver;
			irr::ILogger* logger;
	};
}