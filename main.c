// Program Name: Centipede
// Author(s): KingInfinity

/* Keep these headers */
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Other available headers */
// including stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h

#include <lib/ce/graphc.h>
#include <lib/ce/fileioc.h>
#include <lib/ce/keypadc.h>
#include <debug.h>
#include <spritesheet.h>
#include <main.h>


/* Put all your code here */
unsigned char spriteOutput[64];
unsigned char mushroomSprite[64];

bool end = false;
uint8_t key;
int positionx = 120;
int positiony = 120; 
bool mushroom[39][29];

void main() {
	gc_InitGraph();
	gc_DrawBuffer();
	spriteSheet(spritesheet,mushroomSprite,107,88,64,8,8,8);
	gameLoop();
	gc_CloseGraph();
	pgrm_CleanUp();
}
void gameLoop() {
	uint8_t x;
	uint8_t y;
	uint8_t oldx;
	uint8_t oldy;
	uint8_t amount = rand() % 10;
	positionx = 120;
	positiony = 120;
	amount+=10;
	srand(rtc_Time());
	while(amount>0) {
		amount--;
   		x = generateRandomNumber(39, oldx);
		y = generateRandomNumber(29, oldy);
		oldx = x;
		oldy=y;
		mushroom[x][y] = true;
	}
	while(end==false) {
		gc_SetPalette(spritesheet_pal, sizeof spritesheet_pal);
		gc_SwapDraw();
		gc_FillScrn(0x00);
    	key = kb_ScanGroup(kb_group_6);
		if(key & kb_Clear) {
			end=true;
		}
		dbg_printf(dbgout, "%d ",positiony);
		key = kb_ScanGroup(kb_group_7);
		if (key & kb_Down) {
			if (positiony < 224) {
				positiony+=8;
			}
		}
		if (key & kb_Up) {
			if (positiony > 0) {
				positiony-=8;
			}
		}
		if (key & kb_Left) {
			if (positionx > 0) {
				positionx-=8;
			}
		}
		if (key & kb_Right) {
			if (positionx < 304) {
				positionx+=8;
			}
		}
		
	spriteSheet(spritesheet,spriteOutput,107,88,0,80,8,8);
	gc_NoClipDrawScaledSprite(spriteOutput,positionx,positiony,8,8,2,2);
		
	for (y=0; y<30; y++) {
   		for (x=0; x<40; x++) {
				if(mushroom[x][y] == true) {
						gc_NoClipDrawScaledSprite(mushroomSprite,x*8,y*8,8,8,2,2);
				}
			}
	}
	}
}
int generateRandomNumber(int max, int previous) {
	int x = rand() % max;
	if(x==previous) {
		return generateRandomNumber(max, previous);
	}
	return x;
}
void spriteSheet(uint8_t *data, uint8_t *output, uint8_t originalWidth, uint8_t originalHeight, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint8_t pictureX=0;
	uint8_t pictureY=0;
	uint8_t pointerX=x;
	uint8_t pointerY=y;
	uint8_t originalX=x;
	uint8_t originalY=y;
	while(pictureY<=height) {
		if(pictureX>width) {
			pictureX=0;
			pointerX=originalX;
			pictureY++;
			pointerY++;
		}
		output[(pictureY*(width))+pictureX]=data[(pointerY*(originalWidth))+pointerX];
		pictureX++;
		pointerX++;
	}
}