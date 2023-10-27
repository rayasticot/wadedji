
//{{BLOCK(col)

//======================================================================
//
//	col, 768x520@8, 
//	Transparent color : 00,00,00
//	+ palette 256 entries, not compressed
//	+ 16 tiles (t reduced) not compressed
//	+ regular map (flat), not compressed, 96x65 
//	Total size: 512 + 1024 + 12480 = 14016
//
//	Time-stamp: 2023-10-27, 00:32:11
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_COL_H
#define GRIT_COL_H

#define colTilesLen 1024
extern const unsigned int colTiles[256];

#define colMapLen 12480
extern const unsigned short colMap[6240];

#define colPalLen 512
extern const unsigned short colPal[256];

#endif // GRIT_COL_H

//}}BLOCK(col)
