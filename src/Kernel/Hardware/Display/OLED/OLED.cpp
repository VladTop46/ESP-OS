#include "OLED.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

OLED& oledInstance = OLED::getInstance();

// Инициализация статического члена класса
OLED& OLED::getInstance() {
    static OLED instance;
    return instance;
}

// Приватный конструктор для создания экземпляра класса
OLED::OLED() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
    // Инициализация
}

void OLED::init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        Serial.println("Stopping OS initialization");
        for (;;);
    }

    oledInstance.getDisplay().display();
    delay(2000);
    oledInstance.getDisplay().clearDisplay();
}

void OLED::clearTextBuffer() {
    for (int i = 0; i < numLines; ++i) {
        textBuffer[i] = "";
    }
}

void OLED::addTextToBuffer(const String &text) {
    // Сдвигаем строки вверх
    for (int i = 0; i < numLines - 2; ++i) {
        textBuffer[i] = textBuffer[i + 1];
    }

    // Добавляем новую строку внизу
    textBuffer[numLines - 2] = text;
}

void OLED::displayTextBuffer() {
    // Очищаем дисплей перед выводом нового содержимого
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);  // Начинаем вывод с верхней части дисплея

    // Выводим строки из буфера на дисплей
    for (int i = 0; i < numLines; ++i) {
        display.println(textBuffer[i]);
    }

    // Показываем буфер дисплея на экране
    display.display();
}

void OLED::cursorBlink() {
    static bool cursorVisible = true;
    static unsigned long lastBlinkTime = 0;
    const unsigned long blinkInterval = 200;  // Интервал мигания в миллисекундах

    // Проверяем, прошло ли достаточно времени для следующего мигания
    if (millis() - lastBlinkTime >= blinkInterval) {
        lastBlinkTime = millis();  // Обновляем время последнего мигания

        // Инвертируем видимость курсора
        cursorVisible = !cursorVisible;

        // Очищаем дисплей перед каждым миганием
        display.clearDisplay();

        // Рисуем курсор, если он видим
        if (cursorVisible) {
            display.drawPixel(10, 10, SSD1306_WHITE);
            display.drawPixel(11, 10, SSD1306_WHITE);
            display.drawPixel(12, 10, SSD1306_WHITE);
            display.drawPixel(13, 10, SSD1306_WHITE);
        }

        // Показываем буфер дисплея на экране
        display.display();
    }
}

void OLED::setInputMode(bool mode) {
    inputMode = mode;
}

void OLED::updateCursor() {
    if (inputMode) {
    
        textBuffer[numLines - 1] = "esp:/$ _";
        displayTextBuffer();
        delay(500);

        textBuffer[numLines - 1] = "esp:/$ ";
        displayTextBuffer();
        delay(500);
    }
}

// Реализация нового метода для доступа к display извне
Adafruit_SSD1306& OLED::getDisplay() {
    return display;
}