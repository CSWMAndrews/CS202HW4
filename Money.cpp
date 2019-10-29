//
// Created by Giddeon on 10/28/2019.
// credit to Matt Perry who's code I referenced
//

#include "Money.hpp"
#include <iostream>

//Primary Output
std::ostream & operator <<(std::ostream & os, const Money & money){
    double myMoney = money.getMoney();
    if(myMoney ==0){
        return os << "$0.00";
    }
    if (money._sign ==1){
        return os << "-$" << myMoney;
    }
    return os << "$" << myMoney;

}


//Addition
Money operator +(Money lhs, const Money & rhs)
{

    //std::cout << lhs._dollars << " " << lhs._cents << " " << rhs._dollars << " " << rhs._cents << "\n";
    lhs._dollars += rhs._dollars;
    lhs._cents += rhs._cents;
    while(lhs._cents >= 100){
        lhs._dollars++;
        lhs._cents -=100;
    }

    //std::cout << lhs._dollars << " " << lhs._cents << " " << rhs._dollars << " " << rhs._cents << "\n";
    return lhs;
}
// Canonical
Money Money::operator+=(const Money &rhs)
{
    return *this = *this + rhs;
}



//Subtraction
Money operator -(Money lhs, const Money & rhs)
{
    // Subtraction operation
    //std::cout << lhs._dollars << " " << lhs._cents << " " << rhs._dollars << " " << rhs._cents << "\n";
    lhs._dollars -= rhs._dollars;
    lhs._cents -= rhs._cents;

    //std::cout << lhs._dollars << " " << lhs._cents << " " << rhs._dollars << " " << rhs._cents << "\n";
    while(lhs._dollars < 0)
    {
        lhs._dollars--;
        lhs._cents +=100;
    }

    //std::cout << lhs._dollars << " " << lhs._cents << " " << rhs._dollars << " " << rhs._cents << "\n";
    return lhs;
}
Money Money::operator-=(const Money &rhs)
{
    //return *this = *this - rhs; //I am not entirely sure why this does not work
    this->_dollars -=rhs._dollars;
    this->_cents -= rhs._cents;
    return *this;
}



//Multiplication
Money operator *(const double & lhs, Money  rhs)
{
// * operator for a money and a double
    rhs._cents *= lhs;
    rhs._dollars *=lhs;
    return rhs;
}
Money operator *(Money lhs, double rhs)
{
// / operator for a money and double
    lhs._cents *= rhs;
    lhs._dollars*=rhs;
    return lhs;
}
Money Money::operator *=(const double & rhs)
{
    this->_dollars *=rhs;
    this->_cents *= rhs;
    while(this->_cents < 0){
        this->_dollars--;
        this->_cents +=100;
    }
    while(this->_cents >= 100){
        this->_dollars++;
        this->_cents -=100;
    }
    return *this;
}


//Division
Money Money::operator /=(const double  & rhs)
{
    this->_dollars /=rhs;
    this->_cents /= rhs;
    while(this->_cents < 0){
        this->_dollars--;
        this->_cents +=100;
    }
    while(this->_cents >= 100){
        this->_dollars++;
        this->_cents -=100;
    }
    return *this;
}
Money operator /(Money lhs, double rhs)
{
    lhs._cents /= rhs;
    lhs._dollars /=rhs;
    return lhs;
}
// Canonical not applicable
//Money operator/(Money lhs, const Money &rhs) { return lhs /= rhs; }



// Canonical not applicable
//Money operator*(Money lhs, const Money &rhs) { return lhs *= rhs; }


//Boolean Operators, ==, !=, <, >, <=, >=
bool Money::operator ==(const Money & rhs)const{
    if(this->_cents == rhs._cents){
        if(this->_dollars == rhs._dollars){
            return true;
        }
    }
    if(this->_dollars == rhs._dollars){
        if(this->_cents == rhs._cents){
            return true;
        }
    }
    return false;
}
bool Money::operator !=(const Money & rhs)const{
    if(this->_cents == rhs._cents){
        if(this->_dollars == rhs._dollars){
            return false;
        }
    }
    if(this->_dollars == rhs._dollars){
        if(this->_cents == rhs._cents){
            return false;
        }
    }
    return true;
}
bool Money::operator <(const Money & rhs)const{
    if (*this == 0 && rhs != 0){
        return true;
    }
    if(this->_dollars < rhs._dollars){
        if(this->_cents < rhs._cents){
            return true;
        }
    }
    if(this->_cents < rhs._cents){
        if(this->_dollars < rhs._dollars){
            return true;
        }
    }
    return false;

}
// Canonical
//bool operator>(const Money &lhs, const Money &rhs) { return rhs < lhs; }
//bool Money::operator >(const Money & rhs)const {return rhs < this;}

