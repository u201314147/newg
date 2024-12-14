#ifdef USE_ONLINE
#include "global.h"

//for papu pyramid and hot air skyway (mostly for ban easy tizzianos)
bool papumoon;

void moongravity() {
    if (octr->special == 4) {

//if not papu pyramid or HAS then user normal low gravity
int moonvalue = papumoon ? 400 : 369;
        // low gravity event
		// space gravity (369) in og ctr is 41% of normal gravity (900)
        for (int i = 0; i < NUM_CLASSES; i++) {
            data.metaPhys[0].value[i] = moonvalue;  
        }
    }
	
    else {

        for (int i = 0; i < NUM_CLASSES; i++) {
            data.metaPhys[0].value[i] = 900; //normal
        }
    }
}

#endif