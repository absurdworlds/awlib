template<class T, class sig>
struct memfun;

template<class T, typename R, typename...Args>
struct memfun<T, R(Args...)> {
	using type = R (T::*)(Args...);
};

template<class T, class sig>
using member_func = typename memfun<T,sig>::type;
