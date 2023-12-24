#include "RTC.h"
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

RTC& rtc = RTC::getInstance();

RTC& RTC::getInstance() {
    static RTC instance;
    return instance;
}

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

    // Запускаем отдельный поток для счета времени
    clockThread = std::thread([this]() {
        while (isRunning) {
            std::this_thread::sleep_for(std::chrono::milliseconds(60000));  // Засыпаем на минуту в миллисекундах
            incrementMinute();
        }
    });
}

// Остановка счёта времени
void RTC::stopClock() {
    isRunning = false;

    // Дожидаемся завершения потока
    if (clockThread.joinable()) {
        clockThread.join();
    }
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
