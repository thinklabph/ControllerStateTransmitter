#include <DigitalIO.h>
#include <PsxControllerBitBang.h>

PsxControllerBitBang<PIN_PS2_ATT, PIN_PS2_CMD, PIN_PS2_DAT, PIN_PS2_CLK> psx;
bool have_controller = false;

void initController(){
  if (!psx.begin()) {
    DEBUG_LN(F("Controller not found!"));
    delay (300);
    have_controller = false;
    blink_pixel(RED, 50);
    return;
  }

  if (!psx.enterConfigMode ()) {
    DEBUG_LN(F("Cannot enter config mode"));
    return;
  }
    
  PsxControllerType ctype = psx.getControllerType ();
  // PGM_BYTES_P cname = reinterpret_cast<PGM_BYTES_P> (pgm_read_ptr (&(controllerTypeStrings[ctype < PSCTRL_MAX ? static_cast<byte> (ctype) : PSCTRL_MAX])));
  DEBUG(F("Dual Shock "));
  
  if (!psx.enableAnalogSticks ()) {
    DEBUG_LN(F("Cannot enable analog sticks"));
    have_controller = false;
    return;
  }
  
  if (!psx.enableAnalogButtons ()) {
    DEBUG_LN(F("Cannot enable analog buttons"));
    have_controller = false;
    return;
  }
  
  if (!psx.exitConfigMode ()) {
    DEBUG_LN(F("Cannot exit config mode"));
    have_controller = false;
    return;
  }
    
	have_controller = true;

}

bool haveController(){
  return have_controller;
}

void reuqestControllerInit(){
  have_controller = false;
}

bool psxRead(){
  return psx.read();
}

uint64_t getControllerState(){
  byte lx, ly, rx, ry;

  uint64_t controller_state=0;
  controller_state = (uint64_t) psx.getButtonWord();

  psx.getLeftAnalog(lx, ly);
  psx.getRightAnalog(rx, ry);
  controller_state <<= 8;
  controller_state += lx;
  controller_state <<= 8;
  controller_state += ly;
  controller_state <<= 8;
  controller_state += rx;
  controller_state <<= 8;
  controller_state += ry;

  return controller_state;
}