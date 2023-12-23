#include "RTC.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

RTC::RTC() : hours(0), minutes(0), isRunning(false) {}

// Установка времени в формате HH:MM
void RTC::setTime(int h, int m) {
    if (h >= 0 && h < 24 && m >= 0 && m < 60) {
        hours = h;
        minutes = m;
    } else {
        std::cerr << "Invalid time format\n";
    }
}

// Запуск счёта времени
void RTC::startClock() {
    isRunning = true;

    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::minutes(1));  // Засыпаем на минуту
        incrementMinute();
    }
}

// Остановка счёта времени
void RTC::stopClock() {
    isRunning = false;
}

// Увеличение минут на 1
void RTC::incrementMinute() {
    minutes++;

    if (minutes == 60) {
        minutes = 0;
        incrementHour();
    }
}

// Увеличение часов на 1
void RTC::incrementHour() {
    hours++;

    if (hours == 24) {
        hours = 0;
    }
}

// Получение текущего времени в формате массива {H1, H0, M1, M0}
std::array<int, 4> RTC::getTime() const {
    return {hours / 10, hours % 10, minutes / 10, minutes % 10};
}

// Цифры для часов

// Массивы пикселей для каждой цифры
const uint16_t RTC::digits[10][9] = {
    {0xFFFF, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0x8001, 0xFFFF}, // 0
    {0x0000, 0x0002, 0x0002, 0xFFFF, 0xFFFF, 0xFFFF, 0x0002, 0x0002, 0x0000}, // 1
    {0x8002, 0xC001, 0xA001, 0x9001, 0x8801, 0x8401, 0x8201, 0x8101, 0xFFFF}, // 2
    {0x4001, 0x8001, 0x8001, 0x8101, 0x8201, 0x8401, 0x8801, 0x4001, 0xFFFF}, // 3
    {0x0001, 0x0001, 0x0001, 0x0001, 0xFFFF, 0xFFFF, 0x0001, 0x0001, 0x0001}, // 4
    {0x4001, 0x8801, 0x8401, 0x8201, 0x8101, 0x9001, 0xA001, 0xC001, 0x8002}, // 5
    {0xFFFF, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0xFFFF}, // 6
    {0x8001, 0x8001, 0x8001, 0x8001, 0xFFFF, 0xFFFF, 0x8001, 0x8001, 0x8001}, // 7
    {0xFFFF, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0xFFFF}, // 8
    {0x0001, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0x8101, 0xFFFF}  // 9
};

// Получение массива пикселей для цифры
const uint16_t* RTC::getDigitPixels(uint8_t digit) {
    return digits[digit];
}
