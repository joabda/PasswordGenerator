#include "password.h"

Password::Password()
/*
    @det 		Default constructor of a Password
    @param 		Rule*      Pointer to the the rule to be taken into consideration
    @return 	void
*/
{
    rule_ = nullptr;
    preferedLength_ = 14;
}


unsigned Password::getLenght() const
/*
    @det 		Method to get the length of the password to be generated
    @param 		void
    @return 	unsigned    Length of the password to generate
*/
{
    if(preferedLength_ > rule_->getMinChars())
        return preferedLength_;
    return rule_->getMinChars() + 2;
}

int Password::selectArray() const
/*
    @det 		Method that will return a random number between 1 and 4(inclusive)
                    1: to use alphabets,
                    2: to use capital alphabets,
                    3: to use numbers,
                    4: to use special chars.
    @param 		void
    @return 	int     number between 1 an 4
*/
{
    int* pointer = new int(); // Pointing to a memory adress
    uintptr_t adress = reinterpret_cast<uintptr_t>(pointer); // Putting that adress in adress
    adress = adress % 5;
    if(adress == 0)
        adress++;
    return static_cast<int>(adress);
}

int Password::generateKey() const
/*
    @det 		Method that will return a random number between 1 and 25 (inclusive)
                    to choose an alphabet letter
    @param 		void
    @return 	int     number between 1 an 25
*/
{
    int* pointer = new int(); // Pointing to a memory adres
    uintptr_t adress = reinterpret_cast<uintptr_t>(pointer); // Putting that adress in adress
    adress = adress % 5;
    return static_cast<int>(adress);
}

QString Password::generate()
{
    int key = 0;
    unsigned alphaCount = 0;
    unsigned capitalAlphaCount = 0;
    unsigned specialCharsCount = 0;
    unsigned numbersCount = 0;
    unsigned currentLenght = 0;
    unsigned desiredLength = getLenght();

    auto add = [&] (const QString& table, unsigned& tableCounter, const int moduloKey = 1)
    {
        key = generateKey();
        key = key % moduloKey;
        password_ = password_ + table[key];
        tableCounter++;
        currentLenght++;
    };

    while(currentLenght < desiredLength)
    {
        int selectedArray = selectArray();
        if(currentLenght == 0)
        {
            selectedArray = selectedArray % 3;
            if(selectedArray == 0)
                selectedArray++;
        }
        switch(selectedArray)
        {
            case 1:
            if((alphaCount==2)&&(numbersCount==0||capitalAlphaCount==0||capitalAlphaCount==1||specialCharsCount==0))
                break;
            add(alpha, alphaCount);
            break;

            case 2:
            if((capitalAlphaCount==2)&&(numbersCount==0||alphaCount==0||alphaCount==1||specialCharsCount==0))
                break;
            add(capitalAlpha, capitalAlphaCount);
            break;

            case 3:
            if((numbersCount==1)&&(alphaCount==0||alphaCount==1||capitalAlphaCount==1||capitalAlphaCount==0||specialCharsCount==0))
                break;
            add(numbers, numbersCount, 10);
            break;

            case 4:
            if((specialCharsCount==1)&&(alphaCount==0||alphaCount==1||capitalAlphaCount==0||capitalAlphaCount==1||numbersCount==0))
                break;
            add(specialChars, specialCharsCount, 6);
            break;
        }
    }

    if(!checkPassword(capitalAlphaCount, numbersCount))
        return generate();
    return password_;
}

QString Password::operator() (Rule* oneRule, const unsigned preferedLength)
{
    preferedLength_ = preferedLength;
    rule_ = oneRule;
    return generate();

}

QString Password::getLastGeneratedPassword() const
/*
    @det 		Getter of the last generated password
    @param 		void
    @return 	QString     last generated password
*/
{
    return password_;
}

bool Password::checkPassword(const unsigned capitalAlphaCount, const unsigned numbersCount) const
{
    if(capitalAlphaCount >= rule_->getMinCapital() &&
       numbersCount >= rule_->getMinNumbers())
        return true;
    return false;
}
