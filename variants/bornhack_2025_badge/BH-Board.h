#pragma once

#include <RadioLib.h>
#include <MeshCore.h>
#include <helpers/radiolib/RadioLibWrappers.h>
#include <helpers/radiolib/CustomSX1262Wrapper.h>
#include <helpers/SensorManager.h>
#include <helpers/ESP32Board.h>
#include <Adafruit_NeoPixel.h>

class BornhackBadge2025 : public ESP32Board {
protected:
    uint8_t startup_reason;
    Adafruit_NeoPixel pixels;   // declare here

public:
    // constructor: initialize NeoPixel with pin & count
    BornhackBadge2025()
      : pixels(5, 0, NEO_GRB + NEO_KHZ800) {}

    void begin() {
        pixels.begin();
        pixels.setBrightness(25);
        pixels.setPixelColor(0, pixels.Color(0xff, 0x14, 0x93));
        pixels.show();
#if defined(PIN_BOARD_SDA) && defined(PIN_BOARD_SCL)
#if PIN_BOARD_SDA >= 0 && PIN_BOARD_SCL >= 0
        Wire.begin(PIN_BOARD_SDA, PIN_BOARD_SCL);
#endif
#endif
        startup_reason = BD_STARTUP_NORMAL;
    }

    void setHasConnection(bool connected) {
        if (connected)
            pixels.setPixelColor(2, pixels.Color(0x00, 0xff, 0x00));
        else
            pixels.setPixelColor(2, pixels.Color(0x00, 0x00, 0x00));

    }

    void messageCount(int msgcount) {
        if (msgcount > 0) {
            pixels.setPixelColor(4, pixels.Color(0x00, 0xff, 0x00));
        } else {
            pixels.setPixelColor(4, pixels.Color(0x00, 0x00, 0x00));
        }
        pixels.show();
    }

    void onBeforeTransmit() override {
        pixels.setPixelColor(3, pixels.Color(255, 0, 0));
        pixels.show();
    }

    void onAfterTransmit() override {
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
    }

    void onRadioIdle() override {
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
        pixels.show();
    }

    void onRadioStartReceive() override {
        pixels.setPixelColor(3, pixels.Color(0, 255, 0));
        pixels.show();
    }

    const char* getManufacturerName() const override {
        return "BornHack Badge 2025";
    }

    uint8_t getStartupReason() const override {
        return startup_reason;
    }

    void reboot() override {
        esp_restart();
    }
};
