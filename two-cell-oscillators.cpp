#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

const int max_x = 4;
const int max_y = 4;
const int max_t = 512;
const int number_of_transitions = 102;
const std::string output_filename = "oscillators-7x7.csv";
const std::string log_filename = "log-7x7";
const int reporting_interval = 5000000;

int transition_from_cells(int parent_0,
                          int parent_1,
                          int parent_2,
                          int parent_3,
                          int parent_4,
                          int parent_5,
                          int parent_6,
                          int parent_7,
                          int parent_8){
  int index = (parent_0<<8)|(parent_1<<7)|(parent_2<<6)|(parent_3<<5)|(parent_4<<4)|(parent_5<<3)|(parent_6<<2)|(parent_7<<1)|parent_8;
  static const int lookup_table[512] = {0,1,2,6,1,3,6,13,2,5,4,17,6,14,12,22,1,8,5,16,3,9,14,24,6,16,17,30,13,24,22,35,2,5,7,18,5,15,18,29,4,11,10,27,17,21,28,37,6,16,18,31,14,25,23,41,12,26,28,39,22,40,36,45,1,3,5,14,8,9,16,24,5,15,11,21,16,25,26,40,3,9,15,25,9,19,25,33,14,25,21,34,24,33,40,43,6,14,18,23,16,25,31,41,17,21,27,38,30,34,39,44,13,24,29,41,24,33,41,46,22,40,37,44,35,43,45,49,2,6,4,12,5,14,17,22,7,18,10,28,18,23,28,36,5,16,11,26,15,25,21,40,18,31,27,39,29,41,37,45,4,17,10,28,11,21,27,37,10,27,20,32,27,38,32,42,17,30,27,39,21,34,38,44,28,39,32,47,37,44,42,48,6,13,17,22,16,24,30,35,18,29,27,37,31,41,39,45,14,24,21,40,25,33,34,43,23,41,38,44,41,46,44,49,12,22,28,36,26,40,39,45,28,37,32,42,39,44,47,48,22,35,37,45,40,43,44,49,36,45,42,48,45,49,48,50,51,52,53,57,52,54,57,64,53,56,55,68,57,65,63,73,52,59,56,67,54,60,65,75,57,67,68,81,64,75,73,86,53,56,58,69,56,66,69,80,55,62,61,78,68,72,79,88,57,67,69,82,65,76,74,92,63,77,79,90,73,91,87,96,52,54,56,65,59,60,67,75,56,66,62,72,67,76,77,91,54,60,66,76,60,70,76,84,65,76,72,85,75,84,91,94,57,65,69,74,67,76,82,92,68,72,78,89,81,85,90,95,64,75,80,92,75,84,92,97,73,91,88,95,86,94,96,100,53,57,55,63,56,65,68,73,58,69,61,79,69,74,79,87,56,67,62,77,66,76,72,91,69,82,78,90,80,92,88,96,55,68,61,79,62,72,78,88,61,78,71,83,78,89,83,93,68,81,78,90,72,85,89,95,79,90,83,98,88,95,93,99,57,64,68,73,67,75,81,86,69,80,78,88,82,92,90,96,65,75,72,91,76,84,85,94,74,92,89,95,92,97,95,100,63,73,79,87,77,91,90,96,79,88,83,93,90,95,98,99,73,86,88,96,91,94,95,100,87,96,93,99,96,100,99,101};
  // B0-0
  // B1c-1 B1e-2
  // B2c-3 B2e-4 B2k-5 B2a-6 B2i-7 B2n-8
  // B3c-9 B3e-10 B3k-11 B3a-12 B3i-13 B3n-14 B3y-15 B3q-16 B3j-17 B3r-18
  // B4c-19 B4e-20 B4k-21 B4a-22 B4i-23 B4n-24 B4y-25 B4q-26 B4j-27 B4r-28 B4t-29 B4w-30 B4z-31
  // B5c-32 B5e-33 B5k-34 B5a-35 B5i-36 B5n-37 B5y-38 B5q-39 B5j-40 B5r-41
  // B6c-42 B6e-43 B6k-44 B6a-45 B6i-46 B6n-47
  // B7c-48 B7e-49
  // B8-50
  // S0-51
  // S1c-52 S1e-53
  // S2c-54 S2e-55 S2k-56 S2a-57 S2i-58 S2n-59
  // S3c-60 S3e-61 S3k-62 S3a-63 S3i-64 S3n-65 S3y-66 S3q-67 S3j-68 S3r-69
  // S4c-70 S4e-71 S4k-72 S4a-73 S4i-74 S4n-75 S4y-76 S4q-77 S4j-78 S4r-79 S4t-80 S4w-81 S4z-82
  // S5c-83 S5e-84 S5k-85 S5a-86 S5i-87 S5n-88 S5y-89 S5q-90 S5j-91 S5r-92
  // S6c-93 S6e-94 S6k-95 S6a-96 S6i-97 S6n-98
  // S7c-99 S7e-100
  // S8-101
  return lookup_table[index];
}

