#include <memory>

#include <awengine/gui/Canvas.h>
#include <awengine/gui/Window.h>
#include <awengine/gui/Drawer.h>

#include "IrrSkin.h"

#include <Irrlicht/irrlicht.h>
#include <Irrlicht/IrrlichtDevice.h>
#include <Irrlicht/driverChoice.h>
using namespace irr;
namespace awrts {
namespace gui {

int guimain()
{
	IrrlichtDevice * device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600));
	auto driver = device->getVideoDriver();
	std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>();
	std::unique_ptr<Skin> skin = std::make_unique<IrrSkin>(driver);
	canvas->setSkin(skin.get());

	auto window = std::make_unique<Window>();
	window->setRect(Rect<f32>(0.1,0.1,0.4,0.4));
	canvas->addElement(std::move(window));

	Drawer drawer;

	canvas->accept(drawer);

	while(device->run() && driver)
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, irr::video::SColor(255,40,138,155));

		canvas->accept(drawer);

		driver->endScene();
	}

	device->drop();
}

}
}

int main()
{
	awrts::gui::guimain();
}
