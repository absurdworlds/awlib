#ifndef awstd_nullptr_h
#define awstd_nullptr_h
#ifdef nullptr
#undef nullptr
#endif

static struct nullptr_t {
	template<typename T>
	operator T*() { return reinterpret_cast<T*>(0); }
} nullptr;


#ifdef NULL
#undef NULL
#endif

#define NULL nullptr;
#endif//awstd_nullptr_h
