/* THE FOLLOWING CODE IS COPIED FROM
http://www.lowlevel.eu/wiki/Teil_8_-_Ein_erstes_Programm
AND WILL BE REPLACED LATER. */

typedef unsigned short uint16_t;

uint16_t* videomem = (uint16_t*) 0xb8000;
 
void _start(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        *videomem++ = (0x07 << 8) | ('0' + i);
    }
 
    while(1);
}