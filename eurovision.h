
#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#define EMPTY_STRING ""
#define NO_USED -1
using std::string ;
// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------
template <typename IteratorType>
IteratorType get(const IteratorType& begin , const IteratorType& end
                             , const int place  );
class Participant
{
// A country competing in the Eurovision
string state_name;
string song_name;
int  song_time_lenght;
string singer_name;
bool is_register;
public :

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend  is allowed here,easy we at CS.

// check if need to do destructor

Participant(string state_name , string song_name , int song_time_lenght
                                                        , string singer_name);
Participant(const Participant&) = delete;
void operator=(const Participant&) = delete;
void update(string song_name,int song_time_lenght , string singer_name );
void updateRegistered(bool status);
string  state();
string  song();
int timeLength();
string singer();
bool isRegistered();

};

std::ostream &operator<<(std::ostream &out ,  Participant&);
std::ostream &operator<<(std::ostream &out , Participant* p);
//---------------------------------------------------


class Voter
{
// Either a proffesional judge or a citizen from a participant state who vote for the winners
string voter_state;
VoterType voter_type;
int times_voted;

public :

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.
// NO friend is allowed here.

    explicit Voter (string state_name = EMPTY_STRING,
                                                VoterType voter_type = Regular);

    Voter(const Voter&) = delete;
    string state();
    VoterType voterType();
    int timesOfVotes();
    Voter& operator++();
    ~Voter();
};

std::ostream &operator<<(std::ostream &out ,  Voter&);
// -----------------------------------------------------------

struct Vote
// A judge's or a citizen's vote
{
Voter *voter;
string states_voted[10];

public:
// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.
explicit Vote (Voter &voter_t, string state1 =EMPTY_STRING ,
        string state2 = EMPTY_STRING, string state3 = EMPTY_STRING
        ,string state4 = EMPTY_STRING, string state5 = EMPTY_STRING,
        string state6 = EMPTY_STRING, string state7 = EMPTY_STRING,
        string state8 = EMPTY_STRING, string state9 = EMPTY_STRING
        , string state10 = EMPTY_STRING);
~Vote();
};

// -----------------------------------------------------------
class MainControl
{
// The main control system for the competition
    friend  std::ostream &operator<<(std::ostream &out ,  MainControl& main);
    class HelpArray{
//A helpful storage for information we need during the competition's run
        public:
        Participant* participant ;
        string state ;
        int regular_vote;
        int judge_vote;
        bool intilize;
        int sorted ;
        HelpArray();
        ~HelpArray();
        string help_state() ;
        void addState(Participant &participant);
    };

public:
    class Iterator {
        //A mechanism to navigate through different lists, arrays, etc.
    public:
        int iterator_place;
        HelpArray * i;
        Iterator();
        void addParticipant(HelpArray *p);
        Iterator** its;
        bool operator<(Iterator a);
        bool  operator==(Iterator it);
        Iterator& operator++();
        Participant* operator*();
    };


private:
int max_allowed_time_length;
int max_allowed_number_of_participants;
int max_allowed_votes;
enum Phase phase;
HelpArray **array;
HelpArray **temp_array;
int participant_number;
Iterator** iterator_array;
bool stateAlreadyParticipant( Participant& participant);
void sorted ();
void swap(HelpArray** a , HelpArray **b );
void iteratorInitilize();
void destroyIterator();

// NIRZE GAM MASHEHO SHE KASHOR LA MISHTATFIM KANIRE MAARAH
public :




    Iterator begin();
    Iterator end();
    explicit MainControl( int time_length = 180 , int number_of_participants =26
                                                    ,int allowed_votes = 5  ) ;
    ~MainControl();
    void setPhase(enum Phase phase);
    MainControl& operator+=(Participant& participant);
    MainControl& operator-=(Participant& participant);
    MainControl& operator+=(Vote Vote);
    bool legalParticipant( Participant& participant);
    bool participate(string s);
    string operator()(int i , VoterType voterType);

    //help functions:
    MainControl& addVoteRegular(Vote vote);
    MainControl& addVoteJudge(Vote vote);
    MainControl& registerParticipant (Participant& participant);
    MainControl& unregisterParticipant (Participant& participant);
    string getRegularVote(int i);
    string getJudgeVote(int i);
    string getAllVote(int i);



};

// -----------------------------------------------------------

#endif
