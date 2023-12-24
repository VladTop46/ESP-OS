#ifndef RTC_H
#define RTC_H

#include <array>
#include <thread>

class RTC {
public:
    // Получение единственного экземпляра класса
    static RTC& getInstance();

    // Установка времени в формате HH:MM
    void setTime(int h, int m);

    // Запуск счёта времени
    void startClock();

    // Остановка счёта времени
    void stopClock();

    // Получение текущего времени в формате массива {H1, H0, M1, M0}
    std::array<int, 4> getTime() const;

private:
    RTC(); // Закрытый конструктор для предотвращения создания экземпляров извне

    int hours;
    int minutes;
    bool isRunning;
    std::thread clockThread;

    // Увеличение минут на 1
    void incrementMinute();

    // Увеличение часов на 1
    void incrementHour();
};

#endif // RTC_H
