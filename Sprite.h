#pragma once

#include <SDL.h>
#include <string>

/**
* Loads a texture (if possible) from a file. Currently only accepts a .bmp file.
* Will put the width and height of the loaded texture into the size parameter.
*
* @param std::string const &path the path (and filename) of the texture you wish to load.
* @param SDL_Renderer &rend the renderer with which you want to associated the texture.
* @param[out] int &w, int &h the size of the loaded texture (if the texture loads).
*
* @return SDL_Texture * the texture if loaded, otherwise nullptr.
*/
SDL_Texture *loadTexture(std::string const &path, SDL_Renderer *rend, int *w, int *h);

/**
* A container for a texture pointer and the src rectangle. Useful when want to 
*  use a texture atlas or otherwise have multiple lightweight drawables from a 
*  single texture loaded into graphics RAM.
* If you destroy a texture while it is still being used by one or more sprites,
*  attempts to draw that sprite are undefined. In addition a sprite only holds the
*  source information - rendering the actual sprite requires someone to specify
*  the destination (in screen coordinates) for the sprite to be drawn to.
* The source rectangle (or subrectangle) specifies the part of the texture that
*  you want draw on the screen. The pixels within the subrectangle will be 
*  scaled to fit into the destination rectangle when rendering.
*
* If this is the texture (which contains several sub-images)
* ___________________________________________________
* |										:=>			|
* |													|
* |			*   *			x   x			o		|
* |			  +				  +			   /T\		|
* |			{___}			 ___		    |		|
* |							/	\		   / \		|
* |													|
* |													|
* |_________________________________________________|
* 
* A sprite would be one of the sub-images and would be defined
*  by that sub-images source rectangle:
* ___________________________________________________
* |										:=>			|
* |	    x,y_______w									|
* |		   |*   *|			x   x			o		|
* |		   |  +	 |			  +			   /T\		|
* |		   |{___}|			 ___		    |		|
* |		   h	  			/	\		   / \		|
* |													|
* |													|
* |_________________________________________________|
*
* @see SDL_Texture
* @see SpriteAtlas
* 
* @author Kevin Forest
*/
class Sprite
{
public:
	/**
	* Create a sprite. If tex is null the sprites behaviour is undefined.
	* The texture can be a shared between multiple sprites - you can have the
	* sprites draw different things by specifying different source rectangles.
	* 
	* @param SDL_Texture *tex the backing texture for this sprite.
	* @param srcRect the source rectangle (in texture coordinates) for the sprite.
	*/
	Sprite(SDL_Texture *tex, SDL_Rect srcRect);
	virtual ~Sprite();

	/** 
	* @return the width of the sprites source rect in pixels
	*/
	int getWidth() const {
		return mSrcRect.w;
	}

	/**
	* @return the height of the sprites source rect in pixels
	*/
	int getHeight() const {
		return mSrcRect.h;
	}

	/**
	* Render the sprite to the screen at the specified destination.
	*  If dst.w == mSrcRect.w && dst.h == mSrcRect.h the sprite is
	*  drawn unscaled - otherwise the image is scaled on the x and y
	*  dimensions such that it fits with the destination rectangle
	*  as opposed to cropping the sprite to fit.
	*
	* @param SDL_Renderer *renderer the sprite gets drawn on here.
	* @param SDL_Rect dst The screen position and size where the sprite
	*                     should be drawn.
	*/
	void draw(SDL_Renderer *renderer, SDL_Rect dst) const;

	void draw(SDL_Renderer *renderer, SDL_Rect dst, float angle) const;


protected:
	/**
	* The source rectangle for the sprite - the pixels within the texture
	*  that are drawn when this sprite is rendered.
	*/
	SDL_Rect mSrcRect;

	/**
	* Pointer to the texture for the sprite.
	*/
	SDL_Texture *mTexture;
	
};

