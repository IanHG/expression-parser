#include "lexer_test.hpp"

#include "../src/parser.hpp"

namespace lexer_test
{
   /**
    * Check is_white_space()
    **/
   void lexer_check_is_white_space::do_test()
   {
      UNIT_ASSERT(parser::detail::is_white_space(' ') , "parser::detail::is_white_space() failed.");
      UNIT_ASSERT(parser::detail::is_white_space('\n'), "parser::detail::is_white_space() failed.");
      UNIT_ASSERT(parser::detail::is_white_space('\t'), "parser::detail::is_white_space() failed.");
   }

   /**
    * Check is_letter()
    **/
   void lexer_check_is_letter::do_test()
   {
      UNIT_ASSERT( parser::detail::is_letter('a'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT( parser::detail::is_letter('b'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT( parser::detail::is_letter('z'), "parser::detail::is_letter() failed.");
   
      std::cout << parser::detail::is_letter('A') << std::endl;

      UNIT_ASSERT( parser::detail::is_letter('A'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT( parser::detail::is_letter('B'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT( parser::detail::is_letter('Z'), "parser::detail::is_letter() failed.");
      
      UNIT_ASSERT(!parser::detail::is_letter('1'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('2'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('3'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('4'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('5'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('6'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('7'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('8'), "parser::detail::is_letter() failed.");
      UNIT_ASSERT(!parser::detail::is_letter('9'), "parser::detail::is_letter() failed.");
   }

   /**
    * Check is_operator()
    **/
   void lexer_check_is_operator::do_test()
   {
      UNIT_ASSERT(parser::detail::is_operator('+'), "parser::detail::is_operator() failed");
      UNIT_ASSERT(parser::detail::is_operator('-'), "parser::detail::is_operator() failed");
   }
   
   /**
    * Check is_digit()
    **/
   void lexer_check_is_digit::do_test()
   {
      UNIT_ASSERT( parser::detail::is_digit('1'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('2'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('3'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('4'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('5'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('6'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('7'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('8'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT( parser::detail::is_digit('9'), "parser::detail::is_digit() failed.");
      
      UNIT_ASSERT(!parser::detail::is_digit('a'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT(!parser::detail::is_digit('b'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT(!parser::detail::is_digit('z'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT(!parser::detail::is_digit('A'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT(!parser::detail::is_digit('B'), "parser::detail::is_digit() failed.");
      UNIT_ASSERT(!parser::detail::is_digit('Z'), "parser::detail::is_digit() failed.");
   }

   /**
    * Check is_left_bracket()
    **/
   void lexer_check_is_left_bracket::do_test()
   {
      UNIT_ASSERT(parser::detail::is_left_bracket('('), "parser::detail::is_left_bracket() failed.");
      UNIT_ASSERT(parser::detail::is_left_bracket('{'), "parser::detail::is_left_bracket() failed.");
      UNIT_ASSERT(parser::detail::is_left_bracket('['), "parser::detail::is_left_bracket() failed.");
      
      UNIT_ASSERT(!parser::detail::is_left_bracket(')'), "parser::detail::is_left_bracket() failed.");
      UNIT_ASSERT(!parser::detail::is_left_bracket('}'), "parser::detail::is_left_bracket() failed.");
      UNIT_ASSERT(!parser::detail::is_left_bracket(']'), "parser::detail::is_left_bracket() failed.");
   }
   
   /**
    * Check is_right_bracket()
    **/
   void lexer_check_is_right_bracket::do_test()
   {
      UNIT_ASSERT( parser::detail::is_right_bracket(')'), "parser::detail::is_right_bracket() failed.");
      UNIT_ASSERT( parser::detail::is_right_bracket('}'), "parser::detail::is_right_bracket() failed.");
      UNIT_ASSERT( parser::detail::is_right_bracket(']'), "parser::detail::is_right_bracket() failed.");
      
      UNIT_ASSERT(!parser::detail::is_right_bracket('('), "parser::detail::is_right_bracket() failed.");
      UNIT_ASSERT(!parser::detail::is_right_bracket('{'), "parser::detail::is_right_bracket() failed.");
      UNIT_ASSERT(!parser::detail::is_right_bracket('['), "parser::detail::is_right_bracket() failed.");
   }
   
   /**
    * Check is_bracket()
    **/
   void lexer_check_is_bracket::do_test()
   {
      UNIT_ASSERT(parser::detail::is_bracket('('), "parser::detail::is_bracket() failed.");
      UNIT_ASSERT(parser::detail::is_bracket('{'), "parser::detail::is_bracket() failed.");
      UNIT_ASSERT(parser::detail::is_bracket('['), "parser::detail::is_bracket() failed.");
      UNIT_ASSERT(parser::detail::is_bracket(')'), "parser::detail::is_bracket() failed.");
      UNIT_ASSERT(parser::detail::is_bracket('}'), "parser::detail::is_bracket() failed.");
      UNIT_ASSERT(parser::detail::is_bracket(']'), "parser::detail::is_bracket() failed.");
   }
   
   /**
    * Check is_escape()
    **/
   void lexer_check_is_escape::do_test()
   {
      UNIT_ASSERT(parser::detail::is_escape('\\'), "parser::detail::is_escape() failed.");
   }

   /**
    * Check token constructor
    **/
   void lexer_token_construction::do_test()
   {
      parser::lexer::token t{parser::lexer::token::token_type::symbol, "abc"};

      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::symbol, "token::type not set correctly." );
      UNIT_ASSERT_EQUAL(t.value(), std::string{"abc"}                      , "token::value not set correctly.");
   }

   /**
    * Check lexer token generation.
    **/
   void lexer_token_generation::do_test()
   {
      std::string str{"1 + (abcd_e * 3.0) { }"};
      parser::lexer::lexer l(const_cast<char*>(str.c_str()), const_cast<char*>(str.c_str()) + str.size());
      l.scan_token();
      
      auto t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::begin, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{""}                        , "token value not correct.");

      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::number, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"1"}                        , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::add, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"+"}                     , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::lbracket, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"("}                          , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::symbol, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"abcd_e"}                   , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::mult, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"*"}                      , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::number, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"3.0"}                      , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::rbracket, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{")"}                          , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::lbracket, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"{"}                          , "token value not correct.");
      
      t = l.next_token();
      UNIT_ASSERT_EQUAL(t.type() , parser::lexer::token::token_type::rbracket, "token type not correct.");
      UNIT_ASSERT_EQUAL(t.value(), std::string{"}"}                          , "token value not correct.");
   }

} /* namespace test */
