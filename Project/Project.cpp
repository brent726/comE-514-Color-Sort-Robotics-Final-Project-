// Project.cpp : Defines the entry point for the console application.
//COME514 Project : Color Segragation Using Robotic Arm 


#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>
#include "cxcore.h"
#include "robotMove.h"
#include "imageProcessing.h"
#include <windows.h>
#include <string>


using namespace std;




int _tmain(int argc, _TCHAR* argv[])
{
   IplImage * inputImage;
   IplImage * imageHSV;

   int colorHolder[5];
   int start=0;

    
  
	printf("Enter 1 to start:  ");
     scanf("%d",&start);
	if(start==1)
	{
			printf("********************LET'S START************************");
			startformation();
			 captureImage();
			 //inputImage =cvLoadImage("C:\\Users\\t6_514lg1.DML\\Desktop\\colorwithblank.jpg",1);
		     inputImage =cvLoadImage("C:\\Users\\t6_514lg1.DML\\Desktop\\capturedImage.jpg",1);
			imageHSV=convertImageRGBtoHSV(inputImage);
	
			 //read Image from file
			//inputImage =cvLoadImage("C:\\Users\\t6_514lg1.DML\\Desktop\\imageHSV.jpg",1);
			//Create a window
			cvNamedWindow("ImageHSV", 1);
			 cvShowImage("ImageHSV", imageHSV);
			  evaluateColor(imageHSV,colorHolder);
			  //set the callback function for any mouse event
			//cvSetMouseCallback("My Window",mouseEvent,inputImage);
	
			 
			
			 //colorHolder will be passed to the next class for movement
			 //printf("%d, %d, %d, %d, %d\n",colorHolder[0],colorHolder[1],colorHolder[2],colorHolder[3],colorHolder[4]);

			

			 int i;
			 for(i=0;i<5;i++)
			 {
				 printf("colorHolder[%d]: %d\n",i,colorHolder[i]);
	
				
					if(i==0)
					{

						if(colorHolder[0]!=0)
						{
						  pickC1();
						  
						  reset();
						  
							//Move first column
							if(colorHolder[0]==1)
							{
						
								throwB1();
								
								reset();
								printf("Column 1 move Red\n");
							}
							else if(colorHolder[0]==2)
							{
								//move green
								throwB2();
								
								reset();
								printf("Column 1 move Green\n");
							}
							else if(colorHolder[0]==3)
							{
								//move blue
								throwB3();
								
								reset();
								printf("Column 1 move Blue\n");
							}

						 }
					 }
					 if(i==1)
					 {
						  
						 
						if(colorHolder[1]!=0)
						{
							 pickC2();
						  
						   reset();
							if(colorHolder[1]==1)
							{
								//move red
								throwB1();
								
								reset();
								printf("Column 2 move Red\n");
							}
							else if(colorHolder[1]==2)
							{
									throwB2();
								
								reset();
									//move green
									printf("Column 2 move Green\n");
							}
							else if(colorHolder[1]==3)
							{
								throwB3();
								
								reset();
									//move blue
								printf("Column 2 move Yellow\n");
							}
						}
					}
					if(i==2)
					{
						
						 
						if(colorHolder[2]!=0)
						{
							 pickC3();
						 
						      reset();
								if(colorHolder[2]==1)
								{
									//move red
									throwB1();
									
									reset();
									printf("Column 3 move Red\n");
								}
								else if(colorHolder[2]==2)
								{
										//move green
									throwB2();
									
									reset();
									printf("Column 3 move Green\n");
								}
								else if(colorHolder[2]==3)
								{
										//move blue
									throwB3();
									
									reset();
									printf("Column 3 move Blue\n");
								}
					
							}
					}
					if(i==3)
					{
						
						if(colorHolder[3]!=0)
						{
								 pickC4();
						 
						         reset();
								if(colorHolder[3]==1)
								{
									throwB1();
									
									reset();
									//move red
									printf("Column 4 move Red\n");
								}
								else if(colorHolder[3]==2)
								{
										//move green
									throwB2();
									
									reset();
									printf("Column 4 move Green\n");
								}
								else if(colorHolder[3]==3)
								{
										//move blue
									throwB3();
									
									reset();
									printf("Column 4 move Blue\n");
								}
						}
					}
					if(i==4)
					{
						
						 
						if(colorHolder[4]!=0)
						{
							 pickC5();
						 
						    reset();

								if(colorHolder[4]==1)
								{
									//move red
									throwB1();
									
									reset();
									printf("Column 5 move Red\n");
								}
								else if(colorHolder[4]==2)
								{
										//move green
									throwB2();
									
									reset();
									printf("Column 5 move Green\n");
								}
								else if(colorHolder[4]==3)
								{
										//move blue
									throwB3();
									
									reset();
									printf("Column 5 move Blue\n");
								}
						   }
					}
		
	
			 }
			  // Wait until user press some key
			cvWaitKey(0);
	
	}
	

}
