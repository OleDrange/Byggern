/*
 * bit_macros.h
 *
 * Created: 19.09.2019 10:50:40
 *  Author: juliessk
 */ 

#ifndef BIT_MACROS
#define BIT_MACROS

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )

#define toggle_bit(reg, bit) (reg ^= (1 << bit))

#endif 
