#ifndef MY_LIB_H_INCLUDED
#define MY_LIB_H_INCLUDED

void buf_fill(char* my_buff, long int size_buff, int fill_counter);

//!-------------------------------------------------------------------------------
//!
//! This function fills buffer
//!
//! @param[in] char* my_buff - buffer which we worked
//! @param[in] long int size_buff - size of buffer
//!
//!-------------------------------------------------------------------------------
void buf_fill(char* my_buff, long int size_buff, int fill_counter)
{
    int i = 0;

    while(i != size_buff)
    {
        my_buff[i] = fill_counter;
        i++;
    }
}

#endif // MY_LIB_H_INCLUDED
