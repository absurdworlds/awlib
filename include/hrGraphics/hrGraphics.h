
#ifndef __HR_GRAPHICS_H__
#define __HR_GRAPHICS_H__


#include <hrConfig.h>

#ifdef HRGRAPHICS_EXPORTS
#define HRGRAPHICS_API __declspec(dllexport)
#else
#define HRGRAPHICS_API __declspec(dllimport)
#endif

#include <hriEncore.h>
#include <hriGraphicsCore.h>

namespace hrengin
{
namespace graphics
{

// Startup the engine
// TODO: workout the way settings are passed to graphics engine
//hriGraphicsCore* Startup(GRAPHICS_DRIVER gdtype, uint32_t dimx, uint32_t dimy, uint8_t bitness, bool fullscreen, bool vsync);
HRGRAPHICS_API hriGraphicsCore* Startup(hriEncore* parent);

} // namespace graphics
}
 
#endif //__HR_GRAPHICS_H__