#pragma once

#include <cstdint>
#if defined(_WIN32)
#include <windows.h>
#include "vjoy/inc/public.h"
#elif defined(__linux__)
typedef long LONG;
#endif

namespace D2K {namespace Input { namespace Joystick {

const uint8_t NO_JOYSTICK = 0;
const uint8_t MAX_JOYSTICKS = 4;

//bool Init(uint8_t device);
bool DeInit(uint8_t device);
bool IsActive(uint8_t device);
int Update(uint8_t device);
void SetButton(uint8_t device, uint8_t button, bool value);
void SetHat(uint8_t device, uint8_t hat, bool value);
//void UpdateHat(uint8_t device);
void SetAxisPercent(uint8_t device, uint8_t axis, uint8_t value);
void SetAxisRaw(uint8_t device, uint8_t axis, LONG value);
void SetAxisSignedMax(uint8_t device, uint8_t axis, LONG value, LONG max);
bool GetButton(uint8_t device, uint8_t button);

}}} // namespace D2K::Input::Joystick
