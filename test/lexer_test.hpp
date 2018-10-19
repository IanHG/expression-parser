#include <cutee.hpp>

namespace lexer_test
{

struct lexer_check_is_white_space
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_check_is_letter
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_check_is_operator
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_check_is_digit
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_check_is_left_bracket
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_check_is_right_bracket
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_check_is_bracket
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_check_is_escape
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_token_construction
   :  public cutee::unit_test
{
   void do_test();
};

struct lexer_token_generation
   :  public cutee::unit_test
{
   void do_test();
};

} /* namespace test */
