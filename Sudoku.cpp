#include <algorithm>
#include <array>
#include <cstddef>
#include <ios>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <iostream>
#include <vector>

class Sudoku{
public:
  using cell_t    = char;
  using row_t     = std::array<cell_t, 9>;
  using body_t    = std::array<row_t, 9>;
  using size_t    = row_t::size_type;
  using point_t   = std::pair<size_t,size_t>;
  using ptArr     = std::array<point_t,9>;
  using sec_t     = std::array<ptArr,9>;
  using bodies_t  = std::vector<body_t>;
  constexpr static sec_t const sections{
    {
      {
	std::make_pair(0, 0),std::make_pair(0, 1),std::make_pair(0, 2),
	std::make_pair(1, 0),std::make_pair(1, 1),std::make_pair(1, 2),
	std::make_pair(2, 0),std::make_pair(2, 1),std::make_pair(2, 2)
      },
      
      {
	std::make_pair(3, 0),std::make_pair(3, 1),std::make_pair(3, 2),
	std::make_pair(4, 0),std::make_pair(4, 1),std::make_pair(4, 2),
	std::make_pair(5, 0),std::make_pair(5, 1),std::make_pair(5, 2)
      },
      
      {
	std::make_pair(6, 0),std::make_pair(6, 1),std::make_pair(6, 2),
	std::make_pair(7, 0),std::make_pair(7, 1),std::make_pair(7, 2),
	std::make_pair(8, 0),std::make_pair(8, 1),std::make_pair(8, 2),
      },

      {
	std::make_pair(0, 3),std::make_pair(0, 4),std::make_pair(0, 5),
	std::make_pair(1, 3),std::make_pair(1, 4),std::make_pair(1, 5),
	std::make_pair(2, 3),std::make_pair(2, 4),std::make_pair(2, 5)
      },
      {
	std::make_pair(3, 3),std::make_pair(3, 4),std::make_pair(3, 5),
	std::make_pair(4, 3),std::make_pair(4, 4),std::make_pair(4, 5),
	std::make_pair(5, 3),std::make_pair(5, 4),std::make_pair(5, 5),

      },
      {
	std::make_pair(6, 3),std::make_pair(6, 4),std::make_pair(6, 5),
	std::make_pair(7, 3),std::make_pair(7, 4),std::make_pair(7, 5),
	std::make_pair(8, 3),std::make_pair(8, 4),std::make_pair(8, 5),
      },
      {
	std::make_pair(0, 6),std::make_pair(0, 7),std::make_pair(0, 8),
	std::make_pair(1, 6),std::make_pair(1, 7),std::make_pair(1, 8),
	std::make_pair(2, 6),std::make_pair(2, 7),std::make_pair(2, 8),

      },
      {
	std::make_pair(3, 6),std::make_pair(3, 7),std::make_pair(3, 8),
	std::make_pair(4, 6),std::make_pair(4, 7),std::make_pair(4, 8),
	std::make_pair(5, 6),std::make_pair(5, 7),std::make_pair(5, 8),

      },
      {
	std::make_pair(6, 6),std::make_pair(6, 7),std::make_pair(6, 8),
	std::make_pair(7, 6),std::make_pair(7, 7),std::make_pair(7, 8),
	std::make_pair(8, 6),std::make_pair(8, 7),std::make_pair(8, 8),
      }
    }
  };
  bodies_t solved_patterns{};
  bool solved{false};
  body_t body;
  Sudoku():body{body_t{row_t{'0','0','0',  '0','0','0', '0','0','0'},//0
		       row_t{'0','0','0',  '0','0','0', '0','0','0'},//1
		       row_t{'0','0','0',  '0','0','0', '0','0','0'},//2
		       row_t{'0','0','0',  '0','0','0', '0','0','0'},//3
		       row_t{'0','0','0',  '0','0','0', '0','0','0'},//4
		       row_t{'0','0','0',  '0','0','0', '0','0','0'},//5
		       row_t{'0','0','0',  '0','0','0', '0','0','0'},//6
		       row_t{'0','0','0',  '0','0','0', '0','0','0'},//7
		       row_t{'0','0','0',  '0','0','0', '0','0','0'}}}{}
  size_t blank{81};
  void assign(std::string_view const& sudoku_input){
    std::string input(sudoku_input.length(), '0');
    auto siter{std::copy_if(sudoku_input.cbegin(),sudoku_input.cend(), input.begin(),
			    [](char const& ch)->bool{return '0' <= ch and ch <= '9';})};
    if (auto const len{std::distance(input.begin(),siter)}; len != 81){
      throw std::length_error(len < 81?"sudoku_input is too short!":"sudoku_input is too long!");
    }
    blank = std::count(input.begin(),siter, '0');
    for (size_t idx{}; idx != 81; ++idx){
      body[idx/9][idx%9] = input[idx];
    }
  }
  void show(){
    for (size_t r{}; r != 9; ++r){
      auto const& row{body[r]};
      for (size_t c{}; c != 9; ++c){
	if (c == 0){std::printf("| ");}
	
	std::printf("%c%s", row[c], (c+1)%3==0 and c != 0? " | ":"");
      }
      std::printf("%s", (r+1)%3==0 and r != 0? "\n  ----------------  \n":"\n");
    }
    std::cout << "Number of blanc is "<<blank << std::endl;
    std::printf("\n\n\n");
  }
  void show_solved(){
    for (auto const& body:solved_patterns){
      for (size_t r{}; r != 9; ++r){
	auto const& row{body[r]};
	for (size_t c{}; c != 9; ++c){
	  if (c == 0){std::printf("| ");}
	
	  std::printf("%c%s", row[c], (c+1)%3==0 and c != 0? " | ":"");
	}
	std::printf("%s", (r+1)%3==0 and r != 0? "\n  ----------------  \n":"\n");
      }
      //std::cout << "Number of blanc is "<<blank << std::endl;
      std::printf("\n\n\n");
    }
  }
  void assume_n_at_point(Sudoku s, point_t pt, cell_t ch){
    auto const& [r,c]{pt};
    s.body[r][c] = ch;
    --s.blank;
  }

