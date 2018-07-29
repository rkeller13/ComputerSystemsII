/*-------------------------------------------------------------------------*
 *---									---*
 *---		lookoutThief.c						---*
 *---									---*
 *---	    This file defines the lookoutThief program, that starts the ---*
 *---	safe and crackingThief programs, and oversees the whole		---*
 *---	application.							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 April 20		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/


//Robert J Keller
//CSC 407
//HW2

#include	"safeBustersHeaders.h"

#define		TEXT_LEN	64

int		isCoastClear	= 1;

int		haveTheGoods	= 0;

pid_t		safePid;

pid_t		crackingThiefPid;

void		sigAlarmHandler	(int	sigInt
				)
{
  printf("Watching thief \"Forget the safe!  We gotta go!\"\n");
  isCoastClear	= 0;
  //  YOUR CODE HERE to send SIG_QUIT to both safePid and crackingThiefPid
  sigInt = kill(safePid, SIG_QUIT);
  sigInt = kill(crackingThiefPid, SIG_QUIT);
}


void		sigChildHandler	(int	sigInt
				)
{
  if  (isCoastClear)
  {
    printf("Watching thief \"Good job, let's skedaddle!\"\n");
    haveTheGoods	= 1;
  }

  //  YOUR CODE HERE to send SIG_QUIT to safePid
  sigInt = kill(safePid, SIG_QUIT);

}


int		main		()
{
  int			time;
  int status;
  struct sigaction	act;

  //  YOUR CODE HERE
  //  Install sigAlarmHandler() as the SIGALRM handler
  memset(&act, '\0', sizeof(act));
  act.sa_handler = sigAlarmHandler;
  sigaction(SIGALRM,&act,NULL);

  //  Install sigChildHandler() as the SIGCHLD handle
  memset(&act, '\0', sizeof(act));
  act.sa_handler = sigChildHandler;
  sigaction(SIGINT,&act,NULL);

  safePid	= fork(); //<-- Change that 0 to make a new process 

  if  (safePid == 0)
  {
    //  YOUR CODE HERE to start safe
    execl("safe", "safe.c", NULL);

    fprintf(stderr,"Watching thief \"Where's the freaking safe?!\"\n");
    exit(EXIT_FAILURE);
  }

  sleep(1);
  crackingThiefPid	= fork(); //<-- Change that 0 to make a new process 

  if  (crackingThiefPid == 0)
  {
    char	pidText[TEXT_LEN];

    snprintf(pidText,TEXT_LEN,"%d",safePid);
    //  YOUR CODE HERE to start crackingThief with pidText as a command line argument
    // Use string to long to turn safePid to integer and assign to crackingThiefPid
    execl("crackingThief", "crackingThief.c", NULL);
    
    fprintf(stderr,"Watching thief \"Where's my partner in crime?!\"\n");
    exit(EXIT_FAILURE);
    
  }

  //  YOUR CODE HERE to get sent SIGALRM NUM_SECS_BEFORE_MUST_GO seconds in the future
  sigAlarmHandler(NUM_SECS_BEFORE_MUST_GO);

  for  (time = 0;  isCoastClear && !haveTheGoods;  time++)
  {
    if  ( (time % NUM_SECS_BETWEEN_HURRY_UPS) == 0 )
      printf("Watching thief \"Hurry it up!\"\n");

    sleep(1);
  }

  //  YOUR CODE HERE to wait for both child processes
  waitpid(crackingThiefPid,&status,0);
  waitpid(safePid,&status,0);
  
  printf("(bye)\n");
  return(EXIT_SUCCESS);
}