bool Money::operator >(const Money & rhs)const{
    if (*this == 0 && rhs != 0){
        return false;
    }
    if(this->_cents > rhs._cents){
        if(this->_dollars > rhs._dollars){
            return true;
        }
    }
    if(this->_dollars > rhs._dollars){
        if(this->_cents > rhs._cents){
            return true;
        }
        return true;
    }
    return false;
}
bool Money::operator <=(const Money & rhs)const{
    if(this->_cents <= rhs._cents){
        if(this->_dollars <= rhs._dollars){
            return true;
        }
    }
    if(this->_dollars <= rhs._dollars){
        if(this->_cents <= rhs._cents){
            return true;
        }
    }
    return false;
}
bool Money::operator >=(const Money & rhs)const{
    if(this->_cents >= rhs._cents){
        if(this->_dollars >= rhs._dollars){
            return true;
        }
    }
    if(this->_dollars >= rhs._dollars){
        if(this->_cents >= rhs._cents){
            return true;
        }
    }
    return false;
}






Money::Money()
{
    //Default Constructor
    _sign = 0;
    _cents = 0;
    _dollars = 0;
    //std::cout << "I made a default money object and set it to: $" << _dollars << "." << _cents << "\n";
}
Money::Money(int userDollars , int userCents)
{
    //Primary Constructor
    if(userDollars < 0){
        _sign = 1;
        userDollars *= -1;
    }
    _cents = userCents;
    _dollars = userDollars;

    //std::cout << "I made a money object and set it to: $" << _dollars << "." << _cents << "\n";
}

Money::Money(double userMoney)
{
    int sign = 0;
    if(userMoney < 0 )
    {
        sign = 1;
        userMoney = userMoney * -1;
    }
    //perform double coversion to int
    int userDollars = int(userMoney);
    //isolate the cents
    double temp = (userMoney - userDollars)*100;
    //knock the double back down to an int
    int userCents = int(temp);
    //insure correct rounding
    if((temp - userCents) >= .5)
    {
        userCents++;
    }
    //set pos/neg sign
    if(sign == 1){
        _sign = 1;
    }
    _cents = userCents;
    _dollars = userDollars;
}
void Money::setMoney(double userMoney)
{
// set the money value
    int sign = 0;
    if(userMoney < 0 )
    {
        sign = 1;
        userMoney = userMoney * -1;
    }
    int userDollars = int(userMoney);
    std::cout << userDollars << std::endl;
    double temp = (userMoney - userDollars)*100;
    int userCents = int(temp);
    if((temp - userCents) >= .5 )
    {
        userCents++;
    }
    if(userCents == 0)
    {
        userCents = .00;
    }
    if(sign == 1)
    {
        _sign = 1;
    }
    _cents = userCents;
    _dollars = userDollars;
}
double Money::getMoney()const
{
    double userCents = _cents;
    double userDollars = _dollars;
    userCents = userCents/100;
    if(userCents == 0){
        userCents = .00;
    }
    std::cout << (userDollars + userCents) << std::endl;
    return (userDollars + userCents);
}
Money::~Money()
{
    //std::cout << "I Copied a Money object \n";
// copy operator
}
Money Money::operator =(const Money & rhs){
    this->_cents = this->_cents + rhs._cents;
    this ->_dollars = this->_dollars + rhs._dollars;
    return *this;
}







/*
bool operator<=(const Money &lhs, const Money &rhs) {
    return !(rhs < lhs);
}

bool operator>=(const Money &lhs, const Money &rhs) {
    return !(lhs < rhs);
}

// Canonical
bool operator!=(const Money &lhs, const Money &rhs) {
    return !(lhs == rhs);
}*/
