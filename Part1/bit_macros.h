/*
 * bit_macros.h
 *
 * Created: 19.09.2019 10:50:40
 *  Author: juliessk
 */ 

#ifndef BIT_MACROS_H_
#define BIT_MACROS_H_

#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )

#define toggle_bit(reg, bit) (reg ^= (1 << bit))

#endif /* BIT_MACROS_H_ */

/*
	set_bit(PORTB, PB4); PB4 = 4

	PORTB = 0b 1001 1001

	PB4 = 1 / 0 eller 0001 0000 << 2   

	set_bit(0b 1001 1001, 1)
	
	setbit(reg, bit){
		reg |= 
	

	PORTB = PORTB | 0000 0001 << 4
	PORTB = PORTB | 0000 0010
	PORTB = 1001 1011  ???
	
	PORTB = PORTB | 0001 0000 << 16
	PORTB = PORTB | 0000 0000
	PORTB = 1001 1001  ???


 */
