#include "DrawableElement.h"

DrawableElement::DrawableElement(SDL_Renderer *rendererArg)
{
	associate_rendr = rendererArg;
}

DrawableElement::~DrawableElement()
{
	;
}