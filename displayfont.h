/***************************************************************************
 * Nanotech allsizefont library; a library that facilitates interfacing Vga Monitor.
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/> 
 **************************************************************************/
#include <VGA.h>
#include "allsizefont.h"
#include <string.h>

#pragma used+
                                                         
unsigned char jj,ii,flag=0,DmSz=0;

unsigned char dataport;

void vga_write(unsigned char Dat,int x,int y,char sz,unsigned char Fncl,unsigned char Bkcl)
{
  
  for(jj = 0;jj < 8;jj++)
		{
		  if((Dat &(0x80>>jj)) == 0)
			{
				//SendDATA(False_Colour);//colour
                                 //Name01[0] = large1[i][j];
                                 VGA.drawPixel(x+((8*(DmSz-1))+jj),y+ii,Bkcl);
                                 //VGA.drawText(Name01,140+jj,50,28,0,0);
			}
	          else if((Dat &(0x80 >>jj)) != 0) 
			{
				//SendDATA(True_Colour);//colour
                                VGA.drawPixel(x+((8*(DmSz-1))+jj),y+ii,Fncl);
			}	
		}    //put data on data port 
                ii++;
                if(ii == 8*sz)
                ii = 0;
}

void enlarge(unsigned char *large1,char c,unsigned char size1)
{
	unsigned char i,j,temp;
	unsigned char k = 0;
	for(i=0;i<size1;i++)
	{
		for(j=0;j<8;j++)
		{
			large1[i] >>= 1;
			temp = c & 0x01;
			if(temp)
				large1[i] |= 0x80;
			if(++k == size1)
			{
				c >>= 1;
				k = 0;
			}
		}
	}
}

void putItSz(char c,int x,int y,unsigned char sz,unsigned char Fncl,unsigned char Bkcl)
{
  unsigned char i,j,k;
  //char large[8][sz];  
  unsigned char large1[8][8];
  for(i=0;i<8;i++)
  {                                     
	  enlarge(large1[i],font8x8[(8*c)+i],sz);		//c here;GCC (c-1)
  }
  DmSz = sz;
  for(j=0;j<sz;j++)
  {
	  for(i=0;i<8;i++)
	  {
		 for(k=0;k<sz;k++)
		  {
			  vga_write(large1[i][j],x,y,sz,Fncl,Bkcl);  
		  }
	  }
	  --DmSz;
  }
}

//--------------------------
void vga_putchar(char c,int x,int y,unsigned char sz,unsigned char Fncl,unsigned char Bkcl)
{
    putItSz(c,x,y,sz,Fncl,Bkcl);
}

//--------------------------
void vga_putstring(char *c,int x,int y,unsigned char sz,unsigned char space,unsigned char Fncl,unsigned char Bkcl)
{
   char i = 0;
   char special = 0;
while(i<strlen(c))
  {
      vga_putchar(*(c+i),x,y,sz,Fncl,Bkcl);
      x += (8+space)*sz;
      if(x>320-8*sz)
       {
        x=0;
        y +=(8*sz);///////////// Fault
      }
      i++;
  }

}

void Full_Colour_Display(unsigned char Colour)
{
  int i,j;
   for(i = 0;i < 240;i++)
		for(j = 0;j < 320;j++)	
                                 VGA.drawPixel(j,i,Colour);
		
}

//----------------------
void Display8x16Character(int uix,int uiy,char ch[],unsigned char Fncl,unsigned char Bkcl)
{
	unsigned char i,j,Chr=0,Q=0;
	while (ch[Q]!='\0')
	{
		Chr =ch[Q]-32;
		for(i = 0;i < 16;i++)
		{
		for(j = 0;j < 8;j++)
		{
			if( ((F8X16[Chr*16+i])&(0x80>>j)) == 0)
			{
				//SendDATA(False_Colour);//colour
                                 VGA.drawPixel(uix+j,(uiy+i),Bkcl);
			}
			else if(((F8X16[Chr*16+i])&(0x80>>j)) != 0) 
			{
				//SendDATA(True_Colour);//colour
                                VGA.drawPixel(uix+j,(uiy + i),Fncl);
			}
		}
		}
		uix+=8;
		Q++;
	}
}

void Display16x24Character(char uix,char uiy,char ch[],unsigned char Fncl,unsigned char Bkcl)
{
	unsigned char i,j,Chr=0,Q=0;
	while (ch[Q]!='\0')
	{
		Chr =ch[Q]-32;
		for(i = 0;i < 24;i++)
		{
		for(j = 0;j < 16;j++)
		{
			if( ((F16X24[Chr*24+i])&(0x8000>>j)) == 0)
			{
				//SendDATA(False_Colour);//colour
                                 VGA.drawPixel(uix+j,(uiy+i),Bkcl);
			}
			else if(((F16X24[Chr*24+i])&(0x8000>>j)) != 0) 
			{
				//SendDATA(True_Colour);//colour
                                VGA.drawPixel(uix+j,(uiy + i),Fncl);
			}
		}
		}
		uix+=16;
		Q++;
	}
}

#pragma used-
