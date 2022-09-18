#ifndef ASSETS_H
#define ASSETS_H


#define BK_TILE_PAGES   3
#define ENTITY_PAGES    4
#define MUSIC_TRACKS    5
#define SFX_FILES       5

#define MAX_FILE_CHAR_LEN 10


// pointers to the sprites for all bk tiles
extern sprite_t* bk_tileset[BK_TILE_PAGES];
extern surface_t surface_bk_tile_page;

// pointers to the sprites for all entity tiles
extern sprite_t* entity_tileset[ENTITY_PAGES];

// xm format music player
extern xm64player_t music_player;

// actively loaded sound effect
extern wav64_t sound_effect;


// names for the bk sprites sprites in the filesystem
const char bk_tileset_names[BK_TILE_PAGES][MAX_FILE_CHAR_LEN] = 
{
    "rom:/tiles_1.sprite",
    "rom:/tiles_2.sprite",
    "rom:/tiles_3.sprite"
};

// names for the entity sprites in the filesystem
const char entity_tileset_names[ENTITY_PAGES][MAX_FILE_CHAR_LEN] = 
{
    "rom:/characters_1.sprite",
    "rom:/characters_2.sprite",
    "rom:/characters_3.sprite",
    "rom:/characters_4.sprite"
};

// names for the music tracks in the filesystem
const char music_track_names[MUSIC_TRACKS][MAX_FILE_CHAR_LEN] =
{
    "rom:/intro_theme.xm64",
    "rom:/menu_theme.xm64",
    " ",
    " ",
    " "
};

// names for the sound effects in the filesystem
const char sfx_file_names[SFX_FILES][MAX_FILE_CHAR_LEN] =
{
    "rom:/cannon.wav64",
    " ",
    " ",
    " ",
    " "
};

// initialize all background tile pages by loading in from ROM. Must be called after DFS_INIT
void bk_tile_sprites_init();
// free memory allocated for background tile pages
void bk_tile_sprites_free();

// initialize all entity sprite pages by loading in from ROM. Must be called after DFS_INIT
void entity_sprites_init();
// free memory allocated for entity sprite pages
void entity_sprites_free();



#endif