#include "AppMain.h"

void AppMain(void) {
  DLogInit();
  SbusStart();
  while (1) {
    HAL_GPIO_TogglePin(LedFmu_GPIO_Port, LedFmu_Pin);
    HAL_Delay(1000);
  }
}
