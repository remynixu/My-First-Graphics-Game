SECTIONS
{
    .assets_table : ALIGN(16)
    {
        /*
         * Here are where the entities are placed! :D
         */
         
        __ent_arundel_png_start = .;
        *arundel.png.o(.data) 
        __ent_arundel_png_end = .;

        . = ALIGN(16);

        __ent_null_png_start = .;
        *entity_null.png.o(.data)
        __ent_null_png_end = .;

        . = ALIGN(16);

        __ent_rock_png_start = .;
        *rock.png.o(.data)
        __ent_rock_png_end = .;

        . = ALIGN(16);

        /*
         * Here are where the tiles are placed! :D
         */

        __til_grass_png_start = .;
        *grass.png.o(.data)
        __til_grass_png_end = .;

        . = ALIGN(16);

        __til_null_png_start = .;
        *tile_null.png.o(.data)
        __til_null_png_end = .;
    }
}
 
INSERT AFTER .rdata
