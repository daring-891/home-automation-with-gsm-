
//temporary variable to store the contents of the received sms

char temp[50];
int m;
int inByte =0;        
void setup()
{
  // initialize serial communication with baud rate of 9600 bps
  Serial.begin(9600);
  // wait for a while till the serial port is ready
  delay(100);
// configure the gsm modemin sms mode   
  Serial.print("AT+CMGF=1\r");
  delay(500);
 // route the contents of the received sms on to serial port
  Serial.print("AT+CNMI=2,2,0,0,0\r");
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  // make default status of pin 2 and 3 low
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(500);
}
//  loop function starts here
void loop()
{
  // clear the temporary variable temp
    m=0;
    for(m=0;m<45;m++)
      {
        temp[m]=0;
      }
   // wait for the reception of the message
   // " is a identifier for the start of the message
    do
    {
        while ( !Serial.available() );   
    } while ( '"' != Serial.read() );

   // read the sms which will have date, time, sms body and the senders number
      for(m=0;m<45;m++)
      {
        while ( !Serial.available() );
        inByte = Serial.read();
        temp[m]=inByte;
      }
  //now write different conditions and required actions
    
    /*codes are
     D1N----------device 1 on
     D1F----------device 1 off
     D2N----------device 2 on
     D2F----------device 2 off
     DAN----------all devices on
     DAF----------all devices off 
     */    
     // device 1 is connected to pin 2 and device 2 is connected to pin 3 of the arduino
   
      if(temp[42]=='O' )
      {
        digitalWrite(2,HIGH);
      
      }
     
      if(temp[42]=='F' )
      {
        digitalWrite(2,LOW);
       }
     
     
      delay(1500); // give some delay before the next cycle starts
}

