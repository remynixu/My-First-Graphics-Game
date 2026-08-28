SECTIONS
{
    .engine_init_table : ALIGN(8)
    {
        __engine_inits_start = .;
        
        KEEP(*libengine_core.a:(.engine_inits))
        
        __engine_inits_end = .;
    }
}

/*
 * These are just going to be pointers for functions so it's okay to put
 * these in read-only data.
 */
 
INSERT AFTER .rdata