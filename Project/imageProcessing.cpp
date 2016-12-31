

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include <iostream>
#include "cxcore.h"
#include "robotMove.h"
#include <windows.h>
#include <string>
void captureImage()
{
	CvCapture* capture = 0;
    IplImage * frame, *frameCopy, * image;

    capture = cvCaptureFromCAM(0); //0=default, -1=any camera, 1..99=your cameram (port Number)
    if(!capture) cout << "No camera detected" << endl;

    cvNamedWindow( "result", 1 );

    if( capture )
    {
        cout << "In capture ..." << endl;
            IplImage* iplImg = cvQueryFrame( capture );
            frame = iplImg;
      

            if( cvWaitKey( 10 ) >= 0 )
                cvReleaseCapture( &capture );

			cvSaveImage("C:\\Users\\t6_514lg1.DML\\Desktop\\capturedImage.jpg",iplImg);
		
		cvDestroyWindow("result");
	}
}
IplImage* convertImageRGBtoHSV(const IplImage *imageRGB)
{
	float fR, fG, fB;
	float fH, fS, fV;
	const float FLOAT_TO_BYTE = 255.0f;
	const float BYTE_TO_FLOAT = 1.0f / FLOAT_TO_BYTE;

	FILE *mfile;

	mfile = fopen("hsv.txt", "w");
	// Create a blank HSV image
	IplImage *imageHSV = cvCreateImage(cvGetSize(imageRGB), 8, 3);
	if (!imageHSV || imageRGB->depth != 8 || imageRGB->nChannels != 3) {
		printf("ERROR in convertImageRGBtoHSV()! Bad input image.\n");
		exit(1);
	}

	int h = imageRGB->height;		// Pixel height.
	int w = imageRGB->width;		// Pixel width.
	int rowSizeRGB = imageRGB->widthStep;	// Size of row in bytes, including extra padding.
	unsigned char *imRGB = (unsigned char *)imageRGB->imageData;	// Pointer to the start of the image pixels.
	int rowSizeHSV = imageHSV->widthStep;	// Size of row in bytes, including extra padding.

	for (int y=0; y<h; y++) {
		for (int x=0; x<w; x++) {
			// Get the RGB pixel components. NOTE that OpenCV stores RGB pixels in B,G,R order.


			int input_address=(imageRGB->width*(y))+(x);
			int bB = (imRGB[3*input_address]);	// Blue component
			int bG = (imRGB[3*input_address + 1]);	// Green component
			int bR = (imRGB[3*input_address + 2]);	// Red component

			// Convert from 8-bit integers to floats.
			fR = bR * BYTE_TO_FLOAT;
			fG = bG * BYTE_TO_FLOAT;
			fB = bB * BYTE_TO_FLOAT;

			// Convert from RGB to HSV, using float ranges 0.0 to 1.0.
			float fDelta;
			float fMin, fMax;
			int iMax, iMin;
			// Get the min and max, but use integer comparisons for slight speedup.
			if (bB < bG) {
				if (bB < bR) {
					fMin = fB;
					iMin=bB;
					if (bR > bG) {
						iMax = bR;
						fMax = fR;
					}
					else {
						iMax = bG;
						fMax = fG;
					}
				}
				else {
					fMin = fR;
					fMax = fG;
					iMax = bG;
					iMin=bR;
				}
			}
			else {
				if (bG < bR) {
					fMin = fG;
					iMin=bG;
					if (bB > bR) {
						fMax = fB;
						iMax = bB;
					
					}
					else {
						fMax = fR;
						iMax = bR;
					}
				}
				else {
					fMin = fR;
					fMax = fB;
					iMax = bB;
					iMin=bR;
				}
			}

			fprintf(mfile, "bR=%d, bG=%d, bB=%d",bR, bG, bB);
			fprintf(mfile, " fMax=%d, fMin=%d",iMax, iMin);
			int delta;

			
			//while(1){}
			//fDelta = fMax - fMin;
			delta=iMax-iMin;

			fV = (float)iMax;				// Value (Brightness).
			if (iMax != 0) {			// Make sure it's not pure black.
				//fS = fDelta / fMax;		// Saturation.
				fS=(float)delta/(float)iMax;
				//float ANGLE_TO_UNIT = 1.0f / (6.0f * fDelta);	// Make the Hues between 0.0 to 1.0 instead of 6.0
				float ANGLE_TO_UNIT = 1.0f / (float)delta;
				if (iMax == bR) {		// between yellow and magenta.
					fH = (float)(bG - bB) * ANGLE_TO_UNIT;
					fprintf(mfile, " red ");
				}
				else if (iMax == bG) {		// between cyan and yellow.
					fH = (2.0f) + (float)( bB - bR ) * ANGLE_TO_UNIT;
				}
				else {				// between magenta and cyan.
					//fH = (2.0f/6.0f) + ( fB - fR ) * ANGLE_TO_UNIT;
					fH = (4.0f) + (float)( bR - bG ) * ANGLE_TO_UNIT;
				}
				// Wrap outlier Hues around the circle.
				/*if (fH < 0.0f)
					fH += 1.0f;
				if (fH >= 1.0f)
					fH -= 1.0f;*/
				fH=fH*60.0f;
				if(fH<0){
					fH=fH+360.0f;
				}
			}
			else {
				// color is pure Black.
				fS = 0;
				fH = 0;	// undefined hue
			}

			

			fprintf(mfile, " fS=%f, fH=%f, fV=%f\n",fS, fH,fV);
			
			if(fS>0.3)
			{

				//Instructions range the fH
				
				if((fH>350||fH<20)&&fV>80)
				{
					//blue channel
					imageHSV->imageData[3*input_address]=0;
					//green channel
					imageHSV->imageData[3*input_address+1]=0;
					//red channel
					imageHSV->imageData[3*input_address+2]=255;
				}
				else if((fH>70&&fH<170)&&fV>60)
				{
					//blue channel
					imageHSV->imageData[3*input_address]=0;
					//green channel
					imageHSV->imageData[3*input_address+1]=255;
					//red channel
					imageHSV->imageData[3*input_address+2]=0;
				}
				else if((fH>190&&fH<290)&&fV>80)
				{
					//blue channel
					imageHSV->imageData[3*input_address]=255;
					//green channel
					imageHSV->imageData[3*input_address+1]=0;
					//red channel
					imageHSV->imageData[3*input_address+2]=0;
				}
				else 
				{
					//blue channel
					imageHSV->imageData[3*input_address]=0;
					//green channel
					imageHSV->imageData[3*input_address+1]=0;
					//red channel
					imageHSV->imageData[3*input_address+2]=0;
				}
						
						

			}
			else
			{
				//blue channel
				imageHSV->imageData[3*input_address]=imageRGB->imageData[3*input_address];
				//green channel
				imageHSV->imageData[3*input_address+1]=imageRGB->imageData[3*input_address+1];
				//red channel
				imageHSV->imageData[3*input_address+2]=imageRGB->imageData[3*input_address+2];

			}
		}
	}
   cvSaveImage("C:\\Users\\t6_514lg1.DML\\Desktop\\imageHSV.jpg",imageHSV);
  
   fclose(mfile);

	return imageHSV;
}
void mouseEvent(int event, int x, int y, int flags, void * param)
{
	 IplImage* img = (IplImage*) param;
    if (event == CV_EVENT_LBUTTONDOWN)
	{ 
        printf("%d,%d\n", x, y);
	}

}

