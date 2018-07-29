/*-------------------------------------------------------------------------*
 *---									---*
 *---		safe.c							---*
 *---									---*
 *---	    This file defines the safe program.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 April 20		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"safeBustersHeaders.h"

int		shouldStillRun	= 1;

int		wasCracked	= 0;

int		count0;

int		count1;

int		count2;

void		sigIntHandler	(int	sigNum
				)
{
  shouldStillRun	= 0;
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


void		sigRotateHandler(int		sigNum,
				 siginfo_t*	infoPtr,
				 void*		dataPtr
				)
{
  int	toSend;

  if  (count0 > 0)
  {
    toSend	= computeResponse(&count0);
  }
  else
  if  (count1 > 0)
  {
    toSend	= computeResponse(&count1);
  }
  else
  if  (count2 > 0)
  {
    toSend	= computeResponse(&count2);

    if  (toSend == SIG_RIGHT_DIGIT)
      wasCracked= 1;

  }

  kill(infoPtr->si_pid,toSend);
}


int		main		()
{
  struct sigaction	act;

  srand(getpid());

  memset(&act,'\0',sizeof(act));

  act.sa_handler	= sigIntHandler;
  sigaction(SIG_QUIT,&act,NULL);

  act.sa_handler	= NULL;
  act.sa_sigaction	= sigRotateHandler;
  act.sa_flags		= SA_SIGINFO;
  sigaction(SIG_TRY_NEXT_DIGIT,&act,NULL);

  count0		= (rand() % 16) + 1;
  count1		= (rand() % 16) + 1;
  count2		= (rand() % 16) + 1;

  printf("Safe (\"Don't tell, but my combination is %d-%d-%d\")\n",
	 count0,count1,count2
	);

  while  (shouldStillRun)
    sleep(1);

  if  (wasCracked)
     printf("Safe \"Ya got me!\"\n");
  else 
     printf("Safe \"I guess I protected the family jewels! ;)\"\n");

  return(EXIT_SUCCESS);
}
