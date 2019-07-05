	#include <pic1687x.h>
	#include "lcd.h"
	#include "Keypad.h"
	#include "Menu.h"
	static   int State;
	void HomePage()
	{
	 int key;
		key=0;
		clearram();
		cursorxy(20,1);
		putString("WELCOME");
		cursorxy(15,2);
		putString("SMARTBEE");
		cursorxy(25,5);
		putString("Menu");
	   	
		while(State==1) 
	    {
	        
			key=scanCode();
			cursorxy(5,1);
			switcher(key);
			
			switch(key)
			{
				case 10:
				{
				    State=2;
		            cursorxy(25,4);
		            putString("wow10");			    
					break;	
				}
				default:
				{
	                break;
				}
		  //	checkDelay();	
		    }
	    }	
	}
	
	
	void MenuPage()
	{
		int key;
		key=0;
		clearram();
		cursorxy(15,0);
		putString("MAIN MENU");
		cursorxy(0,1);
		putString("1.Security Settings");
		cursorxy(0,2);
		putString("2.IP setting");
		cursorxy(0,3);
		putString("3.Registration");
		cursorxy(0,4);
		putString("4.Factory Reset");
		cursorxy(50,5);
		putString("Back");
	
		/////////////////////????????????????????????/
		//// have to scan the keypad infintely till a key is pressed within a while loop 
		//////// 
		do
	    {
		key=scanCode();
		
		switch(key)
		{
			case 1:
			{
				State=21;
				break;
				}
			case 2:
			{
				State=22;
				break;
				}
				
			case 3:
			{
				State=23;
				break;
				}
			case 4:
			{
				State=24;
				break;
					}
			case 11://for back
			{
				//State=50;// 50 is my range.no body can interfere
			State =1;//	DisplayName();
				break;
				}
			default:
				break;
			
			}
		checkDelay();
		}while (State==2);
		
		
	}
	void SetSecurity()
	{
		int key;
		key=0;
		clearram();
		cursorxy(15,1);
		putString("SECURITY SETTINGS");
		cursorxy(0,2);
		putString("1.Display Name");
		cursorxy(0,3);
		putString("2.Username");
		cursorxy(0,4);
		putString("3.Password");
		cursorxy(50,6);
		putString("Back");
	
		/////////////////////????????????????????????/
		//// have to scan the keypad infintely till a key is pressed within a while loop 
		//////// while(keypressed){
			do{
		key=scanCode();
	
			switch(key)
			{
				case 1:
				{
					State=11;
					break;
				}
				case 2:
				
				{
					State=12;
					break;				
					}
				case 3:
				{
					State=13;
					break;
					}
					case 11:
					{
						State=2;
						break;
						}
				default:
					break;
			}
			checkDelay();
			}while(State==21);
						
		
	}
	void SetIP()
	{
	int key;
	key=0;
	    clearram();
		cursorxy(15,1);
		putString("IP SETTINGS ");
		cursorxy(0,2);
		putString("1.IP Address");
		cursorxy(0,3);
		putString("2.Network Mask");
		cursorxy(0,4);
		putString("3.Gateway IP");
		cursorxy(50,6);
		putString("Back");
	
		/////////////////////????????????????????????/
		//// have to scan the keypad infintely till a key is pressed within a while loop 
		//////// while(keypressed){
		do{
		    key=scanCode();
	
			switch(key)
			{
				case 1:
				{
					State=14;
					break;
				}
				case 2:
				
				{
					State=15;
					break;				
				}
				case 3:
				{
					State=16;
					break;
				}
				case 11:
				{
					State=2;
					break;
				}
				default:
				break;
			}
			checkDelay();
		}while(State==22);
		
		
		
	}

	
		
		
			//samitha's code....................................samitha's code ....................samitha's code
	void DislplayName(){
	
	
		int key;
		key=0;
		clearram();
		cursorxy(15,1);
		putString("Display Name");
		cursorxy(0,3);
		putString("%s",getDataFromGateway(1));//this string should be get from gateway
		cursorxy(0,6);// also this method should be overloaded so that string address and a pointer reference could be put in
		putString("Change");
		cursorxy(50,6);
		putString("Back");
		cursorxy(0,3);
	
		/////////////////////????????????????????????/
		//// have to scan the keypad infintely till a key is pressed within a while loop 
		//////// while(keypressed){
			do{
		key=scanCode();
	
	
	if (key == 11){// 11 for back command
		State = 11;
		else if (key == 12){
		state = 50;// 50 for change command
		//ruwans method
//		cursorxy(0,3);
//		putString("%s",getDataFromGateway());
		
		}
		
	}
			checkDelay();
			}while(State==21);
						
		
	
	}
	
    unsigned char* getDataFromGateway(unsigned char commandIndex){
		int i = 0;
		unsigned  char[20] displayData;
		unsigned char temp;
		temp=0xff;
		byteOut(commandIndex);// this is also not specified

		for(i;(i<20 && (temp!=0)) ;i++){//check out about read byte, this is not clearly specified
			
		    temp=readByte();
			displayData[i]	= temp;
		}
		return displayData;
	
	
	}
	//rigtbyte readbyte
	void UserName(){
	
	
		int key;
		key=0;
		clearram();
		cursorxy(15,1);
		putString("UserName");
		cursorxy(0,3);
		putString("%s",getDataFromGateway(2));//this string should be get from gateway
		cursorxy(0,6);// also this method should be overloaded so that string address and a pointer reference could be put in
		putString("Change");
		cursorxy(50,6);
		putString("Back");
		cursorxy(0,3);
	
		/////////////////////????????????????????????/
		//// have to scan the keypad infintely till a key is pressed within a while loop 
		//////// while(keypressed){
			do{
		key=scanCode();
	
	
	if (key == 11){// 11 for back command
		State = 1;
		else if (key == 12){
		state = 50;// 50 for change command
		UserName();
		
		}
		
	}
			checkDelay();
			}while(State==21);
						
	}
	void PassWord(){
	
	
		int key;
		key=0;
		clearram();
		cursorxy(15,1);
		putString("Password");
		cursorxy(0,3);
		putString("%s",getDataFromGateway(3));//this string should be get from gateway
		cursorxy(0,6);// also this method should be overloaded so that string address and a pointer reference could be put in
		putString("Change");
		cursorxy(50,6);
		putString("Back");
		cursorxy(0,3);
	
		/////////////////////????????????????????????/
		//// have to scan the keypad infintely till a key is pressed within a while loop 
		//////// while(keypressed){
			do{
		key=scanCode();
	
	
	if (key == 11){// 11 for back command
		State = 1;
		else if (key == 12){
		state = 50;// 50 for change command
		Password();
		
		}
		
	}
			checkDelay();
			}while(State==21);
						
	}
	
	
	
	
	