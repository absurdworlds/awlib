#include <memory>

#include <Irrlicht/irrlicht.h>
#include <Irrlicht/IrrlichtDevice.h>

#include <awengine/gui/Canvas.h>
#include <awengine/gui/Window.h>
#include <awengine/gui/Drawer.h>

#include "IrrEngine.h"

using namespace irr;
namespace awrts {
namespace gui {


int guimain()
{
	IrrlichtDevice * device = createDevice(video::EDT_OPENGL,
			irr::core::dimension2d<u32>(800, 600));
	auto driver = device->getVideoDriver();
	std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>();
	std::unique_ptr<Engine> engine = std::make_unique<IrrEngine>(driver);
	std::unique_ptr<Style> style = std::make_unique<Style>();
	canvas->setStyle(style.get());
	style->initDefaults();
	style->getElementStyle("window");

	auto window = std::make_unique<Window>();
	window->setRect(Rect<Coordinate>(0.1,0.1,0.4,0.4));
	canvas->addElement(std::move(window));

	Drawer drawer(*engine);

	while(device->run() && driver)
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, irr::video::SColor(255,40,138,155));

		canvas->accept(drawer);

		driver->endScene();
	}

	device->drop();
}

} // namespace core
} // namespace awrts

int main()
{
	awrts::gui::guimain();
}
