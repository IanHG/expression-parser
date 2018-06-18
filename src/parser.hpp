#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <list>
#include <map>

#include <cassert>

#include <iostream>

#include "expr.hpp"

namespace parser
{

namespace detail
{
   using char_type = char;
   using char_ptr  = char_type*;

   inline bool is_white_space(const char_type c)
   {
      return (' ' == c) || ('\t' == c) || ('\n' == c);
   }
   
   inline bool is_letter(const char_type c)
   {
      return   (('a' <= c) && ('z' >= c))
           ||  (('A' <= c) && ('Z' >= c));
   }

   inline bool is_operator(const char_type c)
   {
      return   ('+' == c) || ('-' == c);
   }

   inline bool is_digit(const char_type c)
   {
      return ('0' <= c) && ('9' >= c);
   }

   inline bool is_left_bracket(const char_type c)
   {
      return ('(' == c);
   }

   inline bool is_right_bracket(const char_type c)
   {
      return (')' == c);
   }

   inline bool is_bracket(const char_type c)
   {
      return is_left_bracket(c) || is_right_bracket(c);
   }

   inline bool is_escape(const char_type c)
   {
      return ('\\' == c);
   }
   
   inline char_type get_char(char_ptr cptr)
   {
      return *cptr;
   }

} /* namespace detail */

class build_string
{
   using char_type = detail::char_type;
   using char_ptr  = char_type*;

   public:
      explicit build_string() = default;

      void append(char_type c)
      {
         str_.append(1, c);
      }

      std::string get_string() const
      {
         return std::move(str_);
      }

   private:
      std::string str_;
};

namespace lexer
{
   class token
   {
      public:
         enum class token_type : int
            {  none     , error 
            ,  begin    , end
            ,  number   , symbol
            ,  oper     , assign
            ,  lbracket = '(', rbracket = ')'
            ,  add      = '+', sub      = '-'
            ,  eq       = '='
            };

         token(token_type type, std::string&& value = std::string{""})
            :  type_(type)
            ,  value_(std::move(value))
         {
         }
         
         token_type type() const
         {
            return type_;
         }

         std::string value() const
         {
            return value_;
         }

      private:
         token_type  type_;
         std::string value_;
   };

   inline std::ostream& operator<<(std::ostream& os, const token::token_type& type)
   {
      os << "print out of token_type not implemented.";
      return os;
   }

   inline bool is_token_end(const token& t)
   {
      return (t.type() == token::token_type::end);
   }

   inline token::token_type operator_token_type(const detail::char_type c)
   {
      if('+' == c)
      {
         return token::token_type::add;
      }
      else if('-' == c)
      {
         return token::token_type::sub;
      }
      else
      {
         return token::token_type::error;
      }
   }

   class lexer
   {
      using token_t        = token;
      using token_list_t   = std::list<token>;
      using token_list_ptr = std::list<token>::iterator;
      using char_ptr       = detail::char_type*;

      public:
         lexer(char_ptr s_beg, char_ptr s_end)
            :  s_itr_(s_beg)
            ,  s_end_(s_end)
         {
            token_list_.emplace_back(token{token::token_type::begin});
            token_list_ptr_ = token_list_.begin();
         }

         void scan_token()
         {
            while(s_itr_ != s_end_)
            {
               if(detail::is_digit(*s_itr_))
               {
                  scan_number();
               }
               else if(detail::is_letter(*s_itr_))
               {
                  scan_symbol();
               }
               else if(detail::is_operator(*s_itr_))
               {
                  scan_operator();
               }
               else if(detail::is_left_bracket(*s_itr_))
               {
                  token_list_.emplace_back(token{token::token_type::lbracket, "("});
                  ++s_itr_;
               }
               else if(detail::is_right_bracket(*s_itr_))
               {
                  token_list_.emplace_back(token{token::token_type::rbracket, ")"});
                  ++s_itr_;
               }
               else
               {
                  ++s_itr_;
               }
            }

            token_list_.emplace_back(token{token::token_type::end});
         }

         void scan_operator()
         {
            while(s_itr_ != s_end_)
            {
               if(detail::is_operator(*s_itr_))
               {
                  token_list_.emplace_back(token{operator_token_type(*s_itr_), std::string{ detail::get_char(s_itr_)} });
               }
               else
               {
                  break;
               }

               ++s_itr_;
            }
         }

         void scan_symbol()
         {
            build_string str;

            while(s_itr_ != s_end_)
            {
               if(detail::is_letter(*s_itr_) || detail::is_digit(*s_itr_))
               {
                  str.append(*s_itr_);
               }
               else
               {
                  break;
               }

               ++s_itr_;
            }
            
            token_t t(token::token_type::symbol, str.get_string());
            token_list_.emplace_back(std::move(t));
         }

         void scan_number()
         {
            build_string str;

            bool found_dot_sep = false;

            while(s_itr_ != s_end_)
            {
               if(detail::is_digit(*s_itr_))
               {
                  str.append(*s_itr_);
               }
               else if(!found_dot_sep && ('.' == *s_itr_))
               {
                  found_dot_sep = true;
                  str.append(*s_itr_);
               }
               else
               {
                  break;
               }

               ++s_itr_;
            }

            token_t t(token::token_type::number, str.get_string());
            token_list_.emplace_back(std::move(t));
         }

         token current_token()
         {
            return *(token_list_ptr_);
         }

         token next_token()
         {
            if(!is_token_end(*token_list_ptr_))
            {
               return *(token_list_ptr_++);
            }
            else
            {
               return token{token::token_type::end};
            }
         }

      private:
         token_list_t   token_list_;
         token_list_ptr token_list_ptr_;
         char_ptr       s_itr_;
         char_ptr       s_end_;
   };

} /* namespace lexer */

class symbol_table
{
   private:
      struct isymbol
      {
      };

      template<class T>
      struct iconstant
         : public isymbol
      {
         // struct to hold constant symbol
      };
      
      template<class T>
      struct ifunction
         : public isymbol
      {
         // struct to hold var arg function symbol
      };
         
      template<class T>
      struct ivariable
         :  public isymbol
      {
         // struct to hold variable symbol (double, float, int etc.)
      };

      struct symbol_store
      {
         using function_store_t = std::map<key_t, ifunction<double> >; // NBNB PLACEHOLDER TEMPLATE
         using variable_store_t = std::map<key_t, ivariable<double> >;

         function_store_t function_store_;
         variable_store_t variable_store_;
      };


   public:
      symbol_table(symbol_table* = nullptr)
      {
      }

      template<class T>
      bool add_symbol(const std::string& symbol, const T& csymbol)
      {
         // implement me !
         assert(false);
      }

      const isymbol& lookup_symbol(const std::string symbol)
      {
         assert(false);
      }

   private:
};

class parser
{
   struct stack
   {
   };

   public:
      parser()
      {
      }

      bool compile(const std::string& expr_str)
      {
         lexer::lexer l(const_cast<char*>(expr_str.c_str()), const_cast<char*>(expr_str.c_str()) + expr_str.size());
         l.scan_token();
         
         while(true)
         {
            lexer::token t = l.next_token();
            if(lexer::is_token_end(t))
            {
               break;
            }

            std::cout << t.value() << std::endl;
         }

         return true;
      }
   
   private:
      stack stack_;
};

} /* namespace parser */

#endif /* PARSER_HPP_INCLUDED */
