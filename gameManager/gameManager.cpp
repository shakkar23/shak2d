#include "gameManager.hpp"
#include "../SDL/main.hpp"
#include "../helper/Coord.hpp"
#include "../game/inGame/Entities/Renderable.hpp"
#include <algorithm>

void gameManager::Init(RenderWindow &window){
	
    //clear the textures so we can reinitialize game
    tex0.clear();
    tex1.clear();
    std::string path = "./assets/SpriteSheet.png";
    dirt =   TextureDictionary::getSpriteSheet(window, path, 0, 0, 8);
    stone =  TextureDictionary::getSpriteSheet(window, path, 1, 0, 8);
	sky =    TextureDictionary::getSpriteSheet(window, path, 3, 0, 8);
    player = TextureDictionary::getSpriteSheet(window, path, 0, 1, 8);
	
    background.load(window, path,0,0,1);

    tex0.push_back(&dirt);
	tex0.push_back(&stone);
    level0.level.at(0).at(0) = levelData::dirt;
	level0.level.at(0).at(1) = levelData::dirt;
    for (auto& col : level0.level) {
            col.at(col.size() -1) = levelData::dirt;
    }

    auto placeDirt = [](levels &guh, int x, int y) {
        guh.level.at(x).at(guh.level[0].size() - 1 - y) = levelData::dirt;
    };
    
    for(int i=0; i < 10; i++){
			placeDirt(level0, i, i);
	}
    
    mrGuy.boundingBox.x = 2;
	mrGuy.boundingBox.y = 2;

	/*
    level0.level.at(1).at(level0.level[0].size() - 1) = levelData::dirt;
	level0.level.at(2).at(level0.level[0].size() - 2) = levelData::dirt;
	level0.level.at(3).at(level0.level[0].size() - 3) = levelData::dirt;
	level0.level.at(4).at(level0.level[0].size() - 4) = levelData::dirt;
	level0.level.at(5).at(level0.level[0].size() - 5) = levelData::dirt;
    */
}

void gameManager::movement(const moveDirection& prevplayer, const moveDirection& player) {
    mrGuy.update(prevplayer, player, DELTATIME);
}
    levelData gameManager::GetTile(float x, float y) {
        // check if x and y are within the bounds of the level
        if (x >= 0 && x < level0.level.size() && y >= 0 && y < level0.level[0].size()) {
            return level0.level[x][y];
        }
		if(x < 0 || x > level0.level.size() || y >= 0)
				return levelData::stone;
			return levelData::sky;
    };
void gameManager::collision() {

    //gravity
	float fNewPlayerPosX = mrGuy.boundingBox.x + (mrGuy.velocity.x + mrGuy.acceleration.x) * DELTATIME;
    float fNewPlayerPosY = mrGuy.boundingBox.y + (mrGuy.velocity.y + mrGuy.acceleration.y) * DELTATIME;
	
    // drag
    


    Coord<float> playerSizeCoord = { 1.0f, 1.0f }; 
	
    if (mrGuy.velocity.x <= 0) // Moving Left
    {
        bool inABlock = false;
        for (int i = 0; i <= playerSizeCoord.y; i++) {
            bool end = (i + 1.0f) > playerSizeCoord.y ? true : false;
            if (GetTile(fNewPlayerPosX, mrGuy.boundingBox.y + (i - (end * 0.0001f))) != levelData::sky)
            {
                //if collided
                inABlock = true;
                break;
            }
        }
        if (inABlock)
        {
            if (fNewPlayerPosX < 0) fNewPlayerPosX--;
            fNewPlayerPosX = (int)fNewPlayerPosX + 1;
            mrGuy.velocity.x = 0;
        }
    }
    else // Moving Right
    {
        bool inABlock = false;
        for (int i = 0; i <= playerSizeCoord.y; i++) {
            bool end = (i + 1.0f) > playerSizeCoord.y ? true : false;
            if (GetTile(fNewPlayerPosX + playerSizeCoord.x - 0.0001f, mrGuy.boundingBox.y + i - (end * 0.0001f)) != levelData::sky)
            {
                inABlock = true;
                break;
            }
        }
        if (inABlock)
        {
            fNewPlayerPosX = (int)fNewPlayerPosX;
            mrGuy.velocity.x = 0;

        }
    }

    mrGuy.isOnGround = false;
    if (mrGuy.velocity.y <= 0) // Moving Up
    {
        bool inABlock = false;
        for (int i = 0; i <= playerSizeCoord.x; i++) {
            bool end = (i + 1.0f) > playerSizeCoord.x ? true : false;
            if (GetTile(fNewPlayerPosX + i - (end * 0.0001f) , fNewPlayerPosY) != levelData::sky)
            {
                inABlock = true;
                break;
            }
        }
        if (inABlock)
        {			
            fNewPlayerPosY = (int)fNewPlayerPosY + 1;
            mrGuy.velocity.y = 0;
        }
    }
    else // Moving Down
    {
        bool inABlock = false;
        for (int i = 0; i <= playerSizeCoord.x; i++) {
            bool end = (i + 1.0f) > playerSizeCoord.x ? true : false;
            if (GetTile(fNewPlayerPosX + i - (end * 0.0001f) , fNewPlayerPosY + playerSizeCoord.y - 0.0001f) != levelData::sky)
            {
                inABlock = true;
                break;
            }
        }
        if (inABlock)
          //if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.999f) != levelData::sky || GetTile(fNewPlayerPosX + 0.999f, fNewPlayerPosY + 1.999f) != levelData::sky)
        {

            if (fNewPlayerPosY < 0)
                fNewPlayerPosY--;
            fNewPlayerPosY = (int)fNewPlayerPosY;
            mrGuy.velocity.y = 0;
            mrGuy.isOnGround = true; // Player has a solid surface underfoot
        }
    }
	mrGuy.boundingBox.x = fNewPlayerPosX;
	mrGuy.boundingBox.y = fNewPlayerPosY;
    
	
}

