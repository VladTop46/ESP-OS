#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef OLED_H
#define OLED_H

class OLED {
public:
    static OLED& getInstance();  // Метод для получения единственного экземпляра класса

    void init();
    void clearTextBuffer();
    void addTextToBuffer(const String &text);
    void displayTextBuffer();
    void cursorBlink();
    void setInputMode(bool mode);
    void updateCursor();

    Adafruit_SSD1306& getDisplay();

    // Удаление конструкторов и операторов присваивания для предотвращения создания копий
    OLED(const OLED&) = delete;
    OLED& operator=(const OLED&) = delete;

private:
    // Приватный конструктор для предотвращения создания экземпляров вне класса
    OLED();

    static const int numLines = 8;
    String textBuffer[numLines - 1];

    String cursorLine; // ???

    Adafruit_SSD1306 display;
    bool inputMode;

    /*
    
    String cursorLine не используется в коде вообще, но при этом контроллер выдаёт ошибку:
    Guru Meditation Error: Core  1 panic'ed (LoadStoreError). 
    при отсутствии переменной. Ошибка также возникает если переменная cursorLine инициализируется до display.
    
    */

    // Другие приватные члены класса, если нужны
};

#endif