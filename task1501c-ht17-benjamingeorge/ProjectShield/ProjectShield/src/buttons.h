/*
 * buttons.h
 *
 * Created: 2017-11-23 16:29:24
 * Author: Benjamin Sejdic & George Albert Florea
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

typedef enum button {btnRIGHT, btnUP, btnDOWN, btnLEFT, btnSELECT, btnNONE} buttonType;
buttonType readLCDbutton(void);

#endif /* BUTTONS_H_ */