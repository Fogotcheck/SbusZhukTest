#include "Sbus.h"
uint8_t SynchBuf[128] = {0};

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart8;

uint8_t buf[2][128] = {0};
uint8_t count[2] = {1, 1};

int SbusStart(void) {
  int ret = 0;
  if (HAL_UART_Receive_IT(&huart2, &buf[0][0], 1) != HAL_OK) {
    ret = -1;
  }
  if (HAL_UART_Receive_IT(&huart3, &buf[1][0], 1) != HAL_OK) {
    ret = -1;
  }

  return ret;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart == &huart3) {
    SbusFrame_t *frame3 = (SbusFrame_t *)buf[1];
    if (frame3->head != SBUS_CONST_HEAD) {
      count[1] = 0;
    } else {
      if (count[1] >= sizeof(SbusFrame_t)) {
        if (frame3->tail == 0) {
          count[1] = 0;

        }
        count[1] = 0;
      }
    }

    if (count[1] >= sizeof(buf[1])) {
      count[1] = 0;
    }
    HAL_UART_Receive_IT(&huart3, &buf[1][count[1]++], 1);
    return;
  }
  if (huart == &huart2) {
    if (count[0] >= sizeof(buf[1])) {
      count[0] = 0;
    }
    HAL_UART_Receive_IT(&huart3, &buf[1][count[0]++], 1);
    return;
  }
}