std::string rulestring_from_rule(int rule[number_of_transitions]){
  static const std::string letters = "cekainyqjrtwz";
  static const int numbers_of_letters[9] = {1,2,6,10,13,10,6,2,1};
  std::string rulestring = "";
  int transition = 0;
  for(int BS=0; BS<2; BS++){
    if(BS){
      rulestring += "/S";
    } else {
      rulestring += "B";
    }
    for(int number_of_neighbours = 0; number_of_neighbours <= 8; number_of_neighbours++){
      int number_of_letters = numbers_of_letters[number_of_neighbours];
      std::string alive = "";
      std::string dead = "";
      for(int letter_number=0; letter_number < number_of_letters; letter_number++){
        char letter = letters[letter_number];
        if(rule[transition]){
          alive += letter;
        } else {
          dead += letter;
        }
        transition++;
      }
      int number_alive = alive.size();
      if(number_alive){
        rulestring += std::to_string(number_of_neighbours);
        if(number_alive != number_of_letters){
          if(number_alive*2 <= number_of_letters){
            std::sort(alive.begin(), alive.end());
            rulestring += alive;
          } else {
            std::sort(dead.begin(), dead.end());
            rulestring += "-" + dead;
          }
        }
      }
    }
  }
  return rulestring;
}

std::string minrulestring(int rule[number_of_transitions]){
  int minrule[number_of_transitions];
  for(int transition = 0; transition < number_of_transitions; transition++){
    if(rule[transition] == 1){
      minrule[transition] = 1;
    } else {
      minrule[transition] = 0;
    }
  }
  return rulestring_from_rule(minrule);
}

std::string maxrulestring(int rule[number_of_transitions]){
  int maxrule[number_of_transitions];
  for(int transition = 0; transition < number_of_transitions; transition++){
    if(rule[transition] == 0){
      maxrule[transition] = 0;
    } else {
      maxrule[transition] = 1;
    }
  }
  return rulestring_from_rule(maxrule);
}

int cells[max_t][max_y+3][max_x+3];

