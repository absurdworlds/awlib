#include <memory>

#include <awengine/gui/Canvas.h>
#include <awengine/gui/Window.h>

#include "IrrSkin.h"

namespace awrts {
namespace gui {

int guimain()
{
	std::unique_ptr<Canvas> canvas(new Canvas());
	std::unique_ptr<Skin> skin(new IrrSkin());
	canvas->setSkin(skin.get());

	std::unique_ptr<Window> window = std::make_unique<Window>(canvas.get());
}

}
}
