
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include"my_lib.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ START OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define CUR_BRUNCH_ASSERT( cur_brunch )                                                                                         \
                                                if(is_brunch_ok == 0)                                                           \
                                                {                                                                               \
                                                    printf(">>> FATAL_ERROR_IN_MEMORY (assert of brunch) <<<\n\n\n");           \
                                                    abort();                                                                    \
                                                }



#define OPERATION( num_of_op , str_of_op )                                                                                      \
                                                if(strcmp(cur_buff, str_of_op) == 0)                                            \
                                                {                                                                               \
                                                    cur_point->value = num_of_op;                                               \
                                                    cur_point->type_of_data = T_operator;                                       \
                                                }


#define DIFF_MOVE( cur_type , left_s, right_s)                                                                                                          \
                                                if(cur_new_tree_point->type_of_data == cur_type && left_s != val_left && right_s != val_right)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END OF DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const int Max_num_size = 20;

const int T_operator = 3;
const int T_value = 2;
const int T_symbol = 1;
const int T_no_T = 10;
const int Nil = 0;



struct diff_tree_brunch *part_creator(struct diff_tree_brunch *parent, double val_of_cur_brunch, int d_type);
struct diff_tree_brunch *pre_reader(void);
struct diff_tree_brunch *rec_reader(struct diff_tree_brunch *cur_point, char *buff);

struct diff_tree_brunch *create_node(int type, double val, struct diff_tree_brunch *fun_left, struct diff_tree_brunch *fun_right);
struct diff_tree_brunch *brunch_copy(struct diff_tree_brunch *what);
struct diff_tree_brunch *differ(struct diff_tree_brunch *what);

int rec_brunch_viewer(struct diff_tree_brunch *cur_brunch);
int is_brunch_ok(struct diff_tree_brunch *cur_point);

long int get_file_size(FILE *text);

void tree_dump(struct diff_tree_brunch *start_point);
void node_dump_gen(struct diff_tree_brunch *cur_point, FILE *dump);
void arrows_dump_gen(struct diff_tree_brunch *cur_point, FILE *dump);

void empty_fnction(struct diff_tree_brunch *not_matter);

void usr_interface(void);
void freesher(struct diff_tree_brunch *start_point);

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
struct diff_tree_brunch
{
    struct diff_tree_brunch *parent_pointer;
    double value;
    int type_of_data;
    struct diff_tree_brunch *left_point;
    struct diff_tree_brunch *right_point;
};

//!---------------------------------------------------------------------------------------------------
//!
//! This program find diff                          v - 0.2
//!
//! UPD (v 0.0.1) - I print main, it was hard... (Asserts also, because it's in my heart)
//! UPD (v 0.2) - Reader wrote, but not tested c:
//!
//! Author: Vladimir Gribanov
//!
//!---------------------------------------------------------------------------------------------------
int main()
{
    usr_interface();

    return 0;
}

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
void usr_interface (void)
{
    struct diff_tree_brunch *start_pre_diff_brunch = pre_reader();

    tree_dump(start_pre_diff_brunch);

    struct diff_tree_brunch *diff_tree_start_point = differ(start_pre_diff_brunch);

    tree_dump(diff_tree_start_point);

    freesher(start_pre_diff_brunch);
    freesher(diff_tree_start_point);
}

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
struct diff_tree_brunch *part_creator(struct diff_tree_brunch *parent, double val_of_cur_brunch, int d_type)
{
    struct diff_tree_brunch *cur_brunch = (struct diff_tree_brunch*) calloc(1, sizeof(struct diff_tree_brunch));

    if(d_type == T_operator)
        cur_brunch->type_of_data = T_operator;
    else if(d_type == T_value)
        cur_brunch->type_of_data = T_value;
    else if(d_type == T_symbol)
        cur_brunch->type_of_data = T_symbol;
    else if(d_type == T_no_T)
        cur_brunch->type_of_data = T_no_T;
    else
        return NULL;

    cur_brunch->parent_pointer = parent;
    cur_brunch->left_point = NULL;
    cur_brunch->right_point = NULL;
    cur_brunch->value = val_of_cur_brunch;

    CUR_BRUNCH_ASSERT(cur_brunch)

    return cur_brunch;
}

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
struct diff_tree_brunch *pre_reader(void)
{
    FILE *diff_info = fopen("diff_info.txt", "rb");

    struct diff_tree_brunch *start_elem = part_creator(NULL, 0, T_no_T);

    long int size_of_file = get_file_size(diff_info);

    char *buff = new char [size_of_file];

    fseek(diff_info, 0, SEEK_SET);
    fread(buff, sizeof(char), size_of_file, diff_info);

    start_elem = rec_reader(start_elem, buff);

    fclose(diff_info);

    return start_elem;
}


//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
struct diff_tree_brunch *rec_reader(struct diff_tree_brunch *cur_point, char *buff)
{
    static long int pos_in_buff = 0;

