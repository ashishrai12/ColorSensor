int s0=4,s1=5,s2=6,s3=7,out=2;
int IR=8;
int red=0,blue=0,green=0,mv=0;
int M1=10,M2=11,N1=12,N2=13,running=1;
int Gnd1=14,Gnd2=15,Gnd3=16,Vcc1=17,Vcc2=18,Vcc3=19;
int counter=0;

void setup()
{
     
     pinMode(s0,OUTPUT);
     pinMode(s1,OUTPUT); 
     pinMode(s2,OUTPUT);
     pinMode(s3,OUTPUT);
     pinMode(Gnd1,OUTPUT);
     pinMode(Gnd2,OUTPUT);
     pinMode(Gnd3,OUTPUT);
     pinMode(Vcc1,OUTPUT);
     pinMode(Vcc2,OUTPUT);
     pinMode(Vcc3,OUTPUT);
     
     pinMode(IR,INPUT);
     
     digitalWrite(s0,HIGH);
     digitalWrite(s1,HIGH);
     digitalWrite(s2,LOW);
     digitalWrite(s3,LOW);
     digitalWrite(Gnd1,LOW);
     digitalWrite(Gnd2,LOW);
     digitalWrite(Gnd3,LOW);
     digitalWrite(Vcc1,HIGH);
     digitalWrite(Vcc2,HIGH);
     digitalWrite(Vcc3,HIGH);
    
     attachInterrupt(0, ISR_INT0, CHANGE);
}

void loop()
{   
      counter=0;
      digitalWrite(s2,HIGH);
      digitalWrite(s3,HIGH);   
      delay(2);  
      green=counter;
      counter=0;
      digitalWrite(s2,LOW);
      digitalWrite(s3,HIGH);  
      delay(2);
      blue=counter;      
      counter=0;   
      digitalWrite(s2,LOW);
      digitalWrite(s3,LOW);
      delay(2);
      red=counter;
      counter=0;  
      
      mv=max(red,max(blue,green));
      red=map(red,0,mv,0,255);
      blue=map(blue,0,mv,0,255);
      green=map(green,0,mv,0,255);
      
      if(running == 1) //RUNNING
      {
        if(digitalRead(IR) == LOW)
        {
          digitalWrite(M1,HIGH);
          digitalWrite(M2,LOW);
          digitalWrite(N1,LOW);
          digitalWrite(N2,HIGH);
          delay(10);
        }
    
        else
        {
          digitalWrite(M1,HIGH);
          digitalWrite(M2,LOW);
          digitalWrite(N1,HIGH);
          digitalWrite(N2,LOW);
        }
      }
    
      else //STOPPED
      {
        digitalWrite(M1,LOW);
        digitalWrite(M2,LOW);
        digitalWrite(N1,LOW);
        digitalWrite(N2,LOW);
      }
      
      if(green>100&&green<150&&blue>80&&blue<100) //threshold for RED
        running=0;
      if(green>150&&blue>105) //threshold for GREEN
        running=1;
} 
 
void ISR_INT0()
{
       counter++;
} 