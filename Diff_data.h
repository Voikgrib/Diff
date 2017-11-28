
//!===================================================================================
//!
//! Library for diff program
//!
//!                     !=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-!
//!                     ! MAKE PREPROCESSOR GREAT AGAIN! !
//!                     !-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=!
//!
//! Author: Gribanov Vladimir
//!
//!===================================================================================

//------------------------------------------------------------------------------------------
//! OPERATION( 'function' , "function")
//------------------------------------------------------------------------------------------

#ifdef NEED_OPERATION

OPERATION( '+' , "+")
OPERATION( '-' , "-")
OPERATION( '*' , "*")
OPERATION( '/' , "/")
OPERATION( '^' , "^")

OPERATION( 's' , "sin")
OPERATION( 'c' , "cos")
OPERATION( 't' , "tg")
OPERATION( 'k' , "ctg")

#undef NEED_OPERATION
#endif // NEED_OPERATION


#ifdef NEED_DIFF_BRUNCH

#define IS_NUM                           if(what->type_of_data == T_value)
#define IS_VAR                           if(what->type_of_data == T_symbol)
#define IS_OP                            if(what->type_of_data == T_operator)

#define TYPE( cur )                      if(what->value == cur)

#define PLUS( left , right )             create_node(T_operator, '+', left, right)
#define MUL( left , right )              create_node(T_operator, '*', left, right)
#define DIV( left , right )              create_node(T_operator, '/', left, right)
#define SUB( left , right )              create_node(T_operator, '-', left, right)
#define POV( left , right )              create_node(T_operator, '^', left, right)

#define dL                               differ(what->left_point)
#define dR                               differ(what->right_point)

#define L                                brunch_copy(what->left_point)
#define R                                brunch_copy(what->right_point)
#define NUM_CR( name )                   struct diff_tree_brunch *name

#define NUM( num )                       create_node(T_value, num, NULL, NULL)

IS_NUM        return NUM(0);
IS_VAR        return NUM(1);
IS_OP
{
    TYPE('+') return PLUS(dL, dR);
    TYPE('-') return SUB(dL, dR);
    TYPE('*') return PLUS(MUL (dL, R), MUL(L, dR));
    TYPE('/') return DIV(SUB(MUL(dL, R), MUL(L, dR)), MUL(R , R));
    TYPE('^') { NUM_CR(num_1) = NUM(1); return MUL(R, POV(L, SUB(R, brunch_copy(num_1))));}

}

#undef NEED_DIFF_BRUNCH
#endif // NEED_DIFF_BRUNCH



