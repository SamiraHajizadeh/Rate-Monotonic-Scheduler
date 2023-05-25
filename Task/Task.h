#ifndef Task_h
#define Task_h
#include "Arduino.h"

class Task {
  public:
    char name;
    int C;
    int D;
    int T;

    Task (){};

    Task (char name_, int C_, int D_, int T_){
        name = name_;
        C = C_;
        T = T_;
        D = D_;
        };

    void do_task(){
        Serial.print(name);
    }
};

#endif
