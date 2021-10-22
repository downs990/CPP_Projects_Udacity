#include <cassert>


//Base class 
class Heart{
    private: 
        int rate{80};

        // Allows Human to have direct access to the private variable 'rate'. 
        friend class Human;
};

// Friend class 
class Human{
    public:
        Heart heart;
        void Exercise(){heart.rate = 150;}
        int HeartRate(){return heart.rate;}
};




int main(){
    Human human;
    assert(human.HeartRate() == 80);
    human.Exercise();
    assert(human.HeartRate() == 150);
}