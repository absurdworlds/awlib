

int guimain()
{
	std::unique_ptr<Canvas> canvas = createCanvas();
	std::unique_ptr<Skin> skin = createIrrSkin();
	canvas->setSkin(skin.get());

	std::unique_ptr<Window> window = createWindow(canvas.get());
}
