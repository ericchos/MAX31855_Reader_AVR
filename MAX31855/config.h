/*
 * config.h
 *
 * Created: 7/10/2014 4:04:11 PM
 *  Author: Eric
 * 
 * Header file for Pin definitions and configuration settings
 * 
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

/* === CPU & Baud Rate Settings === */
//#define F_CPU 7372800UL  // Using 7.3728MHz Crystal OSC
#define F_CPU 16000000UL

/* === STEP #1: Specify whether this is debug or release build === */
#define DEBUG_BUILD	1

#endif /* CONFIG_H_ */