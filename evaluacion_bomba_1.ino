#include <LiquidCrystal.h>

const int rs = 4, en = 6, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
const int UP = 3, DOWM = 2, ARM = 5, LED = 12;

boolean eARM=false,eUP=false,eDOWM=false,eLED=false;
boolean rARM,rUP,rDOWM;

boolean armada=false;

long t,t_tarea2=0,t_tarea1=0;

int conteo=20;

const String vpUP="UP ",vpDOWM="DOWM ", vpARM="ARM ";
String PASSWORD = "DOWM UP DOWM DOWM UP ARM ",sPASSWORD="";

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  // INICIALIZO LCD 16X2
  lcd.begin(16,2);
  
  // INCIANDO MODO CONFIGURACION
  ModoConfig();
  
  //DECLARO LOS BOTONES UP, DOWM Y ARM
  pinMode(UP,INPUT);
  pinMode(DOWM,INPUT);
  pinMode(ARM,INPUT);
  
}

void ModoConfig()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Modo Config");
  lcd.setCursor(0,1);
  lcd.print(conteo);
  lcd.setCursor(4,1);
  lcd.print("Segundos");
}

void CuantaRegre()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Esto Exprotara!!");
  lcd.setCursor(0,1);
  lcd.print(conteo);
  lcd.setCursor(4,1);
  lcd.print("Segundos");
}

void notificacion1()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Bomba Desarmada");
  lcd.setCursor(0,1);
  lcd.print(conteo);
  lcd.setCursor(4,1);
  lcd.print("Segundos");
}

void notificacion2()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BOOOOOOMMM");
}

void Tarea1()
{
  t=micros();
  if(conteo>1)
  {
    if((t-t_tarea1)>(1000000))// 1000000uS = 1S = 1000mS
    {
      t_tarea1=t;
      conteo=conteo-1;
      CuantaRegre();
    }
  }
  else
  {
    if(conteo!=0)
    {
      conteo=conteo-1;
      CuantaRegre();
      delay(500);
      notificacion2();
    }
  }
}

void Tarea2()
{
  t=micros();
  if((t-t_tarea2)>(500000))// 500000uS = 500mS
  {
    t_tarea2=t;
    digitalWrite(LED,eLED);
    eLED=!(eLED);
  }
}

void BotonUP()
{
  eUP=digitalRead(UP);// 0 // 1 // 1 // 0
  if(rUP!=eUP)// 0 != 0 // 0 != 1 // 1 != 1 // 0 != 1
  {
    if(eUP)//   // 1 //  //  //
    {
      //ejecucion
      if(10<=conteo && conteo<60 && !(armada)) // 10<=conteo<=60
      {
        conteo=conteo+1; // 20 // 21 //  //  
        ModoConfig();
      }
      if(armada)
      {
        sPASSWORD=sPASSWORD+vpUP;// concatenar
      }
    }
  } 
  rUP=eUP;// 0 // 1 // 1 // 0
}

void BotonDOWM()
{
  eDOWM=digitalRead(DOWM);
  if(rDOWM!=eDOWM)
  {
    if(eDOWM)
    {
      //ejecucion
      if(10<conteo && conteo<=60 && !(armada)) // 10<=conteo<=60
      {
        conteo=conteo-1; // 20 // 21 //  //  
        ModoConfig();
      }
      if(armada)
      {
        sPASSWORD=sPASSWORD+vpDOWM;// concatenar
      }
      
    }
  } 
  rDOWM=eDOWM;
}

boolean password(String pass, String Spass)
{
  if(PASSWORD==sPASSWORD)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void BotonARM()
{
  eARM=digitalRead(ARM);
  if(rARM!=eARM)
  {
    if(eARM)
    {
      //ejecucion
      armada=true;
      if(armada)
      {
        sPASSWORD=sPASSWORD+vpARM;// concatenar
        if(password(PASSWORD,sPASSWORD))
        {
          armada=false;
          notificacion1();
          delay(1000);
          conteo=20;
          ModoConfig();
        }
        else
        {
          sPASSWORD="";
        }
      }
    }
  } 
  rARM=eARM;
}


void loop()
{
  BotonUP();
  BotonDOWM();
  BotonARM();

  Tarea2();
  if(armada)
  {
    Tarea1();
  }
  
}