    int inf_pos = 0;

    char cur_buff[Max_num_size] = {};

    struct diff_tree_brunch *n_element_l = (struct diff_tree_brunch*) calloc(1, sizeof(struct diff_tree_brunch));
    n_element_l->type_of_data = Nil;
    struct diff_tree_brunch *n_element_r = (struct diff_tree_brunch*) calloc(1, sizeof(struct diff_tree_brunch));
    n_element_r->type_of_data = Nil;

    while(buff[pos_in_buff] == ' ' || buff[pos_in_buff] == '\n' || buff[pos_in_buff] == '\t' || buff[pos_in_buff] == '\r')
        pos_in_buff++;

    if(cur_point->type_of_data == T_no_T && cur_point->parent_pointer == NULL)
    {

        while(buff[pos_in_buff] != '\'')
            pos_in_buff++;
    }

    if(buff[pos_in_buff] == '\'')
    {
        pos_in_buff++;

        buf_fill(cur_buff, Max_num_size, '\0');

        while(buff[pos_in_buff] != '\'')
            cur_buff[inf_pos++] = buff[pos_in_buff++];

        pos_in_buff++;

        #define NEED_OPERATION
        #include"Diff_data.h"

        if(strcmp(cur_buff, "x") == 0 && cur_point->type_of_data != T_operator)///includit' !!!
        {
            cur_point->value = 'x';
            cur_point->type_of_data = T_symbol;
        }
        else if(cur_point->type_of_data != T_operator)
        {
            cur_point->value = atof(cur_buff);
            cur_point->type_of_data = T_value;
        }
    }

    while(buff[pos_in_buff] == ' ' || buff[pos_in_buff] == '\n' || buff[pos_in_buff] == '\t' || buff[pos_in_buff] == '\r')
        pos_in_buff++;

    if(buff[pos_in_buff] == '(')
    {
        pos_in_buff++;

        if(cur_point->type_of_data == T_operator)
        {
            cur_point->left_point = rec_reader(n_element_l, buff);
            cur_point->left_point->parent_pointer = cur_point;

            while(buff[pos_in_buff] != '(')
                pos_in_buff++;

            pos_in_buff++;

            cur_point->right_point = rec_reader(n_element_r, buff);
            cur_point->right_point->parent_pointer = cur_point;
        }
        else
        {
            printf(" Err_print \\ val = %d \\ type = %d \\ \n", cur_point->value, cur_point->type_of_data);
            printf(" It's strange... \n");
        }

    }
    else if(buff[pos_in_buff] == ')')
    {
        pos_in_buff++;
        return cur_point;
    }
    else
    {
        pos_in_buff++;
        printf("...Menya tyt bit ne dolzno...\n...Hmmmmm...\n");
        return cur_point;
    }

    return cur_point;
}


//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
int is_brunch_ok(struct diff_tree_brunch *cur_point)
{
    if(cur_point != NULL &&
       cur_point->left_point != cur_point &&
       cur_point->right_point != cur_point &&
       cur_point->parent_pointer != cur_point
       )
       {
        return 0;
       }
    else
        return -1;
}

//!----------------------------------------------------------------
//!
//!
//!
//! @param[in] FILE *text -
//!
//! @param[out] size_of_text -
//!
//!----------------------------------------------------------------
long int get_file_size(FILE *text)
{
    long int size_of_text = 0;

    const int zero = 0;

    fseek(text, zero, SEEK_END);
    size_of_text = ftell(text);

    return size_of_text;
}


//!-------------------------------------------------------------------------------
//!
//! This function create dump in dot language
//!
//! @param[in] struct diff_tree_brunch *start_point - pointer on start structure
//!
//!-------------------------------------------------------------------------------
void tree_dump(struct diff_tree_brunch *start_point)
{
    FILE *dump = fopen("dump.dot","w");

    fprintf(dump, "digraph list {\n\tnode [shape = record];\n");

    node_dump_gen(start_point, dump);
    arrows_dump_gen(start_point, dump);

    fprintf(dump, "}");

    fclose(dump);

    system("C:\\Users\\bqbq4\\OneDrive\\Документы\\Проги\\release\\bin\\dotty.exe dump.dot");
}