int main(){
  std::ofstream output_file;
  output_file.open(output_filename);
  std::ofstream log_file;
  log_file.open(log_filename);

  // Grid of cells
  for(int x = 0; x < max_x+3; x++){
    for(int y = 0; y < max_y+3; y++){
      for(int t = 0; t < max_t; t++){
        cells[t][y][x] = 0;
      }
    }
  }
  cells[0][0][1] = 1;

  // Rules which apply at that generation (-1 if undetermined)
  int rules[max_t][number_of_transitions];
  for(int t = 0; t < max_t; t++){
    for(int transition = 0; transition < number_of_transitions; transition++){
      rules[t][transition] = -1;
    }
    rules[t][0] = 0; // B0
    rules[t][1] = 0; // B1c
    rules[t][2] = 0; // B1e
    rules[t][6] = 1; // B2a
  }

  // Bounding Box
  int x_bound[max_t];
  int y_bound[max_t];
  for(int t = 0; t < max_t; t++){
    x_bound[t] = y_bound[t] = 0;
  }
  x_bound[0] = 2;
  y_bound[0] = 1;

  // Which transitions need to be set
  int new_transitions[max_t][number_of_transitions];
  for(int t = 0; t < max_t; t++){
    for(int transition = 0; transition < number_of_transitions; transition++){
      new_transitions[t][transition] = -1;
    }
  }

  // Number of transitions needing to be set
  int number_of_new_transitions[max_t];
  for(int t = 0; t < max_t; t++){
    number_of_new_transitions[t] = -1;
  }

  // Integer < pow(2,number_of_new_transitions) to specify in binary which transitions to set
  int transitions_to_set[max_t];
  for(int t = 0; t < max_t; t++){
    transitions_to_set[t] = -1;
  }

  // Current generation
  int t = 0;

  // output_file << "Period,Minrule,Maxrule" << std::endl;

  bool  completion_flag = false;
  int number_of_reports = 0;
  int number_of_oscillators = 0;
  while(!completion_flag){
    for(int count = 0; count < reporting_interval; count++){
      if(transitions_to_set[t] == -1){
        transitions_to_set[t] = 0;

        for(int x=0; x<=x_bound[t]; x++){
          for(int y=0; y<=y_bound[t]; y++){
            int transition = transition_from_cells(
              cells[t][y][x],
              cells[t][y][x+1],
              cells[t][y+1][x+1],
              cells[t][y+1][x],
              x==0 ? cells[t][y+1][1] : cells[t][y+1][x-1],
              x==0 ? cells[t][y][1] : cells[t][y][x-1],
              x==0 ? (y==0 ? cells[t][1][1] : cells[t][y-1][1]) : (y==0 ? cells[t][1][x-1] : cells[t][y-1][x-1]),
              y==0 ? cells[t][1][x] : cells[t][y-1][x],
              y==0 ? cells[t][1][x+1] : cells[t][y-1][x+1]
            );
            if((rules[t][transition] == -1) && (new_transitions[t][transition] == -1)){
              new_transitions[t][transition] = transition;
            }
          }
        }

        //Rearrange new_transitions[t] to get new transitions at the front, and count them
        number_of_new_transitions[t] = 0;
        for(int transition = 0; transition < number_of_transitions; transition++){
          if(new_transitions[t][transition]!=-1){
            new_transitions[t][transition] = -1;
            new_transitions[t][number_of_new_transitions[t]] = transition;
            number_of_new_transitions[t]++;
          }
        }
        if(number_of_new_transitions[t]>30){
          log_file << "Possible sign error caused by number_of_new_transitions > 30 (t=" << t << ", " << minrulestring(rules[t]) << ", " << maxrulestring(rules[t]) << ")" << std::endl;
        }
      }

      // Copy rule to next generation
      for(int transition = 0; transition < number_of_transitions; transition++){
        rules[t+1][transition] = rules[t][transition];
      }

      // std::cout << "Parent rule:" << minrulestring(rules[t]) << ", " << maxrulestring(rules[t]) << std::endl;
      // for(int transition = 0; transition < number_of_transitions; transition++){
      //   std::cout << rules[t][transition];
      // }
      // std::cout << std::endl;
      // std::cout << "Parent pattern: (t=" << t << ")" << std::endl;
      // for(int y = 0; y<y_bound[t]; y++){
      //   for(int x = 0; x<x_bound[t]; x++){
      //     std::cout << cells[t][y][x];
      //   }
      //   std::cout << std::endl;
      // }

      // Set rule for next generation
      for(int i = 0; i < number_of_new_transitions[t]; i++){
        rules[t+1][new_transitions[t][i]] = !!(transitions_to_set[t] & (1 << i)); // Check ith bit of transitions_to_set[t]
      }
      transitions_to_set[t]++;

      // Create new Grid
      for(int y=0; y<=y_bound[t]; y++){
        for(int x=0; x<=x_bound[t]; x++){

          int transition = transition_from_cells(
            cells[t][y][x],
            cells[t][y][x+1],
            cells[t][y+1][x+1],
            cells[t][y+1][x],
            x==0 ? cells[t][y+1][1] : cells[t][y+1][x-1],
            x==0 ? cells[t][y][1] : cells[t][y][x-1],
            x==0 ? (y==0 ? cells[t][1][1] : cells[t][y-1][1]) : (y==0 ? cells[t][1][x-1] : cells[t][y-1][x-1]),
            y==0 ? cells[t][1][x] : cells[t][y-1][x],
            y==0 ? cells[t][1][x+1] : cells[t][y-1][x+1]
          );
          // std::cout << transition << ",";
          cells[t+1][y][x] = rules[t+1][transition];
          if(cells[t+1][y][x]){
            x_bound[t+1] = std::max(x+1,x_bound[t+1]);
            y_bound[t+1] = std::max(y+1,y_bound[t+1]);
          }
        }
        // std::cout << std::endl;
      }

      // Increase current time
      t++;

      // std::cout << "Child rule:" << minrulestring(rules[t]) << ", " << maxrulestring(rules[t]) << std::endl;
      // for(int transition = 0; transition < number_of_transitions; transition++){
      //   std::cout << rules[t][transition];
      // }
      // std::cout << std::endl;
      // std::cout << "Child pattern: (t=" << t << ")" << std::endl;
      // for(int y = 0; y<y_bound[t]; y++){
      //   for(int x = 0; x<x_bound[t]; x++){
      //     std::cout << cells[t][y][x];
      //   }
      //   std::cout << std::endl;
      // }

      bool backtrack_flag = false;

      // Check if pattern is empty
      if(!x_bound[t]){
        // std::cout << "Empty" << std::endl;
        backtrack_flag = true;
      }

      //Check if pattern is too big
      if(!backtrack_flag){
        if(t == max_t - 1){
          log_file << "Out of time, t=" << t << ", " << minrulestring(rules[t]) << ", " << maxrulestring(rules[t]) << std::endl;
          backtrack_flag = true;
        }
      }
      if(!backtrack_flag){
        if(x_bound[t] > max_x){
          // std::cout << "Out of space (x), t=" << t << ", " << minrulestring(rules[t]) << ", " << maxrulestring(rules[t]) << std::endl;
          backtrack_flag = true;
        }
      }
      if(!backtrack_flag){
        if(y_bound[t] > max_y){
          // std::cout << "Out of space (y), t=" << t << ", " << minrulestring(rules[t]) << ", " << maxrulestring(rules[t]) << std::endl;
          backtrack_flag = true;
        }
      }
      //Check if pattern is exploding
      // x
      if(!backtrack_flag){
        if(rules[t][13] == 1){
          // >= 2 adjacent
          for(int x = 0; x+1<x_bound[t]; x++){
            if(
              (cells[t][y_bound[t]-1][x] == 1)
              && (cells[t][y_bound[t]-1][x+1] == 1)
            ){
              // std::cout << "Exploding 1" << std::endl;
              backtrack_flag = true;
              break;
            }
          }
        } else if(rules[t][3] == 0){
          // Exactly 2 adjacent
          for(int x = 0; x+2<x_bound[t]; x++){
            if(
              (cells[t][y_bound[t]-1][x] == 0)
              && (cells[t][y_bound[t]-1][x+1] == 1)
              && (cells[t][y_bound[t]-1][x+2] == 1)
              && ((x+3 >= x_bound[t]) || (cells[t][y_bound[t]-1][x+3] == 0))
            ){
              // std::cout << "Exploding 2" << std::endl;
              backtrack_flag = true;
              break;
            }
          }
        } else {
          //dead,dead,alive,alive,dead,dead
          for(int x = 0; x+3<x_bound[t]; x++){
            if(
              (cells[t][y_bound[t]-1][x] == 0)
              && (cells[t][y_bound[t]-1][x+1] == 0)
              && (cells[t][y_bound[t]-1][x+2] == 1)
              && (cells[t][y_bound[t]-1][x+3] == 1)
              && ((x+4 >= x_bound[t]) || (cells[t][y_bound[t]-1][x+4] == 0))
              && ((x+5 >= x_bound[t]) || (cells[t][y_bound[t]-1][x+5] == 0))
            ){
              // std::cout << "Exploding 3" << std::endl;
              backtrack_flag = true;
              break;
            }
          }
        }
      }
      // y
      if(!backtrack_flag){
        if(rules[t][13] == 1){
          // >= 2 adjacent
          for(int y = 0; y+1<y_bound[t]; y++){
            if(
              (cells[t][y][x_bound[t]-1] == 1)
              && (cells[t][y+1][x_bound[t]-1] == 1)
            ){
              // std::cout << "Exploding 1" << std::endl;
              backtrack_flag = true;
              break;
            }
          }
        } else if(rules[t][3] == 0){
          // Exactly 2 adjacent
          for(int y = 0; y+2<y_bound[t]; y++){
            if(
              (cells[t][y][x_bound[t]-1] == 0)
              && (cells[t][y+1][x_bound[t]-1] == 1)
              && (cells[t][y+2][x_bound[t]-1] == 1)
              && ((y+3 >= y_bound[t]) || (cells[t][y+3][x_bound[t]-1] == 0))
            ){
              // std::cout << "Exploding 2" << std::endl;
              backtrack_flag = true;
              break;
            }
          }
        } else {
          //dead,dead,alive,alive,dead,dead
          for(int y = 0; y+3<y_bound[t]; y++){
            if(
              (cells[t][y][x_bound[t]-1] == 0)
              && (cells[t][y+1][x_bound[t]-1] == 0)
              && (cells[t][y+2][x_bound[t]-1] == 1)
              && (cells[t][y+3][x_bound[t]-1] == 1)
              && ((y+4 >= y_bound[t]) || (cells[t][y+4][x_bound[t]-1] == 0))
              && ((y+5 >= y_bound[t]) || (cells[t][y+5][x_bound[t]-1] == 0))
            ){
              // std::cout << "Exploding 3" << std::endl;
              backtrack_flag = true;
              break;
            }
          }
        }
      }
      // Check if pattern is repeating
      // Flipped
      if(!backtrack_flag){
        for(int t_past = t; t_past >= 0; t_past--){
          if(!backtrack_flag){
            if(x_bound[t]==y_bound[t_past] && y_bound[t]==x_bound[t_past]){
              int equality_flag = true;
              for(int x=0;x<x_bound[t];x++){
                for(int y=0;y<y_bound[t];y++){
                  if(cells[t][y][x] != cells[t_past][x][y]){
                    equality_flag = false;
                    goto outside_of_loop_0;
                  }
                }
              }
              outside_of_loop_0:
              if(equality_flag){
                backtrack_flag = true;
                if(t_past == 0){
                  output_file << (2*t) << "," << minrulestring(rules[t]) << "," << maxrulestring(rules[t]) << std::endl;
                  number_of_oscillators++;
                } else {
                  // std::cout << "Repeating" << std::endl;
                }
              }
            }
          }
        }
      }
      // Not Flipped
      if(!backtrack_flag){
        for(int t_past = t-1; t_past >= 0; t_past--){
          if(!backtrack_flag){
            if(x_bound[t]==x_bound[t_past] && y_bound[t]==y_bound[t_past]){
              int equality_flag = true;
              for(int x=0;x<x_bound[t];x++){
                for(int y=0;y<y_bound[t];y++){
                  if(cells[t][y][x] != cells[t_past][y][x]){
                    equality_flag = false;
                    goto outside_of_loop_1;
                  }
                }
              }
              outside_of_loop_1:
              if(equality_flag){
                backtrack_flag = true;
                if(t_past == 0){
                  output_file << t << "," << minrulestring(rules[t]) << "," << maxrulestring(rules[t]) << std::endl;
                  number_of_oscillators++;
                } else {
                  // std::cout << "Repeating" << std::endl;
                }
              }
            }
          }
        }
      }
      if(backtrack_flag){
        while(true){
          for(int x = 0; x < x_bound[t]; x++){
            for(int y = 0; y < y_bound[t]; y++){
              cells[t][y][x] = 0;
            }
          }
          for(int transition = 0; transition < number_of_transitions; transition++){
            rules[t][transition] = -1;
          }
          rules[t][0] = 0; // B0
          rules[t][1] = 0; // B1c
          rules[t][2] = 0; // B1e
          rules[t][6] = 1; // B2a
          x_bound[t] = y_bound[t] = 0;
          for(int transition = 0; transition < number_of_transitions; transition++){
            new_transitions[t][transition] = -1;
          }
          number_of_new_transitions[t] = -1;
          transitions_to_set[t] = -1;
          if(t){
            t--;
          } else {
            std::cout << std::endl;
            std::cout << "Search complete" << std::endl;
            completion_flag = true;
            break;
          }
          if(transitions_to_set[t] < (1 << number_of_new_transitions[t])){
            break;
          }
        }
      }
      // std::cout << std::endl;
      if(completion_flag){
        break;
      }
    }
    if(!completion_flag){
      number_of_reports++;
      std::string progress_string = "";
      float progress_float = 0;
      float denominator = 1;
      for(int t_output = 0; t_output<max_t; t_output++){
        if(number_of_new_transitions[t_output]!=-1){
          if(t_output){
            progress_string += ", ";
          }
          progress_string += std::to_string(transitions_to_set[t_output] - 1) + "/" + std::to_string(1 << number_of_new_transitions[t_output]);
          denominator = denominator/(1 << number_of_new_transitions[t_output]);
          progress_float += (transitions_to_set[t_output] - 1)*denominator;
        } else {
          break;
        }
      }
      std::cout << std::endl;
      std::cout << "Number of iterations = " << (number_of_reports*(reporting_interval/1000000)) << " million" << std::endl;
      std::cout << "Number of oscillators = " << number_of_oscillators << std::endl;
      std::cout << "Progress = " << (100*progress_float) << "\% (" << progress_string << ")" << std::endl;
    }
  }
  output_file.close();
  return 0;
}

