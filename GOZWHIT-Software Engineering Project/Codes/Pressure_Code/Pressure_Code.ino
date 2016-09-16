#include<SoftwareSerial.h>

SoftwareSerial btconnect(5,6);
char datain;
char dataout;
int sensor_pin1=A0;
int sensor_pin2=A2;
int sensor_pin3=A4;
int pin1=8;
int pin2=9;
int pin3=10;
int sensor_value1;
int sensor_value2;
int sensor_value3;

void setupBlueToothConnection()
{
// btconnect.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
 btconnect.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
 btconnect.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
 btconnect.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
 btconnect.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
 delay(2000); // This delay is required.
 btconnect.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
 Serial.println("The slave bluetooth is inquirable!");
 delay(2000); // This delay is required.
 btconnect.flush();
}

void setup()
{
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  digitalWrite(pin3,HIGH);
  /*pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);*/
  pinMode(sensor_pin1,INPUT);
  pinMode(sensor_pin2,INPUT);
  pinMode(sensor_pin3,INPUT);
  setupBlueToothConnection();
  Serial.begin(57600);
  btconnect.begin(57600);
}

void loop()
{
  sensor_value1=analogRead(sensor_pin1);
  sensor_value2=analogRead(sensor_pin2);
  sensor_value3=analogRead(sensor_pin3);
  Serial.println(sensor_value1);
  //Serial.print(" " );
  //Serial.print(sensor_value2);
  //Serial.print(" ");
  //Serial.println(sensor_value3);
  if(sensor_value1>=15)
  {
    btconnect.print('A');
    btconnect.print('C');
    btconnect.print('C');
    btconnect.print('I');
    btconnect.print('D');
    btconnect.print('E');
    btconnect.print('N');
    btconnect.print('T');
  delay(300000);
  }
  delay(100);
}

