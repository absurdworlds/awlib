#ifndef awstd_nullptr_h
#define awstd_nullptr_h
#ifdef nullptr
#undef nullptr
#endif

static const struct nullptr_t {
	template<typename T>
	operator T*() const { return 0; }

	template<class C, class T>
	operator T C::*() const { return 0; }

	// for sizeof()
	void const* const _dummy_;

private:
	void operator&() const;
} nullptr = {0};


#ifdef NULL
#undef NULL
#endif

#define NULL nullptr
#endif//awstd_nullptr_h
