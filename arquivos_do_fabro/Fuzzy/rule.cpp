// Project FLIE-Fuzzy Logic Inference Engine - Joƒo Alberto Fabro - out/1996
// Method Definition File rule.cc - Implementation of class fuzzy_rule

#include "flie.h"

rule::rule()
{
 inputcat1 = inputcat2 = inputcat3 = outputcat = NULL;
}
// definerule(category*,category*) - Defines a rule with just one input set
//				     and one output set!
// Each set must be part of a linguistic variable!
void rule::definerule(trapezoid_category *input1, trapezoid_category *output)
{
inputcat1 = input1;
outputcat = output;
}

// definerule(category*,category*,category*) - Defines a rule with two input sets
//				     and one output set!
void rule::definerule(trapezoid_category *input1,trapezoid_category *input2,trapezoid_category *output)
{
inputcat1 = input1;
inputcat2 = input2;
outputcat = output;
}
// definerule(category*,category*,category*,category*) - Defines a rule with three
// input sets and one output set!
void rule::definerule(trapezoid_category *input1,trapezoid_category *input2,trapezoid_category *input3, trapezoid_category *output)
{
inputcat1 = input1;
inputcat2 = input2;
inputcat3 = input3;
outputcat = output;
}

// evaluaterule(float) - Evaluates the rule and return the result(pertinence of the
//			 output set!)
float rule::evaluaterule(float &inputval1)
{
 return(inputcat1->getshare(inputval1));
}

// idem for two inputs! Use a t_norm to calculate!
float rule::evaluaterule(float &inputval1, float &inputval2)
{
 return(tnorm(inputcat1->getshare(inputval1), inputcat2->getshare(inputval2)));
}

// idem for three inputs! Use a t_norm to calculate!
float rule::evaluaterule(float &inputval1, float &inputval2, float &inputval3)
{
 float x=tnorm(inputcat1->getshare(inputval1), inputcat2->getshare(inputval2));
 return(tnorm(x,inputcat3->getshare(inputval3)));
}

// getoutputcategory - return outputcat!
trapezoid_category *rule::getoutputcategory()
{
return(outputcat);
}

void rule::clearinputcategoryactivations()
{
      if(inputcat1!=NULL) inputcat1->clearoutput();
      if(inputcat2!=NULL) inputcat2->clearoutput();
      if(inputcat3!=NULL) inputcat3->clearoutput();
}


void rule::clearoutputcategoryactivations()
{
       outputcat->clearoutput();
}

void rule::save_m(FILE *file)
{
 if(inputcat1)
   fprintf(file, "%d",inputcat1->getnumber()+1);
 if(inputcat2)
   fprintf(file, " %d",inputcat2->getnumber()+1);
 if(inputcat3)
   fprintf(file, " %d",inputcat3->getnumber()+1);
 fprintf(file, ", ");

 if(outputcat)
   fprintf(file, "%d (1) : 1\r",outputcat->getnumber()+1);
}

void rule::save(FILE *file)
{
 if(inputcat1)
   fprintf(file, "%s\n",inputcat1->getname());
 else
   fprintf(file, "NULL\n");
 if(inputcat2)
   fprintf(file, "%s\n",inputcat2->getname());
 else
   fprintf(file, "NULL\n");
 if(inputcat3)
   fprintf(file, "%s\n",inputcat3->getname());
 else
   fprintf(file, "NULL\n");
 if(outputcat)
   fprintf(file, "%s\n",outputcat->getname());
}

void rule::load(FILE *file)
{
 // instead of loading rule, we load the names of the categories of the rule
 // inside the fuzzy_control object!!!
 // and use "insert_rule" from fuzzy_control!!! 

}

rule::~rule()
{
 if(inputcat1)
   free(inputcat1);
 if(inputcat2)
   free(inputcat2);
 if(inputcat3)
   free(inputcat3);
 if(outputcat)
   free(outputcat);
}
