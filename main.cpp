#include "Sudoku.cpp"
int main(int argc, char *argv[]){
  Sudoku s{};
//   std::string sudoku_input{R"(
// | 531 | 246 | 789 | 
// | 600 | 000 | 000 | 
// | 098 | 000 | 000 | 
//   ----------------  
// | 800 | 000 | 000 | 
// | 400 | 000 | 000 | 
// | 700 | 000 | 000 | 
//   ----------------  
// | 060 | 000 | 280 | 
// | 000 | 000 | 005 | 
// | 000 | 000 | 000 | 

// )"};
  std::string sudoku_input{R"(

   | 000 | 000 | 000 |
   | 001 | 203 | 600 |
   | 059 | 801 | 420 |
    =================
   | 037 | 000 | 000 |
   | 000 | 000 | 000 |
   | 096 | 000 | 000 |
    =================
   | 042 | 706 | 580 |
   | 008 | 902 | 700 |
   | 000 | 000 | 000 |

)"};
  s.assign(sudoku_input);
  s.show();
  s.solve(false);
  //alter to true when you wanna see the process of solving(´・ω・｀)
  s.show_solved();
  
  return 0;
}
