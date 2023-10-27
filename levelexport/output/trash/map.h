
//{{BLOCK(map)

//======================================================================
//
//	map, 768x512@8, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 31 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 96x64 
//	Total size: 512 + 1984 + 12288 = 14784
//
//	Time-stamp: 2023-10-27, 00:32:11
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAP_H
#define GRIT_MAP_H

#define mapTilesLen 1984
extern const unsigned int mapTiles[496];

#define mapMapLen 12288
extern const unsigned short mapMap[6144];

#define mapPalLen 512
extern const unsigned short mapPal[256];

#endif // GRIT_MAP_H

//}}BLOCK(map)
