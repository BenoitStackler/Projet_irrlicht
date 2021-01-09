#include <irrlicht.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "character.hpp"
#include "hero.hpp"
#include "enemy.hpp"
#include "projectile.hpp"
#include "Terrain.hpp"
#include "Caisse.hpp"
#include "Obstacle.hpp"
#include "Grid.hpp"
#include "Node_Graph.hpp"
#include "Path.hpp"
#include "vec2.hpp"
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
  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1000, 1000), 16, false, false, false, &receiver);
  if (!device)
    return 1;
  device->setWindowCaption(L"Hello CPE!");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  //IGUIEnvironment* guienv = device->getGUIEnvironment();

  //smgr->addCameraSceneNodeFPS();
  ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(256.0f * 1 / 2, 256.0f * 0.8, 256.0f * 1 / 2), vector3df(255.0f * 1 / 2, 0, 256.0f * 1 / 2));
  camera->setRotation(vector3df(32, 90, 90));
  camera->bindTargetAndRotation(true);

  // guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
  // rect<s32>(10,10,260,22), true);
  device->getFileSystem()->addFileArchive("./irrlicht-1.8.4/media/map-20kdm2.pk3");

  Terrain terain = Terrain("./irrlicht-1.8.4/media/terrain-heightmap.bmp", "./irrlicht-1.8.4/media/stones.jpg", vector3df(0.0f, 0.0f, 0.0f), vector3df(0, 0, 0), vector3df(1.0f, 0, 1.0f));
  Caisse caisse = Caisse(vector2d<int>(10, 10), 10.0f);
  Caisse caisse1 = Caisse(vector2d<int>(120, 120), 10.0f);
  //caisse1.scale(vector3df(3.0f, 1.0f, 1.0f));
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


  int Nx = 10;
  int Ny = 10;

  Obstacle obst1;
  obst1.x(1);
  obst1.y(2);
  obst1.nx(2);
  obst1.ny(1);

  Obstacle obst2;
  obst2.x(6);
  obst2.y(6);
  obst2.nx(3);
  obst2.ny(2);

  Obstacle obst3;
  obst3.x(5);
  obst3.y(4);
  obst3.nx(2);
  obst3.ny(2);

  Obstacle obst4;
  obst4.x(3);
  obst4.y(6);
  obst4.nx(2);
  obst4.ny(2);


  std::vector<Obstacle> obstacles;
  obstacles.push_back(obst1);
  obstacles.push_back(obst2);
  obstacles.push_back(obst3);
  obstacles.push_back(obst4);

  Grid grid = create_grid_obstacles(Nx, Ny, obstacles);



  std::vector<vec2> nodes = get_nodes_positions(Nx, Ny, obstacles, grid);
  Grid grid_nodes(Nx, Ny);

  for (int k = 0 ; k < nodes.size() ; k++){
      grid_nodes(nodes[k].x, nodes[k].y) = 1;
  }

  for (int i = 0 ; i < Nx ; i++){
      for (int j = 0 ; j < Ny ; j++){
          std::cout << grid(i, j) + 2*grid_nodes(i, j) << " " ;

      }
      std::cout << std::endl;
  }

  vec2 p0;
  vec2 p1;
  p0.x = 0;
  p1.x = 2;
  p0.y = 3;
  p1.y = 5;

  auto c = bresenham(p0, p1);



  std::vector<Node_Graph> vec_nodes;
  int k = 0;
  for (vec2 node_v : nodes){
      vec_nodes.push_back(Node_Graph(node_v.x, node_v.y, k));
      ++k;
  } 
  Node_Graph start(7, 4, k);
  ++k;
  Node_Graph end(1, 9, k);


  vec_nodes.push_back(end);
  vec_nodes.push_back(start);

  start.compute_neighbours(vec_nodes, grid);
  end.compute_neighbours(vec_nodes, grid);

  for (int k = 0 ; k < vec_nodes.size() ; k++){
      vec_nodes[k].compute_neighbours(vec_nodes, grid);
  }

  int s = vec_nodes.size();

  Path foundPath = find_path(vec_nodes, start, end);

  for (Node_Graph node : foundPath.path()){
      std::cout << '(' << node.x() << ',' << node.y() <<')' << std::endl;
  }






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
