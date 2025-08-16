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
        pixels.setPixelColor(0, pixels.Color(0xff, 0x14, 0x93));
        pixels.show();
        startup_reason = BD_STARTUP_NORMAL;
    }

    void onBeforeTransmit() override {
        pixels.setPixelColor(3, pixels.Color(255, 0, 0));
        pixels.show();
    }

    void onAfterTransmit() override {
        pixels.setPixelColor(3, pixels.Color(0, 0, 0));
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
