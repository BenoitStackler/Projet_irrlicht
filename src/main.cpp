#include <irrlicht.h>
#include "character.hpp"
#include "hero.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "Terrain.hpp"
#include "Caisse.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

IrrlichtDevice *device;
IVideoDriver *driver;
ISceneManager *smgr;
float dim_pix_x = 10.0f;
float dim_pix_y = 10.0f;

class MyEventReceiver : public IEventReceiver
{
public:
  // This is the one method that we have to implement
  virtual bool OnEvent(const SEvent &event)
  {
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
  }

  // This is used to check whether a key is being held down
  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }

  MyEventReceiver()
  {
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
  }

private:
  // We use this array to store the current state of each key
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main()
{
  // create device
  MyEventReceiver receiver;
  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(256 * 5, 256 * 5), 16, false, false, false, &receiver);
  if (!device)
    return 1;
  device->setWindowCaption(L"Hello CPE!");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  //IGUIEnvironment* guienv = device->getGUIEnvironment();

  //smgr->addCameraSceneNodeFPS();
  ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(256.0f * 1 / 2, 256.0f * 1, 256.0f * 1 / 2), vector3df(-1.0f + 256.0f * 1 / 2, 0, 256.0f * 1 / 2));
  camera->setRotation(vector3df(32, 90, 90));
  camera->bindTargetAndRotation(true);

  // guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
  // rect<s32>(10,10,260,22), true);
  device->getFileSystem()->addFileArchive("./irrlicht-1.8.4/media/map-20kdm2.pk3");

  Terrain terain = Terrain("./irrlicht-1.8.4/media/terrain-heightmap.bmp", "./irrlicht-1.8.4/media/stones.jpg", vector3df(0.0f, 0.0f, 0.0f), vector3df(0, 0, 0), vector3df(1.0f, 0, 1.0f));
  Caisse caisse = Caisse(vector2d<int>(10, 10), 10.0f);
  Caisse caisse1 = Caisse(vector2d<int>(120, 120), 10.0f);
  caisse1.scale(vector3df(3.0f, 1.0f, 1.0f));
  Hero hero = Hero("./irrlicht-1.8.4/media/sydney.md2", "./irrlicht-1.8.4/media/sydney.bmp", vector3df(0, 0, 0), vector3df(0, 0, 0), 200.0f, 20.0f);
  std::vector<Enemy> enemies = create_enemy(3, hero);

  Projectile proj = hero.shoot();
  //IAnimatedMesh* mesh = smgr->getMesh("./irrlicht-1.8.4/media/sydney.md2");
  // scene::IAnimatedMesh *meshq = smgr->getMesh("20kdm2.bsp");
  // scene::ISceneNode *nodeq = 0;

  // if (meshq)
  // {
  //   nodeq = smgr->addOctreeSceneNode(meshq->getMesh(0), 0, -1, 1024);
  // }
  // if (nodeq)
  //   nodeq->setPosition(core::vector3df(-1300, -144, -1249));

  //  scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));

  //   if(anim)
  //   {
  //       node->addAnimator(anim);
  //       anim->drop();
  //       anim = 0;
  //   }
  //node->drop();
  //node = 0; // As I shouldn't refer to it again, ensure that I can't

  device->getCursorControl()->setVisible(false);
  int lastFPS = -1;

  // In order to do framerate independent movement, we have to know
  // how long it was since the last frame
  u32 then = device->getTimer()->getTime();

  // This is the movemen speed in units per second.
  const f32 MOVEMENT_SPEED = 40.f;

  while (device->run())
  {
    // Work out a frame delta time.
    const u32 now = device->getTimer()->getTime();
    const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
    then = now;

    driver->beginScene(true, true, video::SColor(0, 100, 100, 100));

    smgr->drawAll();

    driver->endScene();

    int fps = driver->getFPS();

    if (lastFPS != fps)
    {
      core::stringw tmp(L"Video Game - Irrlicht Engine [");
      tmp += driver->getName();
      tmp += L"] fps: ";
      tmp += fps;

      device->setWindowCaption(tmp.c_str());
      lastFPS = fps;
    }
  }
  device->drop();

  return 0;
}