int RGBColorOutput(int aveR, int aveG, int aveB)
{
		int result;
		aveR=aveR/10;
		aveB=aveB/10;
		aveG=aveG/10;
		//printf("R: %d",aveR);
		if(aveR>=240&&aveR<=255&&aveG<20&&aveB<20)
		{
				printf("Red\n");
				result=1;
		}
		else if(aveG>=240&&aveG<=255&&aveR<20&&aveB<20)
		{
				printf("Green\n");
				result=2;
		}
		else if(aveB>=240&&aveB<=255&&aveR<20&&aveG<20)
		{
				printf("Blue\n");
				result=3;
		}
		else
		{
				printf("NULL\n");
				result=0;
		}

		return result;
}	
void evaluateColor(const IplImage *imageRGB,int * color)
{

	//int color[5]; //colors 0=null 1=Red 2=Green 3 = Blue 
	IplImage *imageHSV = cvCreateImage(cvGetSize(imageRGB), 8, 3);

	int h = imageRGB->height;		// Pixel height.
	int w = imageRGB->width;		// Pixel width.
	int rowSizeRGB = imageRGB->widthStep;	// Size of row in bytes, including extra padding.
	unsigned char *imRGB = (unsigned char *)imageRGB->imageData;	// Pointer to the start of the image pixels.
	int rowSizeHSV = imageHSV->widthStep;	// Size of row in bytes, including extra padding.
	//char *imHSV = imageHSV->imageData;	// Pointer to the start of the image pixels.

			//uchar *pRGB = (uchar*)(imRGB + y*rowSizeRGB + x*3);
		int B, G, R, input_address;
		int aveR=0;
		int aveG=0;
		int aveB=0;

		//first box
		for(int x=50;x<60;x++)
		{
			input_address=(imageRGB->width*(293))+(x);
			B = (imRGB[3*input_address]);	// Blue component
			G = (imRGB[3*input_address + 1]);	// Green component
			R = (imRGB[3*input_address + 2]);	// Red component
			printf("bB: %d, bG: %d, bR: %d\n",B,G,R);
			aveR=R+aveR;
			aveG=G+aveG;
			aveB=B+aveB;
		}
		printf("First Color: ");
		color[0]=RGBColorOutput(aveR, aveG, aveB);
		

		aveR=0;
		aveG=0;
		aveB=0;
		//for second box
		for(int x=175;x<185;x++)
		{
			input_address=(imageRGB->width*(293))+(x);
			B = (imRGB[3*input_address]);	// Blue component
			G = (imRGB[3*input_address + 1]);	// Green component
			R = (imRGB[3*input_address + 2]);	// Red component
			printf("bB: %d, bG: %d, bR: %d\n",B,G,R);
			aveR=R+aveR;
			aveG=G+aveG;
			aveB=B+aveB;
		}
		printf("Second Color: ");
		color[1]=RGBColorOutput(aveR, aveG, aveB);
		aveR=0;
		aveG=0;
		aveB=0;
		//for third box
		for(int x=305;x<315;x++)
		{
			input_address=(imageRGB->width*(293))+(x);
			B = (imRGB[3*input_address]);	// Blue component
			G = (imRGB[3*input_address + 1]);	// Green component
			R = (imRGB[3*input_address + 2]);	// Red component
			printf("bB: %d, bG: %d, bR: %d\n",B,G,R);
			aveR=R+aveR;
			aveG=G+aveG;
			aveB=B+aveB;
		}

		printf("Third Color: ");
		color[2]=RGBColorOutput(aveR, aveG, aveB);
		aveR=0;
		aveG=0;
		aveB=0;
		//for fourth box
		
		for(int x=445;x<455;x++)
		{
			input_address=(imageRGB->width*(293))+(x);
			B = (imRGB[3*input_address]);	// Blue component
			G = (imRGB[3*input_address + 1]);	// Green component
			R = (imRGB[3*input_address + 2]);	// Red component
			
			aveR=R+aveR;
			aveG=G+aveG;
			aveB=B+aveB;
			printf("bB: %d, bG: %d, bR: %d\n",B,G,R);
		}
		
		//printf("\n%d",aveB);
		printf("Fourth Color: ");
		color[3]=RGBColorOutput(aveR, aveG, aveB);
		
		//printf("\n%d",aveB);
		
		aveR=0;
		aveG=0;
		aveB=0;
		//for fifth box
		
		for(int x=570;x<580;x++)
		{
			input_address=(imageRGB->width*(293))+(x);
			B = (imRGB[3*input_address]);	// Blue component
			G = (imRGB[3*input_address + 1]);	// Green component
			R = (imRGB[3*input_address + 2]);	// Red component
			
			aveR=R+aveR;
			aveG=G+aveG;
			aveB=B+aveB;
			printf("bB: %d, bG: %d, bR: %d\n",B,G,R);
		}
		printf("Fifth Color: ");
		color[4]=RGBColorOutput(aveR, aveG, aveB);

}