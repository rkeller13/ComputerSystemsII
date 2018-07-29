/* 
Robert Keller CSC407 HW2

Safe Program

The safe chooses a random combination
Then it hangs out waiting for either 
SIG_QUIT (the game is over, stop the process) or
SIG_TRY_NEXT_DIGIT (see if the current combination is correct)

*/



#include	"safeBustersHeaders.h"

int shouldStillRun = 1;
int safeOpen = 0;
int firstNum;
int secondNum;
int thirdNum;

pid_t   crackingThiefPid;

//Your simple SIG_QUIT handler should just set your should still run variable to 0.
void    sigQuitHandler (int  sigInt
        )
{
  shouldStillRun = 0;
}



int		computeResponse	(int*		countPtr
				)
{
  int	toReturn;

  sleep(1);
  (*countPtr)--;

  if  (*countPtr == 0)
  {
    printf("Safe \"Click!\"\n");
    toReturn	= SIG_RIGHT_DIGIT;
  }
  else
  {
    printf("Safe \"Nope.\"\n");
    toReturn	= SIG_WRONG_DIGIT;
  }

  return(toReturn);
}


/* Your advanced SIG_TRY_NEXT_DIGIT handler should
See if your first combination number variable is greater than 0. 
If it is then do computeResponse(address of first number var) and send the int value it 
returns back to the process that signaled it.
else, if your second combination number variable is greater than 0. 
If it is then do computeResponse(address of second number var) and send the int value it 
returns back to the process that signaled it.
else, if your third combination number variable is greater than 0. 
If it is then do computeResponse(address of third number var) and send the int value it 
returns back to the process that signaled it. 
However before sending your signal back to the crackingThief process, see if this value equals 
SIG_RIGHT_DIGIT. If so, then set your was safe opened variable to 1. */
void    sigTryNextDigitHandler (int    sigInt,
         siginfo_t* sigInfoPtr,
         void*    data
        )
{
  if  (firstNum > 0)
    computeResponse(firstNum);
  else if (secondNum > 0)
    computeResponse(secondNum);
  else if (thirdNum > 0)
    if (computeResponse(thirdNum) == SIG_RIGHT_DIGIT)
      safeOpen = 1;
    computeResponse(thirdNum);   
}



int main () {
  //srand(getpid()) (this initializes the random number generator)
	srand(getpid());

  struct sigaction  act;

//Install a simple handler for SIG_QUIT
  memset(&act, '\0', sizeof(act));
  act.sa_handler = sigQuitHandler;
  sigaction(SIG_QUIT,&act,NULL);

//Install an advance handler for SIG_TRY_NEXT_DIGIT
  memset(&act, '\0', sizeof(act));
  act.sa_flags= SA_SIGINFO;
  act.sa_sigaction = sigTryNextDigitHandler;
  sigaction(SIG_TRY_NEXT_DIGIT,&act,NULL);

//Initialize all your combination numbers with the expression (rand() % 16) + 1
  firstNum = (rand() % 16) +1;
  secondNum = (rand() % 16) +1;
  thirdNum = (rand() % 16) +1;

//printf() what the combination is
  printf("The combination is %d - %d - %d", firstNum, secondNum, thirdNum);

/*Hangout in a loop:
while  (your should still run variable)
  sleep(1);*/
  while(shouldStillRun)
    sleep(1);

/*After ending the loop, note whether the safe was opened:
if  (your was safe opened var)
  printf(Some humble);
else
  printf(Some bragging message); */
  if (safeOpen == 1)
    printf("You got lucky and won the lottery!");
  else
    printf("You're too dumb to open this safe!");

//Do return(EXIT_SUCCESS)
  return(EXIT_SUCCESS);

}


















