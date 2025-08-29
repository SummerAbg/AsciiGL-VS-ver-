#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>

namespace AsciiTools {
#include <Xinput.h>
// Joystick的功能原本是要管理多手柄下的控制，但我太懒了，暂且先封装一个手柄使用情况下的api
class Joystick {
public:
  using KeyMapping = std::pair<DWORD, std::function<void()>>;
  using KeyMappings = std::vector<KeyMapping>;
  using pKeyMappings = std::unique_ptr<KeyMappings>;

  Joystick() {
    this->key_stroke = new XINPUT_KEYSTROKE();
    this->key_map = std::make_unique<KeyMappings>();
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
  }

  // 检测有无可用的Xinput设备
  //  若成功，返回true并传递state值和index值
  //  若失败，返回false并不对state进行修改，index默认为0
  bool detectXinputDevice() {
    for (index = 0; index < XUSER_MAX_COUNT; index++) {
      if (XInputGetState(index.load(), &state) == ERROR_SUCCESS) {
        return true;
      }
    }
    return false;
  }

  void onJoystickVibration() {
    vibration.wLeftMotorSpeed = 32000;  // use any value between 0-65535 here
    vibration.wRightMotorSpeed = 16000; // use any value between 0-65535 here
    XInputSetState(index, &vibration);
  }

  void offJoystickVibration() {
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(index, &vibration);
  }

  int getJoystickIndex() const { return index.load(); }

  void keyFunctionMapping(const KeyMappings &mapping) {
    *this->key_map = mapping;
  }

  // 按键功能绑定
  // 先判断key_map有没有同键对象。若有，修改其值；若全无，额外添加
  void keyFunctionMapping(const KeyMapping &mapping) {
    for (auto &index : *key_map) {
      if (index.first == mapping.first) {
        index.second = mapping.second;
        return;
      }
    }
    this->key_map->push_back(mapping);
  }

  void update() {
    const DWORD error_code = XInputGetKeystroke(index.load(), 0, key_stroke);
    if (error_code == ERROR_EMPTY || error_code == ERROR_DEVICE_NOT_CONNECTED)
      return;

    const DWORD key_button = key_stroke->VirtualKey;
    if (key_stroke->Flags != XINPUT_KEYSTROKE_KEYDOWN)
      return;

    for (const auto &index : *key_map) {
      if (key_button == index.first)
        index.second();
    }
  }

private:
  pKeyMappings key_map;
  PXINPUT_KEYSTROKE key_stroke;
  XINPUT_STATE state;
  XINPUT_VIBRATION vibration;
  std::atomic<int> index; // 可用的其中一个设备的编号
};
} // namespace AsciiTools