#include <Arduino.h>
#include "application/Application.h"

Application application;

void setup()
{
  application.begin();
}

void loop()
{
  application.update();
}