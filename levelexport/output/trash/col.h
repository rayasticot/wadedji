
//{{BLOCK(col)

//======================================================================
//
//	col, 1024x264@8, 
//	Transparent color : 00,00,00
//	+ palette 256 entries, not compressed
//	+ 16 tiles (t reduced) not compressed
//	+ regular map (flat), not compressed, 128x33 
//	Total size: 512 + 1024 + 8448 = 9984
//
//	Time-stamp: 2023-10-28, 02:26:13
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_COL_H
#define GRIT_COL_H

#define colTilesLen 1024
extern const unsigned int colTiles[256];

#define colMapLen 8448
extern const unsigned short colMap[4224];

#define colPalLen 512
extern const unsigned short colPal[256];

#endif // GRIT_COL_H

//}}BLOCK(col)