//!-------------------------------------------------------------------------------
//!
//! This function do recursive print nodes in dump file in dot language
//!
//! @param[in] struct diff_tree_brunch *cur_point - pointer on current structure
//! @param[in] FILE *dump - dump file
//!
//!-------------------------------------------------------------------------------
void node_dump_gen(struct diff_tree_brunch *cur_point, FILE *dump)
{
    if(cur_point->left_point != NULL)
        node_dump_gen(cur_point->left_point, dump);

    if(cur_point->type_of_data == T_operator || cur_point->type_of_data == T_symbol)
        fprintf(dump, "\tnode%p [label = \"cur_poz = %p|{<f0> Parent = %p | <f1> %c |{<f2> left = %p | <f3> right = %p }}\"];\n", cur_point, cur_point, cur_point->parent_pointer, (int)cur_point->value, cur_point->left_point, cur_point->right_point);
    else
        fprintf(dump, "\tnode%p [label = \"cur_poz = %p|{<f0> Parent = %p | <f1> %f |{<f2> left = %p | <f3> right = %p }}\"];\n", cur_point, cur_point, cur_point->parent_pointer, cur_point->value, cur_point->left_point, cur_point->right_point);

    if(cur_point->right_point != NULL)
        node_dump_gen(cur_point->right_point, dump);
}

//!-------------------------------------------------------------------------------
//!
//! This function do recursive print arrows in dump file in dot language
//!
//! @param[in] struct diff_tree_brunch *cur_point - pointer on current structure
//! @param[in] FILE *dump - dump file
//!
//!-------------------------------------------------------------------------------
void arrows_dump_gen(struct diff_tree_brunch *cur_point, FILE *dump)
{
    if(cur_point->left_point != NULL)
        arrows_dump_gen(cur_point->left_point, dump);

    if(cur_point->left_point != NULL)
        fprintf(dump, "\t\"node%p\":f2 -> \"node%p\":f0;\n", cur_point, cur_point->left_point);

    if(cur_point->right_point != NULL)
        fprintf(dump, "\t\"node%p\":f3 -> \"node%p\":f0;\n", cur_point, cur_point->right_point);

    if(cur_point->right_point != NULL)
        arrows_dump_gen(cur_point->right_point, dump);
}

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
struct diff_tree_brunch *brunch_copy(struct diff_tree_brunch *what)
{
    struct diff_tree_brunch *where = (struct diff_tree_brunch*) calloc(1, sizeof(struct diff_tree_brunch));
    where->value = what->value;
    where->type_of_data = what->type_of_data;

    if(what->left_point!= NULL)
    {
        where->left_point = brunch_copy(what->left_point);
        where->left_point->parent_pointer = where->left_point;
    }
    else
        where->left_point = NULL;

    if(what->right_point != NULL)
    {
        where->right_point = brunch_copy(what->right_point);
        where->right_point->parent_pointer = where->right_point;
    }
    else
        where->right_point = NULL;

    return where;
}

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
int rec_brunch_viewer(struct diff_tree_brunch *cur_brunch)
{
    int i_found = 0;

    if(cur_brunch->left_point != NULL && i_found == 0)
        i_found = rec_brunch_viewer(cur_brunch->left_point);


    if(cur_brunch->type_of_data == T_symbol)
        i_found = 1;


    if(cur_brunch->right_point != NULL && i_found == 0)
        i_found = rec_brunch_viewer(cur_brunch->right_point);

    return i_found;
}

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
struct diff_tree_brunch *create_node(int type, double val, struct diff_tree_brunch* fun_left, struct diff_tree_brunch* fun_right)
{
    struct diff_tree_brunch *new_node = (struct diff_tree_brunch*) calloc(1, sizeof(struct diff_tree_brunch));

    if(type == T_operator)
    {
        new_node->left_point = fun_left;
        new_node->right_point = fun_right;
        new_node->left_point->parent_pointer = new_node->left_point;
        new_node->right_point->parent_pointer = new_node->right_point;

        new_node->type_of_data = T_operator;
        new_node->value = val;
    }
    else if(type == T_value)
    {
        new_node->left_point = NULL;
        new_node->right_point = NULL;
        new_node->type_of_data = T_value;
        new_node->value = val;
    }
    else if(type == T_symbol)
    {
        new_node->left_point = NULL;
        new_node->right_point = NULL;
        new_node->type_of_data = T_symbol;
        new_node->value = val;
    }
}

//!---------------------------------------------------------------------------------------------------
//!
//!
//!
//!---------------------------------------------------------------------------------------------------
struct diff_tree_brunch *differ(struct diff_tree_brunch *what)
{
    struct diff_tree_brunch *where = (struct diff_tree_brunch*) calloc(1, sizeof(struct diff_tree_brunch));

    #define NEED_DIFF_BRUNCH
    #include "Diff_data.h"
}

//!---------------------------------------------------------------------------------------------------
//!
//! It's like me! Do nothing :D
//!
//!---------------------------------------------------------------------------------------------------
void empty_fnction(struct diff_tree_brunch *not_matter)
{
    return;
}

//!------------------------------------------------------------------------------
//!
//! Why
//!
//!------------------------------------------------------------------------------
void freesher(struct diff_tree_brunch *cur_point)
{
    if(cur_point->left_point != NULL)
        freesher(cur_point->left_point);

    if(cur_point->right_point != NULL)
        freesher(cur_point->right_point);

    free(cur_point);
}



