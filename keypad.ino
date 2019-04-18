#include <ArduinoInit.h>     //no space between # and the word include
#include <SendOnlySoftwareSerial.h>
#include "Arduino.h"
#include "Keypad.h"

/*
 GAME NOTES:

 COLORS: 
 Blue = 1
 Green = 2
 Purple = 3
 Orange = 4
 Black = 5

 SHAPES:
 Circle = 1
 Hex = 2
 Triangle = 3
 Square = 4
 Star = 5

 CARDS:
 blue circle = 1
 blue hex = 2
 blue tri = 3

 green square = 4
 green tri = 5
 green hex = 6

 purp circle = 7
 purp star = 8
 purp hex = 9

 orange star = 10
 orange circle = 11
 orange square = 12

 black square = 13
 black tri = 14
 black star = 15
*/
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  // put your setup code here, to run once:
  //configArduino();
  Serial.begin(9600);

  int ledPin = 0;
  
  for (int i = 0; i <= 13; i++)
  {
    pinMode(ledPin, OUTPUT);
  }

  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  char player;
  char key;
  int player1_sequence[4];
  int player2_sequence[4];
  int player1_guess[4];
  int player2_guess[4];
  int player1_color[4];
  int player1_shape[4];
  int player2_color[4];
  int player2_shape[4];

  int num_correct = 0;
  bool correct = false;

  digitalWrite(A5, LOW);
  digitalWrite(A4, LOW); 
  digitalWrite(A3, LOW);
  digitalWrite(A2, LOW); 

  Serial.println("Hit 1 to start!");

  while(1)
  {
    key = keypad.getKey();
    

    if (key != NO_KEY)
    {
        //Serial.println(key);
        break;
    }
  }

  if (key != NO_KEY)
  {
    player = key;

    if (player == '1')
    {
      Serial.println("Player 1 is choosing the pattern");
      digitalWrite(A3, HIGH);
      digitalWrite(A2, LOW);

      Serial.println("Enter your sequence. Refer to card quide for help.");

      //Player 1 enters their card sequence
      for (int i = 0; i <=3; i++)
      {
        player1_sequence[i] = enter_sequence();
      }

      //color and shape arrays populated
      for (int y = 0; y <= 3; y++)
      {
        player1_color[y] = color(player1_sequence[y]);
        player1_shape[y] = shape(player1_sequence[y]);
      }

      Serial.println("Player sequence");
      for (int j = 0; j <= 3; j++)
      {
        Serial.println(player1_sequence[j]);
      }

      /*
      Serial.println("Player colors");
      for (int w = 0; w <= 3; w++)
      {
        Serial.println(player1_color[w]);
      }

      Serial.println("Player shapes");
      for (int l = 0; l <= 3; l++)
      {
        Serial.println(player1_shape[l]);
      }
      */
      
      //Clears screen
      for (int x = 0; x < 100; x++)
      {
        Serial.println(" ");
      }

      //Player 2 enters their guess sequence
      Serial.println("Player 2 is now guessing.");
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);
      int guess_num = 0;
      for (int f = 1; f <= 10; f++)
      {
        num_correct = 0;
        Serial.print("Guess #: ");
        Serial.println(guess_num + 1);
        guess_num++;
  
        for (int a = 0; a <=3; a++)
        {
          player2_sequence[a] = enter_sequence();
        }
  
        Serial.println("Player sequence");
        for (int p = 0; p <= 3; p++)
        {
          Serial.println(player2_sequence[p]);
        }
  
        //player 2 colors and shapes populated
        for (int z = 0; z <= 3; z++)
        {
          player2_color[z] = color(player2_sequence[z]);
          player2_shape[z] = shape(player2_sequence[z]);
        }

        /*
        Serial.println("Player colors");
        for (int q = 0; q <= 3; q++)
        {
          Serial.println(player2_color[q]);
        }
  
        Serial.println("Player shapes");
        for (int v = 0; v <= 3; v++)
        {
          Serial.println(player2_shape[v]);
        }
        */
        
        //checking guess
        for (int b = 0; b <= 3; b++)
        {
          Serial.print("Card #: ");
          Serial.println(b+1);
          
          if (player2_sequence[b] == player1_sequence[b])
          {
              num_correct++;
              Serial.println("PERFECT MATCH");
              //Serial.println("LIGHTS ON");
              digitalWrite(A5, HIGH);
              digitalWrite(A4, HIGH);
              delay(2000);
              //Serial.println("LIGHTS OFF");
              digitalWrite(A5, LOW);
              digitalWrite(A4, LOW);
              
          }
  
          else if ((player2_color[b] == player1_color[b]))
          {
            Serial.println("COLOR MATCH");
            digitalWrite(A4, HIGH);
            delay(2000);
            digitalWrite(A4, LOW);
          }
  
         else if ((player2_shape[b] == player1_shape[b]))
          {
            Serial.println("SHAPE MATCH");
            digitalWrite(A5, HIGH);
            delay(2000);
            digitalWrite(A5, LOW);
          }

          else 
          {
            Serial.println("NO MATCH");
          }
      }
      //Serial.println(num_correct);
      if (num_correct == 4)
        {
          Serial.println("YOU WIN");
          break;
        }
      }
    }

    /*
    else if (player == '2')
    {
      Serial.println("Player 2 is choosing the pattern");
      digitalWrite(A2, HIGH);
      digitalWrite(A3, LOW);

      Serial.println("Enter your sequence. Refer to card quide for help.");

      for (int i = 0; i <=3; i++)
      {
        player2_sequence[i] = enter_sequence();
        
      }

      for (int j = 0; j <= 3; j++)
      {
        Serial.println(player2_sequence[j]);
      }
    }
    
    
    else
    {
      Serial.println("pls choose a valid option");
    } 
    */   
  }
  
}

