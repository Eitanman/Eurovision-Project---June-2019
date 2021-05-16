#include <iostream>
#include <string>
#include "seat.h"
using std::string;
using std::exception;
using std::cout;
using std::endl;




///////////////////////////Seat////////////////////////

Seat::Seat(int line, int chair) :line(line), chair(chair){}
//Creator for the abstract class "Seat"

string Seat::seatLocation() {
//Print out a given Seat location
    string location = "line: " + std::to_string(this->line) + ", "
                      + "chair: " + std::to_string(this->chair);
    return location;
}


/////////////////////////GreenRoomSeat///////////////////

GreenRoomSeat::GreenRoomSeat(int line, int chair): Seat(line,chair){}
//Creator for GreenRoomSeat

string GreenRoomSeat::location() {
//Print out a given GreenRoomSeat location
    string location = "Green Room-> " + seatLocation();
    return location;
}

const char* NoPrice::what() const noexcept {
//Prints the relevant message about the fact that GreenRoomSeats have no price
    return "Not For Sale !";
}

NoPrice::NoPrice() {
//helping function. Prints out "No-price" error message
    exception_massage = what();
}

int GreenRoomSeat::price(){
//Print out a given GreenRoomSeat price (only it prints out an error since these seats have no price)
    NoPrice what ;
    throw what;
}



///////////////////////MainHallSeat////////////////////

MainHallSeat::MainHallSeat(int line, int chair): Seat(line,chair), main_hall_base(100) {}
//Creator for the abstract class "MainHallSeat"


/////////////////////SpecialSeat///////////////////

SpecialSeat::SpecialSeat(int line, int chair): MainHallSeat(line,chair), special_base(300) {}
//Creator for the abstract class "SpecialSeat"

///////////////////DisablePodiumSeat///////////////

DisablePodiumSeat::DisablePodiumSeat(int line, int chair, int price) : SpecialSeat(line,chair), disabled_price(200){}
//Creator for "DisablePodiumSeat"

string DisablePodiumSeat::location() {
//Print out a given DisablePodiumSeat location
    string location = "Disable Podium-> " + seatLocation() ;
    return location;
}

int DisablePodiumSeat::price(){
//Print out a given DisablePodiumSeat price
    return this->disabled_price;
}

////////////////GoldenCircleSeat//////////////////

GoldenCircleSeat::GoldenCircleSeat(int line, int chair, int price) : SpecialSeat(line,chair), golden_base(1000){
//Creator for "GoldenCircleSeat"
    (((this->golden_price = price) +=this->special_base)+= this->golden_base)+=this->main_hall_base;}

string GoldenCircleSeat::location() {
//Print out a given GoldenCircleSeat location
    string location = "Golden Circle-> " + seatLocation();
    return location;
}

int GoldenCircleSeat::price(){
//Print out a given GoldenCircleSeat price
    return this->golden_price;
}

////////////////RegularSeat///////////////////

RegularSeat::RegularSeat(char area, int line, int chair) : MainHallSeat(line,chair), area(area) {}
//Creator for the abstract type "RegularSeat"


/////////////////FrontRegularSeat////////////////

FrontRegularSeat::FrontRegularSeat(char area , int line, int chair, int price) : RegularSeat(area,line,chair),
front_base(500) {
//Creator for "FrontRegularSeat"
    ((this->front_price = price) += front_base) += this->main_hall_base;
}


string FrontRegularSeat::location() {
//Print out a given FrontRegularSeat location
    string location = "Front-> area: " + string(1,area) + ", " +  seatLocation();
    return location;
}

int FrontRegularSeat::price() {
//Print out a given FrontRegularSeat price
    return this->front_price;
}

///////////////////MiddleRegularSeat////////////

MiddleRegularSeat::MiddleRegularSeat(char area , int line, int chair, int price) : RegularSeat(area,line,chair),
middle_base(250) {
//Creator for "MiddleRegularSeat"
    ((this->middle_price = price) += middle_base) += this->main_hall_base;
}

string MiddleRegularSeat::location() {
//Print out a given MiddleRegularSeat location
    string location = "Middle-> area: " + string(1,area) + ", " +  seatLocation();
    return location;
}

int MiddleRegularSeat::price() {
//Print out a given MiddleRegularSeat price
    return this->middle_price;
}


//////////////RearRegularSeat////////////////


RearRegularSeat::RearRegularSeat(char area , int line, int chair, int price) : RegularSeat(area,line,chair) {
//Creator for "RearRegularSeat"
    (this->rear_price = price) += this->main_hall_base;
}

string RearRegularSeat::location() {
//Print out a given RearRegularSeat location
    string location = "Rear-> area: " + string(1,area) + ", " +  seatLocation();
    return location;
}

int RearRegularSeat::price() {
//Print out a given RearRegularSeat price
    return this->rear_price;
}


