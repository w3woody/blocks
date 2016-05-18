/*  levels.cpp
 *  
 *      Constants with the levels for game play
 */

/*  Blocks: A simple Arduboy game.
 *
 *  Copyright © 2016 by William Edward Woody
 *
 *  This program is free software: you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as published by the 
 *  Free Software Foundation, either version 3 of the License, or (at your 
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along 
 *  with this program. If not, see <http://www.gnu.org/licenses/>
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "levels.h"

/****************************************************************************/
/*                                                                          */
/*  Constants                                                               */
/*                                                                          */
/****************************************************************************/

/*  LevelMap
 *
 *      Each level is a 16 byte bitmap shwoing which areas have walls. A 1 bit
 *  is a wall.
 */
const static PROGMEM uint16_t LevelMap[] = 
{
    // Level 1
    0xFFFF,
    0x8001,
    0x8001,
    0x8001,
    0x8001,
    0x8001,
    0x8001,
    0xFFFF,
    
    // Level 2
    0xFFFF,
    0x8001,
    0x8001,
    0x8101,
    0x8101,
    0x8001,
    0x8001,
    0xFFFF,
    
    // Level 3
    0xFFFF,
    0x8001,
    0x8001,
    0x8101,
    0x8101,
    0x8001,
    0x8001,
    0xFFFF,
    
    // Level 4
    0xFFFF,
    0xF47F,
    0xF47F,
    0xF641,
    0xF001,
    0xF401,
    0xF601,
    0xFFFF,

    // Level 5
    0xFFFF,
    0x8F09,
    0x8909,
    0x8109,
    0x8909,
    0x8801,
    0x8F01,
    0xFFFF,

    // Level 6
    0xFFFF,
    0xFFFF,
    0xFF9F,
    0xC01F,
    0xC61F,
    0xFCFF,
    0xFC01,
    0xFFFF,

    // Level 7
    0xFFFF,         // 1111111111111111
    0xFFFF,         // 1111111111111111
    0xFE3F,         // 1111111000111111
    0xF83F,         // 1111100000111111
    0xF93F,         // 1111100100111111
    0xF9FF,         // 1111100111111111
    0xFFFF,         // 1111111111111111
    0xFFFF,         // 1111111111111111

    // Level 8
    0xFFFF,
    0xF0FF,
    0xF08F,
    0xF00F,
    0xFFCF,
    0xFFCF,
    0xFFCF,
    0xFFFF,
};

/*  BoxMap
 *
 *      Each level box map is a header (with the number of boxes), followed
 *  by a byte per box, with the format XXXXYYYY.
 */
const static PROGMEM uint8_t BoxMap[] =
{
    1,
    0x84,
    1,
    0x54,
    2,
    0x53,
    0x54,
    2,
    0x73,
    0x72,
    4,
    0x22,
    0x24,
    0x32,
    0x34,
    2,
    0x53,
    0x74,
    2,
    0x64,
    0x83,
    3,
    0x52,
    0x62,
    0x53,
};


/*  EndMap
 *
 *      Same format as the BoxMap; this gives the position where the boxes
 *  should go after being moved..
 */
const static PROGMEM uint8_t EndMap[] =
{
    1,
    0xA4,
    1,
    0xA4,   
    2,
    0xA3,   
    0xA4,   
    2,
    0xB4,
    0xD4,
    4,
    0xD1,
    0xD2,
    0xE1,
    0xE2,
    2,
    0xD6,
    0xE6,
    2,
    0x82,
    0x93,
    3,
    0xA2,
    0xB2,
    0xB3,
};

/*  StartPos
 * 
 *      One byte per level, in the same XXXXYYYY format as used with boxes;
 *  this gives the initial position of the player
 */

const static PROGMEM uint8_t StartPos[] = {
    0x44,
    0x44,
    0x44,
    0x43,
    0x23,
    0x73,
    0x53,
    0xA6,
};

/****************************************************************************/
/*                                                                          */
/*  Methods                                                                 */
/*                                                                          */
/****************************************************************************/

/*  GetBoundaries
 *
 *      Get the boundaries for each level
 */
 
void GetBoundaries(uint8_t levelIndex, uint16_t *mem)
{
    memcpy_P(mem,LevelMap + levelIndex * 8,16);
}

/*  ParseMap
 *
 *      Runs the common code for getting the boxes or end map locations.
 */

static uint8_t ParseMap(uint8_t levelIndex, const uint8_t *src, uint8_t *dest)
{
    uint8_t len;
    while (levelIndex > 0) {
        len = pgm_read_byte(src);
        src += len+1;
        --levelIndex;
    }
    len = pgm_read_byte(src);
    ++src;
    memcpy_P(dest,src,len);
    return len;
}

/*  GetBoxes
 * 
 *      Copy an array of box positions within our level. These are the initial
 *  box positions. This assumes the boxpos array is at least MAXBOXES in size
 */
uint8_t GetBoxes(uint8_t levelIndex, uint8_t *boxpos)
{
    return ParseMap(levelIndex,BoxMap,boxpos);   
}

/*  GetEnds
 * 
 *      Get the location where the boxes are to be moved.
 */
uint8_t GetEnds(uint8_t levelIndex, uint8_t *endpos)
{
    return ParseMap(levelIndex,EndMap,endpos);
}

/*  GetStartPos
 *   
 *      Get the location of the player at the start of the level.
 */
uint8_t GetStartPos(uint8_t levelIndex)
{
    return pgm_read_byte(StartPos + levelIndex);
}

