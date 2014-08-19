
/**********************/
/* Havok magic spells */
/**********************/

// [id=keycode]
#include <Common/Base/keycode.cxx>

// [id=productfeatures]
// We're using only physics - we undef products even if the keycode is present so
// that we don't get the usual initialization for these products.
#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR

#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
// Vdb needs the reflected classes
//#define HK_EXCLUDE_FEATURE_RegisterReflectedClasses
#define HK_EXCLUDE_FEATURE_MemoryTracker
#define HK_EXCLUDE_FEATURE_hkpAccurateInertiaTensorComputer
#define HK_EXCLUDE_FEATURE_CompoundShape
#define HK_EXCLUDE_FEATURE_hkpAabbTreeWorldManager
#define HK_EXCLUDE_FEATURE_hkpKdTreeWorldManager

#include <Common/Base/Config/hkProductFeatures.cxx>
