
#include <iostream>
#include "eurovision.h"

using std::string ;
using std::cout;
using std::endl;
using namespace std;


///////////////////////template get; //////////////////////////

template <typename IteratorType>
IteratorType get(const IteratorType& begin , const IteratorType& end
                             , const int place  ){
//A function used to get the location "i-th biggest"** item in a list, array,etc.
//**if i=1 then the biggest item, if i=2 then the second biggest and so on....
    int size_of_array = 0;
    for (IteratorType iterator = begin   ; !(iterator == end) ; ++iterator ){
        size_of_array++;
    }

    IteratorType* array = new IteratorType[size_of_array] ;
    int count = 0;
    for (IteratorType iterator = begin   ; !(iterator == end) ; ++iterator ){
        array[count] = iterator;
        count++;
    }
    int i, j;
    bool swapped;
    for (i = 0; i < size_of_array; i++)
    {
        swapped = false;
        for (j = 0; j < size_of_array-i-1; j++)
        {
            if (array[j] < array[j+1])
            {

                IteratorType temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }

    IteratorType result = array[place-1];
    delete[] array;
    return result;
}

////////////////////Participant////////////////////////////////

Participant::Participant(string state_name, string song_name
               , int song_time_lenght, string singer_name) {
//A creator for the class participant (which is a state either competing
// or potentially competing in Eurovision)
    this->state_name = state_name;
    this->song_name = song_name;
    this->song_time_lenght = song_time_lenght;
    this->singer_name = singer_name;
    this->is_register = false;
}

string Participant::state(){
//return a given participant's state name
    return  this->state_name ;
}

string Participant::song(){
//return a given participant's song name
    return  this->song_name;
}

int Participant::timeLength() {
//return the time length of a given participant's song
    return this->song_time_lenght;
}

string Participant::singer() {
//return the name of a given participant's singer
    return  this->singer_name;
}

bool Participant::isRegistered() {
//Check if a given participant is registered to compete in Eurovision
    return this->is_register;
}

void Participant::update(string song_name,int song_time_lenght ,
                                                        string singer_name ){
//Update the details for a given participant
    if(this->is_register){
        return;
    }
    if (song_name != EMPTY_STRING){
        this->song_name = song_name;
    }
    if(song_time_lenght != 0){
        this->song_time_lenght = song_time_lenght;
    }
    if(singer_name != EMPTY_STRING){
        this->singer_name = singer_name;
    }
    return;
}

void Participant::updateRegistered(bool status) {
//Update the registration statues for a given participant
    this->is_register = status;
}

std::ostream&  operator<<(std::ostream &out , Participant& p){
//Print the details for given participant based on reference
    out <<"[" + p.state() + "/" + p.song() + "/"  ;
    out << p.timeLength() ;
    out << '/' + p.singer() +"]"  ;
    return out;
}

std::ostream&  operator<<(std::ostream &out , Participant* p){
//Print the details for given participant based on pointer
    out <<"[" + p->state() + "/" + p->song() + "/"  ;
    out << p->timeLength() ;
    out << '/' + p->singer() +"]"  ;
    return out;
}

//////////////// Voter/////////////////////////////////

Voter::Voter (string state_name, enum VoterType voter_type){
//Creator for the class Voter
    this->voter_state = state_name;
    this->voter_type = voter_type;
    this->times_voted = 0;
}

string Voter::state(){
//Return a given voter's state name
    return  this->voter_state;
}

VoterType Voter::voterType(){
//Return a given voter's type
    return  this->voter_type;
}


int Voter::timesOfVotes() {
//Return how many times a given voter has voted
    return  this->times_voted;
}
Voter& Voter::operator++(){
//Add to the number of times a given voter has voted
    this->times_voted++;
    return *this;
}

std::ostream&  operator<<(std::ostream &out , Voter& voter){
//Print the details for a given voter
    out <<"<" + voter.state() + "/"  ;
    if (voter.voterType() == Regular){
        out <<"Regular>";
    }
    else if(voter.voterType() == Judge){
        out <<"Judge>";
    }
    return out;
}

Voter::~Voter(){}
//Empty destructor for Voter class (cause of compiler needs)

//////////////// Vote/////////////////////////////////
Vote::Vote(Voter &voter_t, string state1 , string state2, string state3
        , string state4 , string state5, string state6 , string state7
                            , string state8 , string state9 , string state10){
//A creator for the class Vote
//Can receive up to 10 different states, if the given voter is a judge
    this->voter = &voter_t;
    this->states_voted[0] = state1;
    this->states_voted[1] = state2;
    this->states_voted[2] = state3;
    this->states_voted[3] = state4;
    this->states_voted[4] = state5;
    this->states_voted[5] = state6;
    this->states_voted[6] = state7;
    this->states_voted[7] = state8;
    this->states_voted[8] = state9;
    this->states_voted[9] = state10;
}
Vote::~Vote() {}
//Empty destructor for Vote class (cause of compiler needs)

//////////////// MainControl/////////////////////////////////
MainControl::HelpArray::HelpArray() {
//Creator for HelpArray
//A sub class built to store important information about the
// competition and the participants
    this->participant = nullptr;
    this->state = EMPTY_STRING;
    this ->regular_vote = 0;
    this->judge_vote = 0;
    this->intilize = false;
    this->sorted = NO_USED;
}

MainControl::HelpArray::~HelpArray() {}
//Empty destructor for HelpArray class (cause of compiler needs)

string MainControl::HelpArray::help_state() {
    return this->state;
}
//Return the state name for a given HelpArray

void MainControl::HelpArray::addState(Participant &participant) {
//Add a new state (participant) to the system
    this->participant = &participant ;
    this->state = participant.state();
}

MainControl::MainControl( int time_length  ,
        int number_of_participants  ,int allowed_votes   ){
//Creator for "MainControl" type
//Basically an operating system for the competition
    this->max_allowed_time_length = time_length;
    this->max_allowed_number_of_participants = number_of_participants;
    this->max_allowed_votes = allowed_votes;

    this->phase = Registration;
    HelpArray** temp = new HelpArray*[max_allowed_number_of_participants] ;
    HelpArray **temp_array = nullptr;
    if (temp_array) {
        ;
    }//For the compiler
    for(int i =0; i<max_allowed_number_of_participants;i++){

        HelpArray  *help_array =  new HelpArray ;

        temp[i] = help_array ;
    }

    this->array = temp;
    this->temp_array = nullptr;
    this->participant_number = 0;
    this->iterator_array = nullptr;
}


MainControl::~MainControl(){
//Destructor for the class "MainControl"
    for (int i = 0; i<this->max_allowed_number_of_participants; i++){
        if(this->array[i]->intilize){
            this->array[i]->participant->updateRegistered(false);
        }

        delete this->array[i];
    }
    delete[] this->array;
    delete[] this->temp_array;
    if(this->iterator_array != nullptr) {
        for (int i = 0; 0 == 0; i++) {
            if (this->iterator_array[i]->i == nullptr) {
                delete this->iterator_array[i];
                break;
            }
            delete this->iterator_array[i];
        }
    }
    delete[] this->iterator_array;
    this->iterator_array = nullptr;
}

void MainControl::setPhase(enum Phase phase){
//Update the phase of the competition
    if((phase - this->phase) == 1){
        this->phase = phase;
    }
}

bool MainControl::stateAlreadyParticipant( Participant& participant) {
//Check if a given state is already registered in the competition
//And therefor can't be registered a 2nd time...
   for(int i = 0; i<max_allowed_number_of_participants ; i++){
       if(this->array[i] != nullptr){
           if(array[i]->help_state() == participant.state()){
               return true;
           }
       }
   }
    return false;
}

bool MainControl::participate(string s) {
//Check if a certain state exists in the system
    for(int i = 0; i<max_allowed_number_of_participants ; i++){
        if(this->array[i] != nullptr){
            if(array[i]->help_state() == s){
                return true;
            }
        }
    }
    return false;
}

static bool legalName(const string state, const string song ,
        const string singer , int song_lenght , int max_lenght  ){
//Check if given details about a participant are legal and the
// participant can join the competition state name, song name, singer
// name and song length Helping function
    if((state != EMPTY_STRING) && (song != EMPTY_STRING) &&
                      (singer != EMPTY_STRING) && (song_lenght <= max_lenght)){
        return true;
    }
    return false;
}


bool MainControl::legalParticipant(Participant& p) {
//Check if a given participant meets all the criteria
    if(legalName(p.state(),p.song(),p.singer(),p.timeLength(),
                                               this->max_allowed_time_length)){
        return true;
    }
    return false;
}

MainControl& MainControl::operator+=(Participant& participant){
//Register a new participant into the competition
    if(this->phase != Registration){
        return *this;
    }
    if(this->participant_number == this->max_allowed_number_of_participants){
        return *this;
    }
    if(this->stateAlreadyParticipant(participant)){
        return *this;
    }
    if(!(this->legalParticipant(participant))){
        return *this;
    }
    return this->registerParticipant(participant);
}

MainControl& MainControl::registerParticipant (Participant& participant){
//helping function
//change the registration status of a participant and update the whole system
//number of participant, so on...
    for(int i = 0; i<this->max_allowed_number_of_participants;i++){
        if (!(this->array[i]->intilize )){
            array[i]->addState(participant);
            array[i]->intilize = true;
            this ->participant_number++;
            participant.updateRegistered(true);
            return *this;
        }
    }
    return *this;
}

MainControl& MainControl::operator-=(Participant& participant){
//Remove a competing participant from the competition
    if(this->phase != Registration){
        return *this;
    }
    if(!participant.isRegistered()){
        return *this;
    }
    return this->unregisterParticipant(participant);
}

MainControl& MainControl::unregisterParticipant (Participant& participant){
//Helping function
//Remove the participant from the system, update his status and update the system
    for(int i = 0; i<this->max_allowed_number_of_participants;i++){
        if (participant.state() == this->array[i]->help_state()) {
            this->array[i]->participant->updateRegistered(false) ;
            delete this->array[i];
            this->array[i] = new HelpArray ;
            this->participant_number--;
            return *this;
        }
    }
    return *this;
}

MainControl& MainControl::operator+=(Vote vote) {
//Add a voter's vote to the system during the voting phase
    bool state_exists = false;
    int voter_state;
    this->sorted();
    for (int i = 0; i < this->participant_number ; i++) {
        if (this->temp_array[i]->state == vote.voter->state()) {
            state_exists = true;
            voter_state = i;
        }
    }
    if ((this->phase != Voting)||(!state_exists)||
                            (!this->temp_array[voter_state]->intilize)) {
        return *this;
    }
    else if (vote.voter->voterType() == Regular) {
        return this->addVoteRegular(vote);
    }
    else if (vote.voter->voterType() == Judge) {
        return this->addVoteJudge(vote);
    }
    return *this;
}

MainControl& MainControl::addVoteRegular(Vote vote){
//helping function
//Add a regular voter's vote
    if (vote.voter->timesOfVotes() >= this->max_allowed_votes) {
        return *this;
    }
    else if (vote.states_voted[0] == vote.voter->state()) {
        return *this;
    }
    else {
        for (int i = 0; i < this->participant_number; i++) {
            if ((this->temp_array[i]->state == vote.states_voted[0])
                                        && (this->temp_array[i]->intilize)) {
                ++(*vote.voter);
                temp_array[i]->regular_vote++;
                return *this;
            }
        }
        return *this;
    }
}

MainControl& MainControl::addVoteJudge(Vote vote){
//helping function
//Add a regular voter's vote
    if (vote.voter->timesOfVotes() >= 1) {
        return *this;
    }

    int points_array[10] = {12, 10, 8, 7, 6, 5, 4, 3, 2, 1};
    for (int i = 0; ((i < 10)&&(vote.states_voted[i]!=EMPTY_STRING)) ; i++) {
        for (int d = 0; d < this->participant_number; d++) {
            if ((this->temp_array[d]->state == vote.states_voted[i]) &&
                 (this->temp_array[d]->intilize) && (vote.voter->state()
                                                    != vote.states_voted[i])) {
                ++(*vote.voter);
                temp_array[d]->judge_vote += points_array[i];
            }
        }
    }
    return *this;
}

void MainControl::swap(MainControl::HelpArray **a, HelpArray **b) {
//Change the location of two "HelpArrays"
    HelpArray *temp = *a;
    *a = *b;
    *b = temp;

}
void MainControl::sorted() {
//Sort the helping array of only the competing states according to the ABC
    if(this->temp_array != nullptr){
        delete[] this->temp_array;
        this->temp_array = nullptr;

    }
    int temp_array_place = 0;
    HelpArray** temp_help_array = new HelpArray*[participant_number+1] ;
    for(int i = 0; i<max_allowed_number_of_participants;i++){
        if (this->array[i]->intilize == true){
            temp_help_array[temp_array_place] = this->array[i];
            temp_array_place++;
        }
    }
    temp_help_array[participant_number] = nullptr;
    this->temp_array = temp_help_array;
    int i, j;
    bool swapped;
    for (i = 0; i < this->participant_number; i++)
    {
        swapped = false;
        for (j = 0; j < this->participant_number-i-1; j++)
        {
            if (this->temp_array[j]->state > this->temp_array[j+1]->state)
            {
                swap(&this->temp_array[j] , &this->temp_array[j+1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }

}
std::ostream &operator<<(std::ostream &out ,  MainControl& main ){
//print the competition's current
    out << "{" << endl;
    if(main.phase == Registration){
        out<< "Registration" << endl ;
        main.sorted();
        for(int i = 0 ; i<main.participant_number;i++){
            out << *(main.temp_array[i]->participant) << endl;
        }
    }
    if(main.phase == Contest){
        out << "Contest" << endl;
    }
    if(main.phase == Voting) {
        out << "Voting" << endl;
        main.sorted();
        for(int i = 0 ; i<main.participant_number;i++){
            out << main.temp_array[i]->state + " : Regular(";
            out << main.temp_array[i]->regular_vote;
            out << ") Judge(";
            out << main.temp_array[i]->judge_vote;
            out << ")" << endl;
        }
    }
    out << "}" << endl;;
    delete[] main.temp_array;
    main.temp_array = nullptr;
    return out;
}

///////////// iterator function //////////////////////////////
void MainControl::Iterator::addParticipant(HelpArray *p) {
//helping function
//Connect a participant to the relevant iterator
    this->i = p;
    this->its = nullptr;
}

void MainControl::destroyIterator() {
//Destroy a given iterator
    for(int i = 0; 0 == 0;i++){
        if(this->iterator_array[i]->i == nullptr){
          delete this->iterator_array[i];
           break;
     }
       delete this->iterator_array[i];
 }
   delete[] this->iterator_array;
   this->iterator_array = nullptr;
}

void MainControl::iteratorInitilize() {
//Initialize a given iterator
    if(this->iterator_array != nullptr){
        this->destroyIterator();
    }
    this->sorted();
    MainControl::Iterator** iterator_array =
            new MainControl::Iterator*[this->participant_number+1] ;
    for(int i =0;i<this->participant_number;i++){
        MainControl::Iterator  *tempIterator =  new MainControl::Iterator ;
        iterator_array[i] = tempIterator ;
        iterator_array[i]->addParticipant(this->temp_array[i]);
        iterator_array[i]->iterator_place = i;
    }
    iterator_array[this->participant_number] = new MainControl::Iterator;
    for(int i =0;i<this->participant_number;i++){
        iterator_array[i]->its = iterator_array;
    }
    this->iterator_array = iterator_array;
}

MainControl::Iterator::Iterator(){
//Iterator creator
    this->i = nullptr ;
    this->its = nullptr;
    this->iterator_place = 0;
}

MainControl::Iterator MainControl::begin(){
//Set an iterator for a given array to the array's first item
    this->iteratorInitilize();
    return *this->iterator_array[0];
}

MainControl::Iterator MainControl::end(){
//Set an iterator for a given array to the array's last item
    if (this->iterator_array == nullptr){ this->iteratorInitilize();}
    return *this->iterator_array[this->participant_number];
}

MainControl::Iterator& MainControl::Iterator::operator++(){
//Move an iterator for a given array to the next item in the array
    for(int i =0; this->its[i]->i != nullptr;i++){
        if(this->i == this->its[i]->i ){
            *this = *this->its[i+1];
            return *this;
        }
    }
    return *this; // maybe do assert or return null idk;
}
//function has 2 uses. Depends if helping integer "sorted"* within HelpArray is set to "NO_USED"** or not
//*"sorted" is an integer where we count a given participants' vote count (Regular, Judge, or All)
//**"NO_USED" is a "define" meant to show that we haven't started the sorting part of the voting phase yet
//If sorted is set to "NO_USED", function advances the iterator across the array
//If sorted is not set to "NO_USED", function sorts out a given array based on its "sorted" values
bool  MainControl::Iterator::operator<(MainControl::Iterator it) {

        if (this->i == nullptr) { return false; }
        if (this->i->sorted == NO_USED){
            if((this->iterator_place <it.iterator_place) || (it.i == nullptr)) {
            return true;
            }
            else
                return false;
        }
        if (it.i == nullptr){
            return false;
        }
        if (this->i->sorted < it.i->sorted){ return true;}
        if(this->i->sorted == it.i->sorted){
            if(this->i->state > it.i->state){ return false;}
            else return true;
        }
        return false;

}
bool  MainControl::Iterator::operator==(MainControl::Iterator it) {
//Checks that two iterator values are the same
    if(this->i == it.i){ return true;}
    return false;
}

Participant*  MainControl::Iterator::operator*(){
//Gives the address to a participant attached to a given iterator
    return this->i->participant ;
}

string MainControl::operator()(int i , VoterType voterType){
//Based on the kind of "voterType" put in, function prints out the "i-th biggest"** participant according to votes
//**If i=1 then biggest, if i=2 then second biggest, if i=3 then 3rd biggest and so on...
    if(this->participant_number<i){ return "";}
    if(i == 0) {return "";}
    if (voterType == Regular){
        return this->getRegularVote(i);
    }
    if (voterType == Judge){
        return this->getJudgeVote(i);
    }
    if (voterType == All){
        return this->getAllVote(i);
    }
    return "";
}

string MainControl::getRegularVote(int i){
//helping function
//Calculates the "i-th biggest" participant based on Regular vote count
    MainControl::Iterator helpArray;
    for (helpArray = this->begin(); helpArray < this->end(); ++helpArray){
        helpArray.i->sorted = helpArray.i->regular_vote;
    }
    MainControl::Iterator result = get(this->begin(),this->end() , i );
    for (helpArray = this->begin(); !(helpArray == this->end()); ++helpArray){
        helpArray.i->sorted = NO_USED;
    }
    return result.i->help_state();
}

string MainControl::getJudgeVote(int i){
//helping function
//Calculates the "i-th biggest" participant based on Judge vote count
    MainControl::Iterator helpArray;
    for (helpArray = this->begin(); helpArray < this->end(); ++helpArray){
        helpArray.i->sorted = helpArray.i->judge_vote;
    }
    MainControl::Iterator result = get(this->begin(),this->end() , i );
    for (helpArray = this->begin(); !(helpArray == this->end()); ++helpArray){
        helpArray.i->sorted = NO_USED;
    }
    return result.i->help_state();
}

string MainControl::getAllVote(int i){
//helping function
//Calculates the "i-th biggest" participant based on all the votes, Judge and Regular
    MainControl::Iterator helpArray;
    for (helpArray = this->begin(); helpArray < this->end(); ++helpArray){
        helpArray.i->sorted = helpArray.i->judge_vote +
                helpArray.i->regular_vote ;
    }
    MainControl::Iterator result = get(this->begin(),this->end() , i );
    for (helpArray = this->begin(); !(helpArray == this->end()); ++helpArray){
        helpArray.i->sorted = NO_USED;
    }
    return result.i->help_state();
}
