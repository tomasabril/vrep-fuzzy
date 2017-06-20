// Project FLIE-Fuzzy Logic Inference Engine - João Alberto Fabro - out/1996

// Class Methods File lingvar.cc - Implementation of class linguisticvariable

#include <string.h>
#include "flie.h"


// Contructor - Just initialize number of categories(fuzzy sets) of variable.
linguisticvariable::linguisticvariable()
{
  numcategories=0;
}

linguisticvariable& linguisticvariable::operator=(const linguisticvariable& l)
{
    if (this != &l) {  // make sure not same object
         strcpy(name, l.name);              // copy new name
         numcategories = l.numcategories;
         for(int i=0;i<numcategories;i++)
                cats[i] = new trapezoid_category(*(l.cats[i]));
    }
return *this; // return ref for multiple assignment
}//end operator=

// setname - Initalize name of variable
void linguisticvariable::setname(char *namevar)
{
 strcpy(name,namevar);
}


// getname - Returns the name of the linguistic variable
char *linguisticvariable::getname()
{
return(name);
}

// includecategory - Receive a pointer to a "category" object, and include this category
// 		     in the linguistic variable(this category should have been define priorly)
int linguisticvariable::includecategory(trapezoid_category *namecat)
{
	if(numcategories<MAXCATEGORIES)
	{
		cats[numcategories] = namecat;
                namecat->setnumber(numcategories);
		numcategories++;
		return(0);
	}
	else
		return(1);
}

// Insert a Pointer to trapezoid_category at the position "num", if there is at least num+1 categories
int linguisticvariable::setcatptr(int n, trapezoid_category *cat )
{
        if(n<MAXCATEGORIES)
            {
              if(n>numcategories) numcategories = n;
              cats[n] = cat;
              return(0);
            }
        else
            {
             cout << "Error in setcatptr: inserted after de end of categories vector\n";
             return(-1);
            }
}

// getcat(char *) - Returns the category object that have "namecat"!

trapezoid_category &linguisticvariable::getcat(char *namecat)
{
char *tmp;

  for(int i=0;i<numcategories;i++)
   {
   tmp=cats[i]->getname();
   if(!strcmp(namecat,tmp))
      return(*cats[i]);
   }
}



// getcat(int) - Returns the category object of position "numcat"!
//                If numcat>numcategories, ERROR!
trapezoid_category &linguisticvariable::getcat(int numcat)
{
  if(numcat<numcategories)
     return(*cats[numcat]);
  else
    cout<<"ERROR!!! in linguisticvariable::getcat(int) with numcat=" << numcat <<
    " and number of categories =" << numcategories <<"\n";
//return(NULL);
}

trapezoid_category *linguisticvariable::getcatptr(int numcat)
{
  if(numcat<numcategories)
     return(cats[numcat]);
  else
    cout<<"ERROR!!! in linguisticvariable::getcat(int) with numcat=" << numcat <<
    " and number of categories =" << numcategories <<"\n";
    return(NULL);
}


void linguisticvariable::clearoutputcategoryactivations()
{
  for(int i=0;i<numcategories;i++)
     cats[i]->clearoutput();
}

void linguisticvariable::save_m(FILE *file, char* number)
{
 fprintf (file, "\r[%s]\r", number);
 fprintf (file, "Name='%s'\r", name);
 fprintf (file, "Range=[%d %d]\r", (int)cats[0]->getrangelow(), -(int)cats[0]->getrangelow());
 fprintf (file, "NumMFs=%d\r",numcategories);
// fprintf (file, "%d\r", numcategories);
  for (int i=0;i<numcategories;i++)
      cats[i]->save_m(file,i);
}

void linguisticvariable::save(FILE *file)
{
 fprintf (file, "%s\n", name);
 fprintf (file, "%d\n", numcategories);
  for (int i=0;i<numcategories;i++)
      cats[i]->save(file);
}

void linguisticvariable::load(FILE *file)
{
  char line[30];
  fgets (name, 30, file); name[strlen(name)-1] = '\0';
  fgets (line, 30, file); line[strlen(line)-1] = '\0';
  numcategories = atoi (line);

  for (int i=0;i<numcategories;i++)
     {
      cats[i] = new trapezoid_category;
      cats[i]->load(file);
      cats[i]->setnumber(i);
     }
}
