#ifndef RTC_H
#define RTC_H

#include <array>

class RTC {
public:
    RTC();

    // Установка времени в формате HH:MM
    void setTime(int h, int m);

    // Запуск счёта времени
    void startClock();

    // Остановка счёта времени
    void stopClock();

    // Получение текущего времени в формате массива {H1, H0, M1, M0}
    std::array<int, 4> getTime() const;

    // Получение массива пикселей для цифры
    static const uint16_t* getDigitPixels(uint8_t digit);

private:
    int hours;
    int minutes;
    bool isRunning;

    // Увеличение минут на 1
    void incrementMinute();

    // Увеличение часов на 1
    void incrementHour();

    // Цифры для часов
    static const uint16_t digits[10][9];
};

#endif // RTC_H