bool gameManager::winCondition() {
    return false;
}
void gameManager::gameLogic(const moveDirection& prevplayer, const moveDirection &player) {
    
    movement(prevplayer, player);
    collision();
    //if (winCondition())
    //    won = true;
}
void gameManager::render(RenderWindow &window) {
    window.clear();
	cameraX = mrGuy.boundingBox.x + (1 / 2.0f);
    cameraY = mrGuy.boundingBox.y + (1 / 2.0f);

    int winX{}, winY{};
    window.getWindowSize(winX, winY);
	
    // width in pixels 
    constexpr float tileWidth = 16.0f * 4.0f;

    const float nVisibleTilesX = (float)winX / tileWidth;
    const float nVisibleTilesY = (float)winY / tileWidth;

	// clamp camera position to prevent it from going out of bounds
	//cameraX = std::max((float)nVisibleTilesX/2.0f, std::min(cameraX, float(level0.level.size())    - float(nVisibleTilesX / 2)));
	//cameraY = std::max((float)nVisibleTilesY / 2.0f, std::min(cameraY, float(level0.level[0].size()) - float(nVisibleTilesY / 2)));
	
    // Calculate Top-Leftmost visible tile
    float fOffsetX = cameraX - (float)nVisibleTilesX / 2.0f;
    float fOffsetY = cameraY - (float)nVisibleTilesY / 2.0f;

    // Clamp camera to game boundaries
    if (fOffsetX < 0)
        fOffsetX = 0;

    if (fOffsetY < 0)
        fOffsetY = 0;

    if (fOffsetX > level0.level.size() - nVisibleTilesX)
        fOffsetX = level0.level.size() - nVisibleTilesX;
    
    if (fOffsetY > level0.level[0].size() - nVisibleTilesY)
        fOffsetY = level0.level[0].size() - nVisibleTilesY;

    // Get offsets for smooth movement
    const float fTileOffsetX = (fOffsetX - (int)fOffsetX) * tileWidth;
    const float fTileOffsetY = (fOffsetY - (int)fOffsetY) * tileWidth;

    //window.render({}, {0,0,winX, winY}, background.texture->texture);

	for(int x = -1; x < nVisibleTilesX + 1; x++) {
        for(int y = -1; y < nVisibleTilesY + 1; y++) {

            SDL_Rect dst{};
                dst.x = (int)ceil(x * tileWidth - (int)fTileOffsetX);
                dst.y = (int)ceil(y * tileWidth - (int)fTileOffsetY);
                dst.w = (int)ceil(tileWidth);
                dst.h = (int)ceil(tileWidth);
			
            switch (GetTile(x + fOffsetX, y + fOffsetY))
            {
                
            case levelData::dirt:
                window.render(dirt.srcRect, dst, dirt.texture->texture);
                break;
            case levelData::stone:
                window.render(stone.srcRect, dst, stone.texture->texture);
                break;
            case levelData::sky:
                window.render(sky.srcRect, dst, sky.texture->texture);
                break;
            default:
                break;
            }
		}
	}
    window.render(player.srcRect, {
        //1715.50757
        (int)((mrGuy.boundingBox.x - fOffsetX) * tileWidth),
        (int)((mrGuy.boundingBox.y - fOffsetY) * tileWidth),
        (int)ceil(tileWidth),
        (int)ceil(tileWidth),
        }, player.texture->texture);

    
	
    window.display();
}
gameManager GameManager;