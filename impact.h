#ifndef _IMPACT__H
#define _IMPACT__H

bool impact_bird_block(const Bird& chim, const Map& map_) {
    SDL_Rect chimRect = chim.getRect();
        int x = (chimRect.x - scr_width + scr_height)/tile_size;
        int y = chimRect.y/tile_size;
    if(map_[x][y]!=0){
            return true;
    }
    return false;
}

#endif
