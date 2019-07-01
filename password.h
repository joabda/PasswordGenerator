#ifndef PASSWORD_H
#define PASSWORD_H
#include <string>
#include <vector>
#include <QDebug>
#include "rule.h"
using namespace std;

static QString alpha = "abcdefghijklmnopqrstuvwxyz";
static QString capitalAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static QString specialChars = "!@#$%&";
static QString numbers = "0123456789";

class Password
{
public:
    Password();
    QString generate();
    QString getLastGeneratedPassword() const;
    QString operator() (Rule* oneRule, const unsigned preferedLength = 14);

private:
    Rule* rule_;
    unsigned preferedLength_;
    QString password_;
    unsigned getLenght() const;
    int selectArray() const;
    int generateKey() const;
    bool checkPassword(const unsigned capitalAlphaCount, const unsigned numbersCount) const;
};

#endif // PASSWORD_H