int enter_sequence()
{
  String temp = "";
  int num;
  
  Serial.println("Enter card. Hit # after you have entered your choice.");

  while(1)
  {
    char key = keypad.getKey();

    if(key != NO_KEY)
    {
      Serial.print(key);
      temp += key;  
    
      if (key == '#')
      {
          Serial.println("Card entered");
          Serial.println(temp);

          num = temp.toInt();
          Serial.println(num);
          return num;
          
          break;
      }
    }
  }
}

int guess_sequence()
{
  String temp = "";
  int num;
  
  Serial.println("Enter a guess card. Hit # after you have entered your choice.");

  while(1)
  {
    char key = keypad.getKey();

    if(key != NO_KEY)
    {
      Serial.print(key);
      temp += key;  
    
      if (key == '#')
      {
          Serial.println("Guess card entered");
          Serial.println(temp);

          num = temp.toInt();
          Serial.println(num);
          return num;
          
          break;
      }
    }
  } 
}

int color(int num)
{
  if ((num > 0) and (num <= 3))
  {
    return 1; //blue
  }

  if ((num > 3) and (num <= 6))
  {
    return 2; //green
  }

  if ((num > 6) and (num <= 9))
  {
    return 3; //purple
  }

  if ((num > 9) and (num <= 12))
  {
    return 4; //orange
  }

  if ((num > 12) and (num <= 15))
  {
    return 5; //black
  }

}

int shape(int num)
{
  if ((num == 1) or (num == 7) or (num == 11))
  {
    return 1; //Circle
  }

  if ((num == 2) or (num == 6) or (num == 9))
  {
    return 2; //hex
  }

  if ((num == 3) or (num == 5) or (num == 14))
  {
    return 3; //triangle
  }

  if ((num == 4) or (num == 12) or (num == 13))
  {
    return 4; //square
  }

  if ((num == 8) or (num == 10) or (num == 15))
  {
    return 5; //star
  }

}

