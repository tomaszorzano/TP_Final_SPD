#include <LiquidCrystal.h>

#define BUTTON_RIGHT 0
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_LEFT 3
#define BUTTON_SELECT 4
#define BUTTON_NONE 5
#define DATANONE 1


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int bitDato1= -1,bitDato2= -1,bitDato3= -1,bitDato4= -1;
int bitParidad1 = 0,bitParidad2 = 0,bitParidad3 = 0,bitParidad4 = 0;

int pasoss = 0;
int valido = 0;
int dataSelect = 1;
int posicion = 1;


int readButtons();
void comienzo();
void setDate();
void showDate();
void validar();
void Hamming();
void mostrarHamming(); 


void setup()
{
  lcd.begin(16, 2); 
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

int previousButton = BUTTON_NONE;
void loop()
{
   int currentButton = readButtons();
   if(currentButton==BUTTON_SELECT && previousButton==BUTTON_NONE){
       pasoss++;
       if (pasoss == 3)
       {
        pasoss = 0;
       }
   }
   previousButton = currentButton;
   switch (pasoss)
   {
   case 0:
       comienzo();
       break;
   case 1:
       showDate();
       setDate();
       break;
   case 2:
       validar();
       Hamming();
       mostrarHamming();
       break;
   }
}


int readButtons()
{
    int value = analogRead(0);
    if (value > 900)
        return BUTTON_NONE;
    if (value < 50)
        return BUTTON_RIGHT;
    if (value < 250)
        return BUTTON_UP;
    if (value < 450)
        return BUTTON_DOWN;
    if (value < 650)
        return BUTTON_LEFT;
    if (value < 850)
        return BUTTON_SELECT;
    return BUTTON_NONE; 
}


void comienzo()
{
  lcd.setCursor(0, 0);
  lcd.print("Presione Select");
  bitDato1 = -1;
  bitDato2 = -1;
  bitDato3 = -1;
  bitDato4 = -1;
  bitParidad1 = 0;
  bitParidad2 = 0;
  bitParidad3 = 0;
  bitParidad4 = 0;
  dataSelect = 1;
}


void showDate()
{
  lcd.setCursor(0,0);
  lcd.print(" ");
  lcd.setCursor(0,1);
  lcd.print("          ");
    lcd.setCursor(1, 0);
    if (bitDato1 == -1)
    {
       lcd.print("*");
    } else
    {
      lcd.print(bitDato1);
    }
    if ( bitDato2 == -1)
    {
      lcd.print("*");
    }else
    {
      lcd.print(bitDato2);
    }
    if (bitDato3 == -1)
    {
      lcd.print("*");
    } else
    {
      lcd.print( bitDato3);
    }
    if ( bitDato4 == -1)
    {
      lcd.print("*");
    } else
    {
      lcd.print( bitDato4);
    }
    lcd.print("             ");
    lcd.setCursor(dataSelect, 1);
    lcd.print("^");
}


int previousButtonData = BUTTON_NONE;
void setDate()
{
    int currentButton = readButtons();
    if (previousButtonData == BUTTON_NONE && currentButton != BUTTON_NONE)
    {
        switch (currentButton)
        {
        case BUTTON_UP:
            switch (dataSelect)
            {
              case 1:
                 bitDato1++;
                if ( bitDato1 == 2)
                 bitDato1 = 0;
                break;
              case 2:
                 bitDato2++;
                if ( bitDato2 == 2)
                 bitDato2 = 0;
                break;
              case 3:
                 bitDato3++;
                if ( bitDato3 == 2)
                 bitDato3 = 0;
                break;
              case 4:
                 bitDato4++;
                if ( bitDato4 == 2)
                 bitDato4 = 0;
                break;
            }
           break;
        case BUTTON_DOWN:
            switch (dataSelect)
            {
              case 1:
                 bitDato1--;
                if ( bitDato1 == -2)
                {
                  bitDato1 = 1;
                } else if (bitDato1 == -1)
                {
                  bitDato1 = 1;
                }
                break;
              case 2:
                bitDato2--;
                if (bitDato2 == -2)
                {
                  bitDato2 = 1;
                } else if (bitDato2 == -1)
                {
                  bitDato2 = 1;
                }
                break;
              case 3:
                bitDato3--;
                if (bitDato3 == -2)
                {
                  bitDato3 = 1;
                } else if (bitDato3 == -1)
                {
                  bitDato3 = 1;
                }
                break;
              case 4:
                bitDato4--;
                if (bitDato4 == -2)
                {
                  bitDato4 = 1;
                } else if (bitDato4 == -1)
                {
                  bitDato4 = 1;
                }
                break;
            }
            break;
        case BUTTON_LEFT:
            dataSelect--;
            if (dataSelect == 0)
            {
              dataSelect = 4;
            }
            break;
        case BUTTON_RIGHT:
            dataSelect++;
            if (dataSelect == 5)
            {
              dataSelect = 1;
            }  
            break;
        }
    }
    previousButtonData = currentButton;
}

void validar()
{
  if (bitDato1 == -1 || bitDato2 == -1 || bitDato3 == -1 || bitDato4 == -1)
  {
    pasoss = 1;
  }
}

void Hamming()
{
  if ((bitDato1 == 0 && bitDato2 == 0 && bitDato4 == 1) || (bitDato1 == 0 && bitDato2 == 1 && bitDato4 == 0) || (bitDato1 == 1 && bitDato2 == 1 && bitDato4 == 1) || (bitDato1 == 1 && bitDato2 == 0 && bitDato4 == 0))
  {
    bitParidad1 = 1;
  }
  if ((bitDato1 == 0 && bitDato3 == 0 && bitDato4 == 1) || (bitDato1 == 0 && bitDato3 == 1 && bitDato4 == 0) || (bitDato1 == 1 && bitDato3 == 1 && bitDato4 == 1) || (bitDato1 == 1 && bitDato3 == 0 && bitDato4 == 0))
  {
    bitParidad2 = 1;
  }
  if ((bitDato2 == 0 && bitDato3 == 0 && bitDato4 == 1) || (bitDato2 == 0 && bitDato3 == 1 && bitDato4 == 0) || (bitDato2 == 1 && bitDato3 == 1 && bitDato4 == 1) || (bitDato2 == 1 && bitDato3 == 0 && bitDato4 == 0))
  {
    bitParidad3 = 1;
  }
}

void mostrarHamming()
{
  lcd.setCursor(1, 0);
  lcd.print(bitParidad1);
  lcd.print(bitParidad2);
  lcd.print(bitDato1);
  lcd.print(bitParidad3);
  lcd.print(bitDato2);
  lcd.print(bitDato3);
  lcd.print(bitDato4);
  lcd.print("        ");
  lcd.setCursor(0,1);
  lcd.print("          ");
  digitalWrite(13, bitParidad1);
  digitalWrite(12, bitParidad2);
  digitalWrite(11, bitDato1);
  digitalWrite(3, bitParidad3);
  digitalWrite(A3, bitDato2);
  digitalWrite(A4, bitDato3);
  digitalWrite(A5, bitDato4);
}
