#ifndef EXPR_HPP_INCLUDED
#define EXPR_HPP_INCLUDED

#include <memory>

namespace expr
{

template<class T>
class abstract_expression
{
   public:
      using expression_ptr = std::unique_ptr<abstract_expression<T> >;
      using branch_type    = expression_ptr;

      explicit abstract_expression()
      {
      }

      virtual ~abstract_expression()
      {
      }

      virtual T evaluate() const = 0;
};

namespace branches
{

template<int N, class T>
void construct
   (  typename abstract_expression<T>::branch_type* branch
   ,  typename abstract_expression<T>::expression_ptr& branch1
   )
{
   branch[0] = std::move(branch1);
}

template<int N, class T>
void construct
   (  typename abstract_expression<T>::branch_type* branch
   ,  typename abstract_expression<T>::expression_ptr& branch1
   ,  typename abstract_expression<T>::expression_ptr& branch2
   )
{
   branch[0] = std::move(branch1);
   branch[1] = std::move(branch2);
}

} /* namespace branches */

enum class operator_type : int { addition, subtraction, unary_minus, unary_plus };

namespace numeric
{

template<class T>
T unary_plus_impl(T value1)
{
   return value1;
}

template<class T>
T unary_minus_impl(T value1)
{
   return - value1;
}

template<class T>
T addition_impl(T value1, T value2)
{
   return value1 + value2;
}

template<class T>
T subtraction_impl(T value1, T value2)
{
   return value1 - value2;
}

template<class T>
T process(  operator_type op
         ,  const typename abstract_expression<T>::expression_ptr& branch1
         )
{
   switch(op)
   {
      case operator_type::unary_plus:
         return unary_plus_impl(branch1->evaluate());
      case operator_type::unary_minus:
         return unary_minus_impl(branch1->evaluate());
   }

   return 0.0;
}

template<class T>
T process(  operator_type op
         ,  const typename abstract_expression<T>::expression_ptr& branch1
         ,  const typename abstract_expression<T>::expression_ptr& branch2
         )
{
   switch(op)
   {
      case operator_type::addition:
         return addition_impl(branch1->evaluate(), branch2->evaluate());
      case operator_type::subtraction:
         return subtraction_impl(branch1->evaluate(), branch2->evaluate());
   }

   return 0.0;
}

} /* namespace numeric */

template<class T>
class litteral_expression
   :  public abstract_expression<T>
{
   public:
      litteral_expression
         (  T value
         )
         :  value_(value)
      {
      }

      virtual ~litteral_expression()
      {
      }

      virtual T evaluate() const
      {
         return value_;
      }

   protected:
      T value_;
};

template<class T>
class variable_expression
   :  public abstract_expression<T>
{
   public:
      variable_expression(T& t)
         :  value_(&t)
      {
      }

      virtual ~variable_expression()
      {
      }

      T evaluate() const
      {
         return *value_;
      }

   protected:
      T* value_;
};

template<class T>
class unary_expression
   :  public abstract_expression<T>
{
   using expression_ptr = typename abstract_expression<T>::expression_ptr;
   using branch_type    = typename abstract_expression<T>::branch_type;

   public:
      unary_expression
         (  const operator_type& op
         ,  expression_ptr       branch1
         )
         :  op_(op)
         {
            branches::construct<1, T>(branch_, branch1);
         }

      virtual ~unary_expression()
      {
      }

      virtual T evaluate() const
      {
         return numeric::process<T>(op_, branch_[0]);
      }

   protected:
      operator_type op_;
      branch_type   branch_[1];
};

template<class T>
class binary_expression
   :  public abstract_expression<T>
{
   using expression_ptr = typename abstract_expression<T>::expression_ptr;
   using branch_type    = typename abstract_expression<T>::branch_type;

   public:
      binary_expression 
         (  const operator_type& op
         ,  expression_ptr       branch1
         ,  expression_ptr       branch2
         )
         :  op_(op)
      {
         branches::construct<2, T>(branch_, branch1, branch2);
      }

      virtual ~binary_expression()
      {
      }

      virtual T evaluate() const
      {
         return numeric::process<T>(op_, branch_[0], branch_[1]);
      }
   
   protected:
      operator_type op_;
      branch_type   branch_[2];
};

template<class T>
class nary_expression
   :  public abstract_expression<T>
{
};

} /* namespace expr */

#endif /* EXPR_HPP_INCLUDED */
