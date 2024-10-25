#pragma once

#include "kxnTask.h"

DEFINE_TASK_STATE(button){
    button_ON,
    button_OFF,
};

CREATE_TASK(button)
/*Add your variable here*/

void setup()
{
    /*Add your code setup here*/
    stop();
}

void loop()
{
    switch (getState())
    {
    case button_ON:
        /*code*/
        kDelay(0);
        setState(button_OFF);
        break;

    case button_OFF:
        /*code*/
        kDelay(0);
        setState(button_ON);
        break;

    default:
        break;
    }
}

void start()
{
    kxnTaskManager.add(this);
    setState(button_ON);
}

void stop()
{
    kDelay(0);
    setStateIdle();
}

END