  //methods for solving sudoku
  Sudoku(Sudoku const& copied):body{copied.body},blank{copied.blank},solved_patterns{copied.solved_patterns}{
    //std::cout << "Copy constructor called!" << std::endl;
  }

  //returns row and column where idx is pointing.
  point_t get_point(size_t const& idx){
    if (81 < idx){throw std::runtime_error("try to get_point outside bound!");}
    return std::make_pair(idx/9, idx%9);
  }
  //returns section number of the point (-1< number <9)
  
  bool n_placible_about_row(point_t const& point, cell_t const& N){
    auto const& [r,_]{point};
    return std::none_of(body[r].cbegin(),body[r].cend(), [&N](auto ch){return ch == N;});
  }
  bool n_placible_about_col(point_t const& point, cell_t const& N){
    auto const& [_,c]{point};
    for (size_t r{}; r != 9; ++r){
      if (body[r][c] == N) return false;
    }
    return true;
  }
  size_t get_section(point_t const& point){
    auto const [r,c]{point};
    //////  0   3   6
    //////  1   4   7
    //////  2   5   8
    return  r/3 + (c/3)*3;
  }
  bool n_placible_about_sec(point_t const& point, cell_t const& N){
    auto const& snum{get_section(point)};
    auto const& sec{Sudoku::sections[snum]};
    return std::none_of(sec.cbegin(),sec.cend(),
			[&N,this](auto const& pt){
			  auto const& [r,c]{pt};
			  return body[r][c] == N;
			});
  }
  bool n_placible_at(point_t point, size_t N){
    if (not('0' < N and N <= '9')){throw std::runtime_error("undefined char N assigned!");}
    auto const& [r,c]{point};
    if (not(body[r][c] == '0')){throw std::runtime_error("You're trying to fiddle with a unzero value!");}
    return
      n_placible_about_col(point, N)
                 and
      n_placible_about_row(point, N)
                 and
      
      n_placible_about_sec(point, N);
  }
  point_t previous_pt{};
  point_t get_zero_point(){
    for (size_t r{}; r != 9; ++r){
      for (size_t c{}; c != 9; ++c){
	if(body[r][c] == '0'){
	  return std::make_pair(r,c);
	}
      }
    }
    return std::make_pair(-1ul,-1ul);
  }

  bool verbose{false};
  void solve_sudoku_internal(Sudoku s){
    auto const&[r,c]{s.get_zero_point()};
    for (char ch{'1'}; ch <= '9'; ++ch){
      if (solved_patterns.empty() and s.n_placible_at({r,c}, ch)){
	s.body[r][c] = ch;
	--s.blank;
	if (verbose){
	  std::cout << "Try filling with '"<<ch<<"' at ["<<r<<", "<<c<<"], remaining blank is "<< s.blank<< std::endl;
	}
	//s.show();
	if (s.blank == 0){
	  solved_patterns.push_back(s.body);
	  solved = true;
	}
	solve_sudoku_internal(s);
	s.body[r][c] = '0';
	++s.blank;
      }
    }//end of chars-for the func gets here means current [r,c] is unable to be filled with some chars
    //so must get back to the previous assumption(=char assignment)
    if (solved_patterns.empty() and verbose){
      std::cout <<  "Any number at [" << r<< ", "<<c<<"] suffices sudoku condition"<< std::endl;
      std::cout << "So Get Back to the previous point!!\n"<< std::endl;
    }
  }
  void solve(bool solve_verbosely = false){
    if (solve_verbosely){verbose=true;}
    solved_patterns.clear();
    solved= false;
    solve_sudoku_internal(*this);

    //call of internal_solving
    if (solved){
      std::cout << "Sudoku is solved!!" << std::endl;
    }else{
      std::cout << "Given Sudoku doesn't have solution!!" << std::endl;
    }
    //call of internal_solving
    
    verbose =false;
  }
};

