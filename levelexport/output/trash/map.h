
//{{BLOCK(map)

//======================================================================
//
//	map, 1024x256@8, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 30 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 128x32 
//	Total size: 512 + 1920 + 8192 = 10624
//
//	Time-stamp: 2023-10-27, 23:38:51
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAP_H
#define GRIT_MAP_H

#define mapTilesLen 1920
extern const unsigned int mapTiles[480];

#define mapMapLen 8192
extern const unsigned short mapMap[4096];

#define mapPalLen 512
extern const unsigned short mapPal[256];

#endif // GRIT_MAP_H

//}}BLOCK(map)
