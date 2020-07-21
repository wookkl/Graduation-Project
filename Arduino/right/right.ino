#include <CapacitiveSensor.h>
#include <SoftwareSerial.h>
//define Mcp3208 Pin
#define SBUF_SIZE 64
#define SELPIN 10 //Selection Pin 
#define DATAOUT 11//MOSI 
#define DATAIN  12//MISO 
#define SPICLOCK  13//Clock
int EBimuAsciiParser(float *item, int number_of_item);
int read_adc(int channel);
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2, 3);
CapacitiveSensor   cs_5_6 = CapacitiveSensor(5, 6); 
SoftwareSerial bluetooth(4, 7);
//Flex-------------------------------------------
char rightHandFlex[6][40];  //flexData -> dtostrf
int flexData[6];            //get FlexData
//-----------------------------------------------
//Ebimu------------------------------------------
char rightHandEbimu[6][40]; //axis_6 -> sprintf
float axis_6[6];            //get 6 axis(euler, acc)
char sbuf[SBUF_SIZE];
signed int sbuf_cnt=0;
//-----------------------------------------------
long capacitor_left;
long capacitor_right;
char capacitor_buff[2][40];
char vcc_buff[40];
void setup()
{ 
  //mcp3208 + Flex
  pinMode(SELPIN, OUTPUT); 
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICLOCK, OUTPUT);
  pinMode(0,INPUT); 
  digitalWrite(SELPIN,HIGH); 
  digitalWrite(DATAOUT,LOW); 
  digitalWrite(SPICLOCK,LOW);

  //Serial
  Serial.begin(115200);
  //Bluetooth
  bluetooth.begin(115200); 
} 
void loop() 
{
   float vin = analogRead(0);
   vin = (vin * 5.0) / 1024.0;
   capacitor_left = cs_2_3.capacitiveSensorRaw(30);    // 1번 터치패드 값 수신 <접촉시 55~60의 정수값 출력>
   capacitor_right = cs_5_6.capacitiveSensorRaw(30);    // 2번 터치패드 값 수신 <접촉시 55~60의 정수값 출력> 
   int flag = 1;
   
   if(EBimuAsciiParser(axis_6,6))
   if(axis_6[3] >= 10 || axis_6[4] >= 10 || axis_6[5] >= 10) flag=0;
   
   for(int i = 0; i < 6; i++){
       flexData[i] = read_adc(i+3);
       if(i==5)flexData[i]=3000;
       sprintf(rightHandFlex[i],"%d",flexData[i]);
   }
   //Ebimu casting
   Serial.print("  6 axis : ");
   for(int i = 0; i < 6; i++){   
       dtostrf(axis_6[i],7,2,rightHandEbimu[i]);
       Serial.print(axis_6[i]); Serial.print(" ");
   }
   Serial.println(" ");  
   dtostrf(vin,7,2,vcc_buff);    
   //send Ebimu
   if(flag){
       for(int i = 0; i < 6; i++){
           bluetooth.write(rightHandEbimu[i]);
           bluetooth.write(",");
       }
       //send Flex
       for(int i = 0; i < 6; i++){
           bluetooth.write(rightHandFlex[i]);
           bluetooth.write(",");
       }
       
       //send Capacitor
       if(capacitor_left>50){
           sprintf(capacitor_buff[0],"1");
       }
       else{
           sprintf(capacitor_buff[0],"0");
       }
       if(capacitor_right>50){
           sprintf(capacitor_buff[1],"1");
       }
       else{
           sprintf(capacitor_buff[1],"0");
       }
       bluetooth.write(capacitor_buff[0]);
       bluetooth.write(",");
       bluetooth.write(capacitor_buff[1]);
       bluetooth.write(",");
       bluetooth.write(vcc_buff);
       bluetooth.write("\n");
    }
}

int read_adc(int channel)
{
    int adcvalue = 0;
    byte commandbits = B11000000;
    commandbits|=((channel-1)<<3);
    
    digitalWrite(SELPIN,LOW); 
    for (int i=7; i>=3; i--)
    {
        digitalWrite(DATAOUT,commandbits&1<<i);
        digitalWrite(SPICLOCK,HIGH);
        digitalWrite(SPICLOCK,LOW);    
    }
    digitalWrite(SPICLOCK,HIGH);    
    digitalWrite(SPICLOCK,LOW);
    digitalWrite(SPICLOCK,HIGH);  
    digitalWrite(SPICLOCK,LOW);
    for (int i=11; i>=0; i--)
    {
        adcvalue+=digitalRead(DATAIN)<<i;
        digitalWrite(SPICLOCK,HIGH);
        digitalWrite(SPICLOCK,LOW);
    }
    digitalWrite(SELPIN, HIGH); //turn off device
    return adcvalue;
}

int EBimuAsciiParser(float *item, int number_of_item)
{
    int n,i;
    int rbytes;
    char *addr; 
    int result = 0;
    
    rbytes = Serial.available();
    for(n=0;n<rbytes;n++)
    {
        sbuf[sbuf_cnt] = Serial.read();
        if(sbuf[sbuf_cnt]==0x0a)
        {
            addr = strtok(sbuf,",");
            for(i=0;i<number_of_item;i++)
            {
                item[i] = atof(addr);
                addr = strtok(NULL,",");
            }
            result = 1;
        }
        else if(sbuf[sbuf_cnt]=='*')
        {     
            sbuf_cnt=-1;
        }
 
        sbuf_cnt++;
        if(sbuf_cnt>=SBUF_SIZE) sbuf_cnt=0;
    }
    return result;
}
