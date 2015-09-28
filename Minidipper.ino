char tempString[10];  // Will be used with sprintf to create strings

void setup()
{
    
    Serial.begin(9600);

    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);

    clearDisplay();  
}

void loop()
{
    bool pin5 = digitalRead(5);
    bool pin6 = digitalRead(6);
    bool pin7 = digitalRead(7);
    bool pin8 = digitalRead(8);
    bool pin9 = digitalRead(9);
    bool pin10 = digitalRead(10);

    uint16_t level = 0;
    level = (!pin10 << 0) + (!pin7 << 1) + (!pin5 << 2) + (!pin9 << 3) + (!pin6 << 4) + (!pin8 << 5);
    
    if (level > 62)
    {
        Serial.print("-GO-");
        setDecimals(0b00000000);
    }
    else
    {
        level *= 5;
        sprintf(tempString, "%04d", level);
        Serial.print(tempString);
        setDecimals(0b00000001);
    }
    

    delay(100);  // This will make the display update at 10Hz.
}

void clearDisplay()
{
    Serial.write(0x76);  // Clear display command
}

void setDecimals(byte decimals)
{
    Serial.write(0x77);
    Serial.write(decimals);
}
