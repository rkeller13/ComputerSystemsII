

//--									--//
//		Table-related constants, classes and functions:	  //
//--									--//

class		Table
{
  //  I.  Member vars:
  //  PURPOSE:  To point to the single dish that is currently on '*this' Table
  //	(if there is one).
  Dish*			dishPtr_;

  //  PURPOSE:  To implement mutual exclusion.
  //  PERHAPS ADD SOME VARS HERE

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  Table		(const Table&	source
		);

  //  No copy assignment op:
  Table&	operator=
		(const Table&	source
  		);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructors, assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' Table to initially have no dishes.  No
  //	parameters.  No return value.
  Table		() :
  		dishPtr_(NULL)
		{
		  //  PERHAPS INITIALIZE SOME VARS HERE
		}

  //  PURPOSE:  To release resources.  No parameters.  No return value.
  ~Table	()
  		{
		  //  PERHAPS DESTROY SOME VARS HERE
		}

  //  V.  Accessors:
  //  PURPOSE:  To return 'dishPtr
  Dish*		getDishPtr	()
  				const
		{
		  return(dishPtr_);
		}


  //  VI.  Mutators:

  //  VII.  Methods that do main and misc. work of class:
  //  PURPOSE:  To have 'chef' attempt to place '*newDishPtr' on '*this' Table
  //	(that is, set 'dishPtr_' to 'newDishPtr').  This cannot be done if
  //	there already is a Dish present (that is, if 'dishPtr_ != NULL').  If
  //	there is a Dish present then the Chef should complain vociferously
  //	and wait until the old Dish is cleared.  No return value.
  void		serve		(Chef&		chef,
				 Dish*		newDishPtr
  				)
  		{
		  //  MAKE THIS THREAD-SAFE, PLEASE
		  dishPtr_	= newDishPtr;
		  sleep( (rand() % MAX_SLEEP_SECONDS) + 1);
		  std::cout
			<< chef
			<< ": \""
			<< *getDishPtr()
			<< " is served!\"\n";
		}

  //  PURPOSE:  To have 'gourmand' attempt to remove 'dishPtr_' from '*this'
  //	Table (that is, return the old value of 'dishPtr_' and set it to
  //	'NULL').  This cannot be done if there is no Dish present (that is, if
  //	'dishPtr_ == NULL').  If there is no Dish present then the Gourmand
  //	should complain vociferously and wait until a Dish is served.  Returns
  //	the old value of 'dishPtr_' and sets 'dishPtr_' to 'NULL'.
  Dish*		eatFrom		(Gourmand&		gourmand
  				)
		{
		  //  MAKE THIS THREAD-SAFE, PLEASE

		  Dish*	toReturn	= getDishPtr();
		  std::cout
			<< gourmand
			<< ": \"That "
			<< *getDishPtr()
			<< " looks yummy!\"\n";
		  sleep( (rand() % MAX_SLEEP_SECONDS) + 1);
		  dishPtr_  = NULL;
		  return(toReturn);
		}
};


//  PURPOSE:  To serve as the global singleton Table instance.
Table		table;


//  PURPOSE:  To have the Chef pointed to by 'void*' ptr 'vPtr' execute
//	its 'prepare()' method 'NUM_DISHES_TO_DO' times and 'serve()' the
//	resulting Dish instances on 'table' 'NUM_DISHES_TO_DO' times.
void*		cook	(void*		vPtr
			)
{
  Chef*	chefPtr	= (Chef*)vPtr;

  //  PERHAPS A LOOP HERE

  return(NULL /* CHANGE IF YOU WANT */);
}


//  PURPOSE:  To have the Gourmand pointed to by 'void*' ptr 'vPtr' execute
//	its 'eatFrom()' method 'NUM_DISHES_TO_DO' times on 'table' and to
//	'consume()' the resulting Dish instances 'NUM_DISHES_TO_DO' times.
void*		eat	(void*		vPtr
			)
{
  Gourmand*	gourmandPtr	= (Gourmand*)vPtr;

  //  PERHAPS A LOOP HERE

  return(NULL /* CHANGE IF YOU WANT */);
}


//  PURPOSE:  To harass CSC 407 students into learning thread programming
//	and thread-safe producer-consumer buffer creation.  If 'argc >= 2' then
//	'argv[1]' is used as a random number seed.  Return 'EXIT_SUCCESS' to
//	OS.
int		main	(int		argc,
			 char*		argv[]
			)
{
  //  I.  Application validity check:

  //  II.  Let's eat!
  //  II.A.  Initialize random number generator:
  if  (argc >= 2)
    srand(atoi(argv[1]));

  //  II.B.  Create Chef and Gourmand threads:
  pthread_t	chefIds[NUM_CHEFS];
  pthread_t	gourmandIds[NUM_CHEFS];

  //  PERHAPS A LOOP HERE

  //  II.C.  Wait for Chef and Gourmand threads:
  //  PERHAPS A LOOP HERE

  //  III.  Finished:
  return(EXIT_SUCCESS);
}