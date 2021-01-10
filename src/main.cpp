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
std::map<std::string, Path> map_paths;

std::vector<irr::scene::ITriangleSelector *> selector;
irr::scene::ISceneCollisionManager *collMan;
World world;

int main()
{
  // create device
  Receiver receiver;

  device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1000, 1000), 16, false, false, false, &receiver);
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

  Terrain terain = Terrain("./irrlicht-1.8.4/media/terrain-heightmap.bmp", "./irrlicht-1.8.4/media/stones.jpg", vector3df(0.0f, 0.0f, 0.0f), vector3df(0, 0, 0), vector3df(1000.0f / 256.0f, 0, 1000.0f / 256.0f));
  Caisse caisse = Caisse(vector2d<int>(0, 0), 10.0f);
  Caisse caisse1 = Caisse(vector2d<int>(89, 89), 10.0f);

  Mur murN = Mur(0, 0, 1, 89);
  Mur murS = Mur(89, 0, 1, 89);
  Mur murE = Mur(0, 89, 89, 1);
  Mur murW = Mur(0, 0, 89, 1);

  //caisse1.scale(vector3df(3.0f, 1.0f, 1.0f));
  hero = Hero("./irrlicht-1.8.4/media/sydney.md2", "./irrlicht-1.8.4/media/sydney.bmp", vector3di(50, 0, 50), vector3df(0, 0, 0), 200.0f, 20.0f);
  world.defHero(hero);
  std::vector<Enemy> enemies = create_enemy(hero);

  selector.push_back(smgr->createTriangleSelector(caisse.node()->getMesh(), caisse.node()));
  selector.push_back(smgr->createTriangleSelector(caisse1.node()->getMesh(), caisse1.node()));
  selector.push_back(smgr->createTriangleSelector(hero.node()));

  Projectile proj = hero.shoot();

  std::vector<Projectile> vect_proj;
  vect_proj.push_back(proj);
  collisionProj(vect_proj);

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

  grid = create_grid_obstacles(Nx, Ny, obstacles);

  std::vector<vec2> nodes = get_nodes_positions(Nx, Ny, obstacles, grid);
  Grid grid_nodes(Nx, Ny);

  for (long unsigned int k = 0; k < nodes.size(); k++)
  {
    grid_nodes(nodes[k].x, nodes[k].y) = 1;
  }

  for (long unsigned int i = 0; i < Nx; i++)
  {
    for (long unsigned int j = 0; j < Ny; j++)
    {
      std::cout << grid(i, j) + 2 * grid_nodes(i, j) << " ";
    }
    std::cout << std::endl;
  }

  int k = 0;
  /*
  for (vec2 node_v : nodes)
  {
    Node_Graph* node = new Node_Graph(node_v.x, node_v.y, k);
    vec_nodes.push_back(*node);
    ++k;
  }
  */

  for (long unsigned int k = 0; k < vec_nodes.size(); k++)
  {
    vec_nodes[k].compute_neighbours(vec_nodes, grid);
  }

  map_paths = compute_all_paths(vec_nodes);

  while (device->run())
  {
    keyControl(receiver);
    // Work out a frame delta time.
    const u32 now = device->getTimer()->getTime();
    const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
    then = now;

    driver->beginScene(true, true, video::SColor(0, 100, 100, 100));
    hero.move();

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
