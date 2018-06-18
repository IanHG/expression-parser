#include <iostream>

#include "src/expr.hpp"
#include "src/parser.hpp"

using namespace expr;
using namespace parser;

int main()
{
   //using float_type = double;
   //using expression_ptr = abstract_expression<float_type>::expression_ptr;

   //float_type variable = 1.4;
   //
   //expression_ptr un_minus { new unary_expression<float_type>(  operator_type::unary_minus
   //                                                          ,  expression_ptr{new variable_expression<float_type>{variable}}
   //                                                          )
   //                        };


   //binary_expression<float_type> bin_add  (  operator_type::addition
   //                                       ,  abstract_expression<float_type>::expression_ptr{new litteral_expression<float_type>{3.0}}
   //                                       //,  abstract_expression<float_type>::expression_ptr{new litteral_expression<float_type>{2.2}}
   //                                       ,  std::move(un_minus)
   //                                       );

   //auto value = bin_add.evaluate();

   //std::cout << value << std::endl;
   //
   
   std::string str = "abc (-10.22123 + 123.23 --lol 3423)";

   ::parser::parser p;
   p.compile(str);

   //lexer::lexer lex(const_cast<char*>(str.c_str()), const_cast<char*>(str.c_str()) + str.size());

   //lex.scan_token();
   //
   //lexer::token t = lex.next_token();
   //for(; !lexer::is_token_end(t); t = lex.next_token())
   //{
   //   std::cout << t.value() << std::endl;
   //}

   return 0;
}
