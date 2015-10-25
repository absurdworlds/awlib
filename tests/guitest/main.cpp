#include <memory>

#include <Irrlicht/IrrlichtDevice.h>

#include <awengine/gui/Canvas.h>
#include <awengine/gui/Window.h>
#include <awengine/gui/Drawer.h>
#include <awengine/core/Logger.h>

#include <awengine/irr/gui/IrrEngine.h>
#include <awengine/irr/gui/InputManager.h>

#include <iostream>

using namespace irr;
namespace irr {
extern "C" IRRLICHT_API IrrlichtDevice* IRRCALLCONV createDevice(
	video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,
	// parantheses are necessary for some compilers
	const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),
	u32 bits = 16,
	bool fullscreen = false,
	bool stencilbuffer = false,
	bool vsync = false,
	IEventReceiver* receiver = 0);
}
namespace awrts {
size_t Event::eventTypes;

class Couter : public core::LogBook {
public:
	virtual void log(std::string msg, core::LogLevel level)
	{
		std::cout << msg << std::endl;
	}
};

namespace gui {


int guimain()
{
	Couter cou;
	core::Logger* log = core::createLogger();
	log->registerLog(&cou);
	core::Logger::setGlobalLogger(log);
	IrrlichtDevice * device = createDevice(video::EDT_OPENGL,
			irr::core::dimension2d<u32>(800, 600));
	auto driver = device->getVideoDriver();
	auto input = std::make_unique<impl::InputManager>(device);
	std::unique_ptr<Engine> engine = std::make_unique<IrrEngine>(driver);
	std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>();
	std::unique_ptr<Style> style = std::make_unique<Style>();
	canvas->setStyle(style.get());
	style->initDefaults();
	style->getElementStyle("window");
	canvas->setName("c");

	canvas->setRect(Rect<Coordinate>(0.0,0.0,1.0,1.0));
	input->registerReceiver(canvas.get());

	auto window = std::make_unique<Window>();
	auto t = window.get();
	window->setRect(Rect<Coordinate>(0.1,0.1,0.9,0.9));
	//window->setRect(Rect<Coordinate>(0.1,0.1,0.4,0.4));
	/*
	window->setRect(Rect<Coordinate>(Coordinate(0.1,5),
				Coordinate(0.1,5),
				Coordinate(0.4,-5),
				Coordinate(0.4,-5)));
	//			*/
	canvas->addElement(std::move(window));
	auto tt = &*canvas->getFirstChild();
	tt->setName("w");

	if (tt == t)
		log->push("heey");
	log->push("window1: " + std::to_string((size_t)t));

	auto window2 = std::make_unique<Window>();
	log->push("window2: " + std::to_string((size_t)window2.get()));
	window2->setDraggable(true);
	window2->setRect(Rect<Coordinate>(0.5,0.5,0.9,0.9));
	window2->setName("x");
	t->addElement(std::move(window2));

	window2 = std::make_unique<Window>();
	log->push("window3: " + std::to_string((size_t)window2.get()));
	window2->setDraggable(true);
	window2->setRect(Rect<Coordinate>(0.1,0.1,0.4,0.4));
	window2->setName("x");
	t->addElement(std::move(window2));

	window2 = std::make_unique<Window>();
	log->push("window4: " + std::to_string((size_t)window2.get()));
	window2->setDraggable(true);
	window2->setRect(Rect<Coordinate>(0.6,0.1,0.95,0.4));
	window2->setName("x");
	t->addElement(std::move(window2));
	Drawer drawer(*engine);

	while(device->run() && driver)
	if (device->isWindowActive()) {
		driver->beginScene(true, true, irr::video::SColor(255,40,138,155));

		canvas->accept(drawer);

		//device->sleep(1);

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
