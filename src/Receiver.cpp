#include "Receiver.hpp"
#include "hero.hpp"
#include "world.hpp"

extern irr::video::IVideoDriver *driver;
extern irr::scene::ISceneManager *smgr;
extern irr::IrrlichtDevice *device;
extern Hero hero;
extern World world;

float x_souris;
float y_souris;
bool is_right_click_up;
bool is_left_click_up = true;

// This is the one method that we have to implement
bool Receiver::OnEvent(const irr::SEvent &event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {

        KeyIsDown[irr::KEY_LBUTTON] = event.MouseInput.isLeftPressed();

        KeyIsDown[irr::KEY_RBUTTON] = event.MouseInput.isRightPressed();

        y_souris = event.MouseInput.X;
        x_souris = event.MouseInput.Y;
    }

    return false;
}

// This is used to check whether a key is being held down
bool Receiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

Receiver::Receiver()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

void keyControl(Receiver receiver)
{
    hero.direction(irr::core::vector3df(y_souris, hero.position().Y, x_souris) - hero.position());
    if (receiver.IsKeyDown(irr::KEY_RBUTTON))
    {
        if (is_right_click_up)
        {
            hero.compute_movements(x_souris, y_souris);
            is_right_click_up = false;
        }
    }
    else
    {
        is_right_click_up = true;
    }

    if (receiver.IsKeyDown(irr::KEY_LBUTTON))
    {
        if (is_left_click_up)
        {
            Projectile *proj_ptr = new Projectile;
            *proj_ptr = hero.shoot();
            world.addProjectile(proj_ptr);
            is_right_click_up = false;
        }
    }
    else
    {
        is_right_click_up = true;
    }

    if (receiver.IsKeyDown(irr::KEY_ESCAPE))
    {
        device->closeDevice();
    }
    else if (receiver.IsKeyDown(irr::KEY_KEY_Q))
    {
        device->closeDevice();
    }
}