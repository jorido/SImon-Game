/*
 * Name: John Do
 * Email: djw0626@student.ubc.ca
 * Student #: 56442833
 * Date: June 17, 2021
 * L1D
 * Purpose: To simulate a simple simon game using Arduino and C 
 * 			The user should copy the pattern of LEDs given by the program
 */

/* define all LEDs and Buttons */ 
#define L_RED 13
#define L_YEL 12
#define L_BLU 11
#define L_GRE 10
#define P_RED 7
#define P_YEL 6
#define P_BLU 5
#define P_GRE 4
#define WIN 9
#define LOSE 8

/* define other symbolic constants and useful arrays e.g. timing */ 

#define ONE_SEC 1000
#define numOfLED 4

const int numOfStage = 5;

const int LED[] = {L_RED, L_YEL, L_BLU, L_GRE}; 
const int PUSH[] = {P_RED, P_YEL, P_BLU, P_GRE};
const int RESULT[] = {WIN,LOSE};
int Output[numOfStage];
int Input[numOfStage];
int buttonState;
int lastButtonState = LOW;

//function prototypes

void randomOutput(int simon[], int numOfSimon);
void startGame(void);
void inGame(int initializedSimon[], int numOfSimon);
void lightUp(int stage);
int checkButton(int stage);



void setup()
{
  // All required setup/configuration statements
  for(int i = 0; i < numOfLED; i++)
  {
    pinMode(LED[i],OUTPUT);
    pinMode(PUSH[i],INPUT);
  }
  pinMode(WIN, OUTPUT);
  pinMode(LOSE, OUTPUT);
}

void loop()
{
  // The statements and function calls 
  // As usual, loop will provides our program's super-loop
  // This sequence of user-made functions is the "main" sequence
  
  randomOutput(Output, numOfStage);
  startGame();
  delay(ONE_SEC);
  inGame(Output, numOfStage);
  delay(ONE_SEC);
  

} 

/* Other user-defined function definitions here*/ 

/* Initialize the output array (for LEDs) with 
   random order of pin numbers. */
void randomOutput(int simon[], int numOfSimon)
{
  randomSeed(analogRead(0));
  for(int i = 0; i < numOfSimon; i++)
  {
    simon[i] = random(L_GRE,L_RED+1);
  }
}

/* Flow of the in-game algorithm */
void inGame(int initializedSimon[], int numOfSimon)
{
  // Stage variable represents what stage the user is on 
  int stage = 0;
  
  /* Repeat the lightUp and checkButton numOfSimon times.
   * numOfSimon represents how many stages there are in the game
   * One can easily change the number of stages by changing numOfStages
   */
  for(int i = 0; i < numOfSimon; i++)
  {
    delay(500);
    lightUp(stage);
    
    //pushButton returns 0 if the button input is wrong.
    stage = checkButton(stage);
    
    // Lose
    if(stage == 0)
    {
      digitalWrite(LOSE, HIGH);
      delay(ONE_SEC*5);
      digitalWrite(LOSE, LOW);
      break;
    }
    // Win
    else if(stage == 5)
    {
      digitalWrite(WIN, HIGH);
      delay(ONE_SEC*5);
      digitalWrite(WIN, LOW);
    }
  }
}

/* Lights up the LEDs according to the 
 * Output array and stage the user is on */
void lightUp(int stage)
{
  for(int i = 0; i < numOfLED; i++)
  {
    digitalWrite(LED[i],LOW);
  }
  for(int j = 0; j <= stage; j++)
  {
    digitalWrite(Output[j],HIGH);
    delay(ONE_SEC);
    digitalWrite(Output[j],LOW);
    delay(500);
  }
}

/* Reads input from pushbutton and immediately checks whether 
 * it matches the Output array
 * if right, the stage increases by 1
 * if wrong, it returns 0 */  
int checkButton(int stage)
{
  
  int counter = 0;
  while (counter <= stage) 
  {
      while (digitalRead(PUSH[0]) == LOW ||
		digitalRead(PUSH[1]) == LOW ||
		digitalRead(PUSH[2]) == LOW ||
		digitalRead(PUSH[3]) == LOW) {
        
		if (digitalRead(PUSH[0]) == HIGH) {
          while (digitalRead(PUSH[0]) == HIGH) {}
          if (Output[counter] != LED[0]) {
          	return 0;
          }
			Input[counter] = LED[0];
        	counter++;
          	break;
		}
		else if (digitalRead(PUSH[1]) == HIGH) {
			while (digitalRead(PUSH[1]) == HIGH) {}
            if (Output[counter] != LED[1]) {
              return 0;
            }
			Input[counter] = LED[1];
        	counter++;
          	break;
		}
		else if (digitalRead(PUSH[2]) == HIGH) {
			while (digitalRead(PUSH[2]) == HIGH) {}
            if (Output[counter] != LED[2]) {
              return 0;
            }
			Input[counter] = LED[2];
        	counter++;
          	break;
		}
		else if (digitalRead(PUSH[3]) == HIGH) {
			while (digitalRead(PUSH[3]) == HIGH) {}
            if (Output[counter] != LED[3]) {
              return 0;
            }
			Input[counter] = LED[3];
        	counter++;
          	break;
		}
	}
  }
  return counter;
}

// Indicate the start of a new game by turning all lights on for 2 seconds.
void startGame(void)
{
  for(int i = 0; i < numOfLED; i++)
  {
    digitalWrite(LED[i],HIGH);
    digitalWrite(PUSH[i],HIGH);
  }
  digitalWrite(RESULT[0],HIGH);
  digitalWrite(RESULT[1],HIGH);
  delay(ONE_SEC*2);
  for(int i = 0; i < numOfLED; i++)
  {
    digitalWrite(LED[i],LOW);
    digitalWrite(PUSH[i],LOW);
  }
  digitalWrite(RESULT[0],LOW);
  digitalWrite(RESULT[1],LOW);
  
}
