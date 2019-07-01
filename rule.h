#ifndef RULE_H
#define RULE_H
#include <QString>

class Rule
{
public:
    Rule();
    Rule(const QString& name, const unsigned minChars, const int maxChars,
          const unsigned minCapital, const unsigned minNumbers, const bool specialChars);

    // Setters
    void setName(const QString& name);
    void setMinChars(const unsigned minChars);
    void setMaxChars(const int maxChars);
    void setMinCapital(const unsigned minCapital);
    void setMinNumbers(const unsigned minNumbers);
    void setSpecialChars(const bool specialChar);

    // Getters
    QString getName() const;
    unsigned getMinChars() const;
    int getMaxChars() const;
    unsigned getMinCapital() const;
    unsigned getMinNumbers() const;
    bool getSpecialChars() const;

    void showRule() const;

    ~Rule() {}

private:
    QString name_;
    unsigned minChars_;
    int maxChars_;
    unsigned minCapital_;
    unsigned minNumbers_;
    bool specialChars_;
};

#endif // RULES_H
