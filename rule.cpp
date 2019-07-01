#include "rule.h"
#include <QDebug>

Rule::Rule(const QString& name, const unsigned minChars, const int maxChars,
      const unsigned minCapital, const unsigned minNumbers, const bool specialChars)
{
    name_ = name;
    minChars_ = minChars;
    maxChars_ = maxChars;
    minCapital_ = minCapital;
    minNumbers_ = minNumbers;
    specialChars_ = specialChars;
}

void Rule::setName(const QString& name)
/*
    @det 		Setter for the rule's name
    @param 		QString     name to be given
    @return 	void
*/
{
    name_ = name;
}

void Rule::setMinChars(const unsigned minChars)
/*
    @det 		Setter for the rule's minimum number of characters
    @param 		unsigned     minimum number of chars
    @return 	void
*/
{
    minChars_ = minChars;
}

void Rule::setMaxChars(const int maxChars)
/*
    @det 		Setter for the rule's maximum number of characters
    @param 		unsigned     maximum number of chars
    @return 	void
*/
{
    maxChars_ = maxChars;
}

void Rule::setMinCapital(const unsigned minCapital)
/*
    @det 		Setter for the rule's minimum number of capital letters
    @param 		unsigned     minimum number of capital letters
    @return 	void
*/
{
    minCapital_ = minCapital;
}

void Rule::setMinNumbers(const unsigned minNumbers)
/*
    @det 		Setter for the rule's minimum number of numbers
    @param 		unsigned     minimum number of numbers
    @return 	void
*/
{
    minNumbers_ = minNumbers;
}

void Rule::setSpecialChars(const bool specialChars)
/*
    @det 		Setter for the rule's allowance for special characted
    @param 		bool        true if special chars are allowed, else false
    @return 	void
*/
{
    specialChars_ = specialChars;
}

QString Rule::getName() const
/*
    @det 		Getter for the rule's name
    @param 		void
    @return 	QString     name given
*/
{
    return name_;
}

unsigned Rule::getMinChars() const
/*
    @det 		Getter for the rule's minimum number of characters
    @param 		void
    @return 	unsigned     minimum number of chars
*/
{
    return minChars_;
}

int Rule::getMaxChars() const
/*
    @det 		Getter for the rule's maximum number of characters
    @param 		void
    @return 	unsigned     maximum number of chars
*/
{
    return maxChars_;
}

unsigned Rule::getMinCapital() const
/*
    @det 		Getter for the rule's minimum number of capital letters
    @param 		void
    @return 	unsigned     minimum number of capital letters
*/
{
    return minCapital_;
}

unsigned Rule::getMinNumbers() const
/*
    @det 		Getter for the rule's minimum number of numbers
    @param 		void
    @return 	unsigned     minimum number of numbers
*/
{
    return minNumbers_;
}

bool Rule::getSpecialChars() const
/*
    @det 		Getter for the rule's allowance for special characted
    @param 		void
    @return 	bool        true if special chars are allowed, else false
*/
{
    return specialChars_;
}

void Rule::showRule() const
/*
    @det 		Method to print a rule's attributes on qDebug stream
    @param 		void
    @return 	void
*/
{
    qDebug()    << name_
                << " " << minChars_
                << " " << maxChars_
                << " " << minCapital_
                << " " << minCapital_
                << " " << specialChars_
                << endl;
}
