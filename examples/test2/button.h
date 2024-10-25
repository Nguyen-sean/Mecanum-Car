#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(button){
    button_ON,
    button_OFF,
};

CREATE_TASK(button)

typedef enum { ON = 20, OFF,} buttonState;
byte strg_bt = 0;
uint8_t output_data = 0;

void setup()
{
    this->resetData();
}

void loop()
{
    switch (getState())
    {
    case button_ON:

        if (this->strg_bt == 1)
            this->output_data = ON;
        else
            this->output_data = OFF;

        kDelay(0);

        setState(button_OFF);

        break;

    case button_OFF:
        this->stop();
        kDelay(0);
        break;

    default:
        break;
    }
}

void read_Button(byte inButton)
{
    this->strg_bt = inButton;
    this->stop();
}

void stop()
{
    kDelay(0);
    setStateIdle();
}

void resetData()
{
    this->stop();
    this->output_data = 0;
    this->strg_bt = 0;
    kDelay(0);
    setStateIdle();
}
uint8_t get_bt_Stt()
{
    kxnTaskManager.add(this);
    setState(button_ON);
    return this->output_data;
}
END