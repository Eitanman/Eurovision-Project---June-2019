#include <iostream>
#include <string>
#ifndef  SEAT_H_
#define  SEAT_H_
using std::string;
using std::exception;


// ---------------------------------------------
class NoPrice : public std::exception
//Exception. Meant for "GreenRoomSeat" which doesn't have a price
{
    string exception_massage;
public:
    NoPrice();
    const char* what() const noexcept override;

};

// ---------------------------------------------
class Seat
//The most general type of seats
//Has integers representing a line and a chair
//Abstract
{
    int line;
    int chair;
public:
    Seat(int line, int chair);
    virtual ~Seat(){}
    virtual int price() = 0;
    virtual string location() = 0;
    string seatLocation();
};


// ---------------------------------------------
class GreenRoomSeat: public Seat
//A special seat backstage meant for teams and singers
//Doesn't have a price. Not for sale!
//Not abstract
{
public:
    GreenRoomSeat(int line, int chair);
    int price();
    string location() override;
};

// ---------------------------------------------
class MainHallSeat : public Seat
//A general type for all the seats located in the main hall
//Has an additional base cost of 100
//Abstract
{

protected:
    int main_hall_base;
public:

    MainHallSeat(int line, int chair);
    virtual int price() override = 0;
    virtual string location()  =0 ;
};

// ---------------------------------------------
class SpecialSeat : public MainHallSeat
//A general type for all the "special" seats located in the main hall
//Has an additional base cost of 300
//Abstract
{
protected:
    int special_base;
public:
    SpecialSeat(int line, int chair);
    virtual int price() override = 0;
    virtual string location() =0;
};

// ---------------------------------------------
class GoldenCircleSeat : public SpecialSeat
//A special exclusive type of seats located within the main hall
//Has an additional base cost of 1000
//Not abstract
{
    int golden_base;
    int golden_price;
public:
    GoldenCircleSeat(int line, int chair, int price);

    int price() override;
    string location() override;

};

// ---------------------------------------------
class DisablePodiumSeat : public SpecialSeat
//A special type of seats located within the main hall and meant for people with disabilities
//Has a set price of 200
//Not abstract
{
    int disabled_price;
public:
    explicit DisablePodiumSeat(int line, int chair, int price = 200);
    int price() override;
    string location() override;
};

// ---------------------------------------------
class RegularSeat : public MainHallSeat
//A general type for all the "regular" seats located in the main hall
//These seats are divided into ares marked with capital letters
//Abstract
{
protected:
    char area;

public:
    RegularSeat(char area, int line, int chair);
    virtual int price() override = 0;
    virtual string location() override = 0;
};

// ---------------------------------------------
class FrontRegularSeat: public RegularSeat
//The first kind of regular seats located in the front part of the main-hall
//Has an additional base cost of 500
//Not abstract
{
    int front_base;
    int front_price;
public:
    FrontRegularSeat(char area, int line, int chair, int price);
    int price() override;
    string location() override;
};

// ---------------------------------------------
class MiddleRegularSeat: public RegularSeat
//The second kind of regular seats located in the middle part of the main-hall
//Has an additional base cost of 250
//Not abstract
{
    int middle_base;
    int middle_price;
public:
    MiddleRegularSeat(char area, int line, int chair, int price);
    int price() override;
    string location() override;
};

// ---------------------------------------------
class RearRegularSeat : public RegularSeat
//The first kind of regular seats located in the rear part of the main-hall
//Has no additional base cost
//Not abstract
{
    int rear_price;
public:
    RearRegularSeat(char area, int line, int chair, int price);
    int price() override;
    string location() override;
};

// ---------------------------------------------
#endif
