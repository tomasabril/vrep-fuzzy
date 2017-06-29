// Project FLIE-Fuzzy Logic Inference Engine - João Alberto Fabro - out/1996

// Header File rule.h



#define MAXRULES 150  // Maximum number of rules per rulebase for fuzzy_control





/* Class Rule - contains one rule of inference - can make inferences based on

 rules of 1, 2 or 3 predecessors and 1 sucessor. To define a rule, are necessary

 the fuzzy sets of predecessors and of the sucessor! Ex: 



 if Tempsense is Xlarge and Levelsense is Large then HeatKnob is Alot



 needs the following definition of rule:



 rule.definerule(SenseTemp.getcat("Xlarge"),SenseLevel.getcat("Large"), 

                   HeatKnob.getcat("Alot"));

*/



class rule

{

private:

	trapezoid_category *inputcat1, *inputcat2, *inputcat3;

	trapezoid_category *outputcat;



public:

        rule();

	void definerule(trapezoid_category *input1,trapezoid_category *output);

	void definerule(trapezoid_category *input1,trapezoid_category *input2,trapezoid_category *output);

	void definerule(trapezoid_category *input1,trapezoid_category *input2,trapezoid_category *input3,

                        trapezoid_category *output);

	float evaluaterule(float &inputval1);

        float evaluaterule(float &inputval1,float &inputval2);

        float evaluaterule(float &inputval1,float &inputval2,float &inputval3);

	trapezoid_category *getoutputcategory();

        void clearinputcategoryactivations();

        void clearoutputcategoryactivations();

        void save_m(FILE *file);
        void save(FILE *file);

        void load(FILE *file);

        ~rule();

};

