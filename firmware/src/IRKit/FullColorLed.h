/*
 Copyright (C) 2013-2014 Masakazu Ohtsuka
  
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 2 of the License, or
 (at your option) any later version.
  
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
  
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __FULLCOLORLED_H__
#define __FULLCOLORLED_H__

class FullColorLed
{
public:
    typedef enum BLINK_MODE {
        ALWAYS_ON      = 0,
        BLINK_THEN_ON  = 1,
        BLINK_THEN_OFF = 2
    };

    FullColorLed(int pinR, int pinG, int pinB);
    void setLedColor(bool colorR, bool colorG, bool colorB, BLINK_MODE blink_mode = ALWAYS_ON, uint8_t blink_timeout = 0);
    void off();
    void onTimer();

private:
    int pinR_;
    int pinG_;
    int pinB_;
    bool colorR_;
    bool colorG_;
    bool colorB_;
    BLINK_MODE blink_mode_; // defaults to ALWAYS_ON
    volatile bool blinkOn_; // altered inside timer ISR
    volatile uint8_t blink_timer_;
};

#endif // __FULLCOLORLED_H__
