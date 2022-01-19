// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>

double cm = 0.0;
double inches = 0.0;

int trigPin = D4;
int echoPin = D5;

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin, 0.0, 100.0);

int btn=D2;
int btnstate=0;
bool flag=0;
int pos=0;

int hora=00;
int minuto=13;

Servo servo;

void setup() {
    Serial.begin(9600);
    Spark.variable("cm", &cm, DOUBLE);
    Spark.variable("inches", &inches, DOUBLE);
    
    pinMode(D3, OUTPUT);
    pinMode(D1, INPUT_PULLUP);
    pinMode(btn, INPUT_PULLUP);
    
    Particle.function("led", ledFunction);
    //Particle.function("led", sensor);
    Particle.syncTime();
    Time.zone(-6);
    
    servo.attach(D3);
    servo.write(180);
    delay(1000);
    servo.detach();

}

int ledFunction(String parametro){
    if(parametro.equalsIgnoreCase("on") && (cm > 24.0) && (cm < 100.0)){
        servo.attach(D3);
        servo.write(0);
        return 1;
        delay(1000);
        servo.detach();
    }
    else if(parametro.equalsIgnoreCase("on") && (cm <= 24.0) && (cm >= 0.0)){
        servo.attach(D3);
        servo.write(0);
        return 2;
        delay(1000);
        servo.detach();
    }
    else if(parametro.equalsIgnoreCase("off") && (cm <= 24.0) && (cm >= 0.0)){
        servo.attach(D3);
        servo.write(180);
        return 3;
        delay(1000);
        servo.detach();
    }
    else if(parametro.equalsIgnoreCase("off") && (cm > 24.0) && (cm < 100.0)){
       servo.attach(D3);
       servo.write(180);
       return 0;
       delay(1000);
       servo.detach();
    }
    else{
        servo.attach(D3);
       servo.write(180);
       return -1;
       delay(1000);
       servo.detach();
    }
}
    
void loop() {
    if(digitalRead(D1)==LOW){
        if(flag == 0){
            pos = 0;
            flag = -1;
        }else if(flag==1){
            pos=180;
            flag=0;
        }
        servo.attach(D3);
        servo.write(pos);
        delay(1000);
        servo.detach();
    }
    if(Time.hour() == hora && Time.minute() == minuto){
            servo.attach(D3);
            servo.write(0);
            delay(1000);
            servo.detach();
            delay(60000);
        }
        
    cm = rangefinder.getDistanceCM();
    inches = rangefinder.getDistanceInch();
    delay(1000);
    
    Serial.print("Centimetros: ");
    Serial.println(cm);
    Serial.print("Pulgadas: ");
    Serial.println(inches);
    Serial.println(" ");
    delay(1000);
}