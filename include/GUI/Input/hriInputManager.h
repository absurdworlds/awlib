
#ifndef __HG_hriInputManager__
#define __HG_hriInputManager__

namespace irr
{
namespace gui
{
	class ICursorControl;
}

}

namespace hrengin
{
namespace gui
{

class hriInputManager
{
	public:
		virtual irr::gui::ICursorControl* GetCursorControl();
};

} // namespace io
} // namespace hrengin

#endif//__HG_hriInputManager__