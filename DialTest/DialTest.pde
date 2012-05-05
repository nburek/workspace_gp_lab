#include <WidgetShield.h>
#include <Widget.h>
#include <DialWidget.h>
#include <ProgressBarWidget.h>
#include <LightWidget.h>

#define TIME_TO_WAIT 0
long lastSendTime = 0;
int fakePotVal = 0;

DialWidget dial1(85, 65, 0);
ProgressBarWidget pbar(150, 150, 0);

LightWidget led1(190, 40, 0);
LightWidget led2(210, 40, 0);
LightWidget led3(230, 40, 0);
LightWidget led4(250, 40, 0);
LightWidget led5(270, 40, 0);
LightWidget led6(290, 40, 0);
LightWidget led7(310, 40, 0);
LightWidget led8(330, 40, 0);

LightWidget led9(190, 60, 0);
LightWidget led10(210, 60, 0);
LightWidget led11(230, 60, 0);
LightWidget led12(250, 60, 0);

void setup(){
  Serial.begin(9600);
 WidgetShield* wC = WidgetShield::Instance();
 wC->resetWidgetShield();

 wC->addWidget(&dial1);
/* wC->addWidget(&led1);
 wC->addWidget(&led2);
 wC->addWidget(&led3);
 wC->addWidget(&led4);
 wC->addWidget(&led5);
 wC->addWidget(&led6);
 wC->addWidget(&led7);
 wC->addWidget(&led8);
 wC->addWidget(&led9);
 wC->addWidget(&led10);
 wC->addWidget(&led11);
 wC->addWidget(&led12);*/

 wC->addWidget(&pbar);
 
}
  
  
void loop()
{
  if ((millis()-lastSendTime) > TIME_TO_WAIT)
  {
    lastSendTime = millis();
    int potVal = (fakePotVal++);//analogRead(0);
    if (fakePotVal==1024) fakePotVal = 0;
    int potVal2 = potVal;
    
    potVal = map(potVal, 0, 1023, 0, 359);
    dial1.redrawNeedle(potVal);
    
    potVal2 = map(potVal2, 0, 1023, 0, 100);
    pbar.redrawBar(potVal2);

  /*  led1.changeStatus();
    led2.changeStatus();
    led3.changeStatus();
    led4.changeStatus();
    led5.changeStatus();
    led6.changeStatus();
    led7.changeStatus();
    led8.changeStatus();
    led9.changeStatus();
    led10.changeStatus();
    led11.changeStatus();
    led12.changeStatus();*/
    
  }
}  
    
    
    
    
    
    
  
