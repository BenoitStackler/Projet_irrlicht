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
#include "Mur.hpp"
#include "Obstacle.hpp"
#include "Grid.hpp"
#include "Node_Graph.hpp"
#include "Path.hpp"
#include "vec2.hpp"
#include "Receiver.hpp"
#include "collision.hpp"
#include "world.hpp"
#include "utils.hpp"

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
Grid grid;
std::vector<Node_Graph> vec_nodes;
Hero hero;

std::vector<irr::scene::ITriangleSelector *> selector;
irr::scene::ISceneCollisionManager *collMan;
World world;
bool EndGame = false;
bool Win = false;

int main()
{
  // create device
  Receiver receiver;

  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(940, 940), 16, false, false, false, &receiver);
  if (!device)
    return 1;
  device->setWindowCaption(L"Hello CPE!");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  //IGUIEnvironment* guienv = device->getGUIEnvironment();

  //smgr->addCameraSceneNodeFPS();
  ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(940.0f / 2, 645.0f, 940.0f / 2), vector3df(938.0f / 2, 0, 940.0f / 2));
  // camera->setRotation(vector3df(32, 90, 90));
  camera->bindTargetAndRotation(true);

  // guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
  // rect<s32>(10,10,260,22), true);
  device->getFileSystem()->addFileArchive("./irrlicht-1.8.4/media/map-20kdm2.pk3");

  Terrain terain = Terrain("./irrlicht-1.8.4/media/terrain-heightmap.bmp", "./irrlicht-1.8.4/media/3.jpg", vector3df(0.0f, 0.0f, 0.0f), vector3df(0, 0, 0), vector3df(1000.0f / 256.0f, 0, 1000.0f / 256.0f));
  Caisse caisse = Caisse(vector2d<int>(0, 0), 10.0f);
  Caisse caisse1 = Caisse(vector2d<int>(89, 89), 10.0f);

  Mur murN = Mur(0, 0, 1, 89);
  Mur murS = Mur(89, 0, 1, 89);
  Mur murE = Mur(0, 89, 89, 1);
  Mur murW = Mur(0, 0, 89, 1);

  //caisse1.scale(vector3df(3.0f, 1.0f, 1.0f));
  hero = Hero("./irrlicht-1.8.4/media/sydney.md2", "./irrlicht-1.8.4/media/sydney.bmp", vector3di(45, 0, 45), vector3df(0, 0, 0), 50.0f, 20.0f);
  world.defHero(&hero);
  std::vector<Enemy> enemies = create_enemy(hero);

  selector.push_back(smgr->createTriangleSelector(murN.node()->getMesh(), murN.node()));
  selector.push_back(smgr->createTriangleSelector(murS.node()->getMesh(), murS.node()));
  selector.push_back(smgr->createTriangleSelector(murE.node()->getMesh(), murE.node()));
  selector.push_back(smgr->createTriangleSelector(murW.node()->getMesh(), murW.node()));
  selector.push_back(smgr->createTriangleSelector(hero.node()));

  for (auto e : enemies)
  {
    selector.push_back(smgr->createTriangleSelector(e.node()));
  }

  // std::vector<Projectile> vect_proj;
  // vect_proj.push_back(proj);

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

  device->getCursorControl()
      ->setVisible(false);
  int lastFPS = -1;

  // In order to do framerate independent movement, we have to know
  // how long it was since the last frame
  u32 then = device->getTimer()->getTime();

  // This is the movemen speed in units per second.
  const f32 MOVEMENT_SPEED = 40.f;

  int Nx = 90;
  int Ny = 90;

  Mur obst1(10, 20, 20, 10);
  obst1.x(10);
  obst1.y(20);
  obst1.nx(20);
  obst1.ny(10);

  Mur obst2(60, 60, 29, 20);
  obst2.x(60);
  obst2.y(60);
  obst2.nx(29);
  obst2.ny(20);

  Mur obst3(50, 40, 20, 20);
  obst3.x(50);
  obst3.y(40);
  obst3.nx(20);
  obst3.ny(20);

  Mur obst4(30, 60, 20, 20);
  obst4.x(30);
  obst4.y(60);
  obst4.nx(20);
  obst4.ny(20);

  std::vector<Obstacle> obstacles;
  obstacles.push_back(obst1);
  obstacles.push_back(obst2);
  obstacles.push_back(obst3);
  obstacles.push_back(obst4);
  obstacles.push_back(murN);
  obstacles.push_back(murS);
  obstacles.push_back(murE);
  obstacles.push_back(murW);

  world.addObstacle(&obst1);
  world.addObstacle(&obst2);
  world.addObstacle(&obst3);
  world.addObstacle(&obst4);
  world.addObstacle(&murN);
  world.addObstacle(&murW);
  world.addObstacle(&murE);
  world.addObstacle(&murS);

  grid = create_grid_obstacles(Nx, Ny, obstacles);

  std::vector<vec2> nodes = get_nodes_positions(Nx, Ny, obstacles, grid);
  Grid grid_nodes(Nx, Ny);

  for (long unsigned int k = 0; k < nodes.size(); k++)
  {
    grid_nodes(nodes[k].x, nodes[k].y) = 1;
  }

  int k = 0;

  for (vec2 node_v : nodes)
  {
    Node_Graph *node = new Node_Graph(node_v.x, node_v.y, k);
    vec_nodes.push_back(*node);
    ++k;
  }

  while (device->run() && !EndGame)
  {
    keyControl(receiver);
    // Work out a frame delta time.
    const u32 now = device->getTimer()->getTime();
    const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
    then = now;

    driver->beginScene(true, true, video::SColor(0, 100, 100, 100));
    hero.move();
    for (auto proj : world.getProjectiles())
    {
      proj->move();
    }

    compute_collisions(&world);

    //collisionProj(world.getProjectiles());
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
