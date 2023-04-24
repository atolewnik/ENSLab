float static_val = 0;
int sensorValue = 0;
float EMA_a = 0.3;
int EMA_S = 0;
int highpass = 0;

void setup()
{
    Serial.begin(115200);
    EMA_S = analogRead(sensorPin); 
    Serial.print("Calibrating...");
    for (int i = 0; i <= 50; i++) {
    float val = analogRead(A0);
    static_val += val;
    Serial.print(".");
    delay(100);
  }
  
    Serial.println(static_val/50);
    
}


void loop()
{
    int val = analogRead(A0)-static_val/50;                    // get Analog value
    // Serial.println(val);
    sensorValue = analogRead(sensorPin);
    EMA_S = (EMA_a*sensorValue) + ((1-EMA_a)*EMA_S);
    highpass = sensorValue - EMA_S; 
    if(val>20){
      Serial.println("Front Wrist Movement"); 
      delay(1000);     
    }
    if(val<-20)
    {
      Serial.println("Back Wrist Movement");
      delay(500);
    }
    delay(100);
}
