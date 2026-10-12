#include "trigger.h"
#include "config/Config.h"

void TriggerClass::shoot(){
    digitalWrite(RELAY_PIN,HIGH);
    delay(3000);
    digitalWrite(RELAY_PIN,LOW);
}