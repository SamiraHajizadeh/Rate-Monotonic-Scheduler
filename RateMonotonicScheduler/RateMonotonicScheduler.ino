#include <Arduino.h>
#include "Task.h"
#define LEN  3

using namespace std;

int gcd(int a, int b){
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

bool comp(Task const & task1, Task const & task2){
    return task1.T < task2.T;
}

bool execution_done(Task task, String schedule, int curr_idx){
  
    int period = task.T;
    int start_point = curr_idx - curr_idx % period;
    String range = schedule.substring(start_point, start_point+period);
    int repeated = 0;
    for (int i = 0; i <= curr_idx - start_point; i++){
      if (range[i] == task.name){
        repeated += 1;
      }
    }
    return repeated >= task.C;
}

Task task('A', 3, 20, 20);
Task task2('B', 2, 5, 5);
Task task3('C', 2, 10, 10);
Task tasks[LEN] = {task, task2, task3};
Task temp;
int ints[LEN];
int hyper_period = 1;
float lcm_num = 1.0;
int loop_count = 0;
String schedule = "";


void setup() {

    Serial.begin(9600);
    
    // finding the hyper period
    for(int i=0; i<LEN ; i++){
      ints[i] = tasks[i].T;}
      
    for(int i=0; i<LEN ; i++){
        lcm_num = (lcm_num / gcd(lcm_num, ints[i])) * ints[i];}

    hyper_period = lcm_num;

}

void loop() {

    if(loop_count < 1){
  
      for(int i=0; i<LEN ; i++){
        Serial.print("name:");
        Serial.print(tasks[i].name);
        Serial.print(" C:");
        Serial.print(tasks[i].C);
        Serial.print(" D:");
        Serial.print(tasks[i].D);
        Serial.print(" T:");
        Serial.print(tasks[i].T);
        Serial.print('\n');
      }
      
      Serial.println("hyper period is: ");
      Serial.println(hyper_period);
      Serial.println('\n');

      // sorting
      for (int i = 0; i < LEN ; i++) {
        for (int j = i; j < LEN ; j++) {
          if (tasks[i].T < tasks[j].T) {
            temp = tasks[i];
            tasks[i] = tasks[j];
            tasks[j] = temp;
          }
        }
      }

      // least upper bound check
      float U = 0;
      for(int i=0; i <LEN ;i++){
          U += tasks[i].C/tasks[i].T;
      }
      if (U <= LEN * (pow(2.0, 1.0/LEN) - 1)){
        Serial.println("Upper Bount Test: Feasible \n");
      }
      else{
        Serial.print("Upper Bount Test: Not Feasible \n");
      }


      // hyperbolic check
      float mult = 1;
      int m = sizeof(tasks);
      for(int i=0; i < m;i++){
        mult *= (tasks[i].C/tasks[i].T + 1);
      }
      if(mult <= 2){
        Serial.println("Hyperbolic Test: Feasible \n");
      }
      else{
        Serial.print("Hyperbolic Test: Not Feasible \n");
      }
      
      //Scheduling
      for(int i=0; i < hyper_period; i++){
        schedule += '-';
        for(int j=0; j<LEN ; j++){
          if (execution_done(tasks[j], schedule, i) == false){
            schedule[i] = tasks[j].name;
            break;
          }
        }
      }

      Serial.println("Final Schedule is:\n");
      Serial.println(schedule);
      Serial.println('\n');
      


      loop_count += 1;

    }
    
}
