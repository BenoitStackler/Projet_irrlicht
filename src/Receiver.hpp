#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <irrlicht.h>
#include <iostream>

class Receiver : public irr::IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent &event);

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;

    Receiver();

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

void keyControl(Receiver receiver);
#endif
