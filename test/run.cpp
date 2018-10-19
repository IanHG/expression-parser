#include "lexer_test.hpp"

int main()
{
   /* *****************************************************************
    * Setup test suite
    * ***************************************************************** */
   cutee::test_suite suite("Check parser framework.");

   /* *****************************************************************
    * parser::detail
    * ***************************************************************** */
   suite.add_test<lexer_test::lexer_check_is_white_space  >("Check parser::detail::is_white_space()."  );
   suite.add_test<lexer_test::lexer_check_is_letter       >("Check parser::detail::is_letter()."       );
   suite.add_test<lexer_test::lexer_check_is_operator     >("Check parser::detail::is_operator()."     );
   suite.add_test<lexer_test::lexer_check_is_digit        >("Check parser::detail::is_digit()."        );
   suite.add_test<lexer_test::lexer_check_is_left_bracket >("Check parser::detail::is_left_bracket()." );
   suite.add_test<lexer_test::lexer_check_is_right_bracket>("Check parser::detail::is_right_bracket().");
   suite.add_test<lexer_test::lexer_check_is_bracket      >("Check parser::detail::is_bracket()."      );
   suite.add_test<lexer_test::lexer_check_is_escape       >("Check parser::detail::is_escape()."       );
   
   /* *****************************************************************
    * token_test
    * ***************************************************************** */
   suite.add_test<lexer_test::lexer_token_construction>("Check parser::lexer::token construction.");
   
   /* *****************************************************************
    * lexer_test
    * ***************************************************************** */
   suite.add_test<lexer_test::lexer_token_generation>("Check parser::lexer token generation.");

   /* *****************************************************************
    * Run tests
    * ***************************************************************** */
   suite.do_tests();

   return 0;
}
