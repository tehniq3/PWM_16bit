/* http://www.arduinoslovakia.eu/blog/2017/7/16-bitove-rozlisenie-pwm-pre-arduino?lang=en
Arduino 16-bit PWM
   v. 1.0
   Copyright (C) 2017 Robert Ulbricht
   http://www.arduinoslovakia.eu
   Based on
   https://arduino.stackexchange.com/questions/12718/increase-pwm-bit-resolution
   Timer1 is set to mode 14 PWM, maximum resolution.
   Connect LED and resistor 1k to pin 10. LED flashes a bit,
   but if the 15-bit resolution is selected, the blinking disappears.
*/   
void setup() {
  Serial.begin(9600);
  setupPWM16();
}

uint16_t icr = 0xffff;


void loop() {
  Serial.println("*");
  for (uint16_t i = 0; i < 65535; i++)
  {
    analogWrite16(10, i);
    delayMicroseconds(100);
  }
delay(250);
analogWrite16(10, 0);
delay(250);
analogWrite16(10, 65535);
delay(250);
analogWrite16(10, 0);
delay(250);
  for (uint16_t j = 65535; j > 0 ; j--)
  {
    analogWrite16(10, j);
    delayMicroseconds(100);
  }
delay(250);
analogWrite16(10, 65535);
delay(250);
analogWrite16(10, 0);
delay(250);
analogWrite16(10, 65535);
delay(250);

}

void setupPWM16() {
  DDRB  |= _BV(PB1) | _BV(PB2);       /* set pins as outputs */
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                 /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS10);                  /* prescaler 1 */
  ICR1 = icr;                         /* TOP counter value (freeing OCR1A*/
}

/* Comments about the setup
  Changing ICR1 will effect the amount of bits of resolution.
  ICR1 = 0xffff; (65535) 16-bit resolution
  ICR1 = 0x7FFF; (32767) 15-bit resolution
  ICR1 = 0x3FFF; (16383) 14-bit resolution etc....
  Changing the prescaler will effect the frequency of the PWM signal.
  Frequency[Hz}=CPU/(ICR1+1) where in this case CPU=16 MHz
  16-bit PWM will be>>> 16000000/(65535+1)=244,14Hz
*/

/* 16-bit version of analogWrite(). Works only on pins 9 and 10. */
void analogWrite16(uint8_t pin, uint16_t val)
{
  switch (pin) {
    case  9: OCR1A = val; break;
    case 10: OCR1B = val; break;
  }
}
