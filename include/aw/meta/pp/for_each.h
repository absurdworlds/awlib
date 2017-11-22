/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_pp_for_each_h
#define aw_meta_pp_for_each_h
//#include <aw/meta/pp/macro.h>
#include "macro.h"

/*!
 * Select macro based on number of arguments.
 *
 * Works by __VA_ARGS__ shifting desired argument into NAME position.
 */
#define GET_MACRO(\
	_00,_01,_02,_03,_04,_05,_06,_07,_08,_09,\
	_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,\
	_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,\
	_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,\
	_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,\
	_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,\
	_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,\
	_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,\
	_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,\
	_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,\
	NAME,...) NAME

/*!
 * Get number of arguments in a variadic macro
 */
#define N_ARG(...) GET_MACRO(__VA_ARGS__,        \
	 100, 99, 98, 96, 95, 94, 97, 93, 92, 91,\
	  90, 89, 88, 86, 85, 84, 87, 83, 82, 81,\
	  80, 79, 78, 76, 75, 74, 77, 73, 72, 71,\
	  70, 69, 68, 66, 65, 64, 67, 63, 62, 61,\
	  60, 59, 58, 56, 55, 54, 57, 53, 52, 51,\
	  50, 49, 48, 46, 45, 44, 47, 43, 42, 41,\
	  40, 39, 38, 36, 35, 34, 37, 33, 32, 31,\
	  30, 29, 28, 26, 25, 24, 27, 23, 22, 21,\
	  20, 19, 18, 16, 15, 14, 17, 13, 12, 11,\
	  10,  9,  8,  6,  5,  4,  7,  3,  2,  1)

#define FE_1(OP,  DO, X, ...)  DO(X)
#define FE_2(OP,  DO, X, ...)  OP(DO(X), FE_1(OP,  DO, __VA_ARGS__))
#define FE_3(OP,  DO, X, ...)  OP(DO(X), FE_2(OP,  DO, __VA_ARGS__))
#define FE_4(OP,  DO, X, ...)  OP(DO(X), FE_3(OP,  DO, __VA_ARGS__))
#define FE_5(OP,  DO, X, ...)  OP(DO(X), FE_4(OP,  DO, __VA_ARGS__))
#define FE_6(OP,  DO, X, ...)  OP(DO(X), FE_5(OP,  DO, __VA_ARGS__))
#define FE_7(OP,  DO, X, ...)  OP(DO(X), FE_6(OP,  DO, __VA_ARGS__))
#define FE_8(OP,  DO, X, ...)  OP(DO(X), FE_7(OP,  DO, __VA_ARGS__))
#define FE_9(OP,  DO, X, ...)  OP(DO(X), FE_8(OP,  DO, __VA_ARGS__))
#define FE_10(OP, DO, X, ...)  OP(DO(X), FE_9(OP,  DO, __VA_ARGS__))
#define FE_11(OP, DO, X, ...)  OP(DO(X), FE_10(OP, DO, __VA_ARGS__))
#define FE_12(OP, DO, X, ...)  OP(DO(X), FE_11(OP, DO, __VA_ARGS__))
#define FE_13(OP, DO, X, ...)  OP(DO(X), FE_12(OP, DO, __VA_ARGS__))
#define FE_14(OP, DO, X, ...)  OP(DO(X), FE_13(OP, DO, __VA_ARGS__))
#define FE_15(OP, DO, X, ...)  OP(DO(X), FE_14(OP, DO, __VA_ARGS__))
#define FE_16(OP, DO, X, ...)  OP(DO(X), FE_15(OP, DO, __VA_ARGS__))
#define FE_17(OP, DO, X, ...)  OP(DO(X), FE_16(OP, DO, __VA_ARGS__))
#define FE_18(OP, DO, X, ...)  OP(DO(X), FE_17(OP, DO, __VA_ARGS__))
#define FE_19(OP, DO, X, ...)  OP(DO(X), FE_18(OP, DO, __VA_ARGS__))
#define FE_20(OP, DO, X, ...)  OP(DO(X), FE_19(OP, DO, __VA_ARGS__))
#define FE_21(OP, DO, X, ...)  OP(DO(X), FE_20(OP, DO, __VA_ARGS__))
#define FE_22(OP, DO, X, ...)  OP(DO(X), FE_21(OP, DO, __VA_ARGS__))
#define FE_23(OP, DO, X, ...)  OP(DO(X), FE_22(OP, DO, __VA_ARGS__))
#define FE_24(OP, DO, X, ...)  OP(DO(X), FE_23(OP, DO, __VA_ARGS__))
#define FE_25(OP, DO, X, ...)  OP(DO(X), FE_24(OP, DO, __VA_ARGS__))
#define FE_26(OP, DO, X, ...)  OP(DO(X), FE_25(OP, DO, __VA_ARGS__))
#define FE_27(OP, DO, X, ...)  OP(DO(X), FE_26(OP, DO, __VA_ARGS__))
#define FE_28(OP, DO, X, ...)  OP(DO(X), FE_27(OP, DO, __VA_ARGS__))
#define FE_29(OP, DO, X, ...)  OP(DO(X), FE_28(OP, DO, __VA_ARGS__))
#define FE_30(OP, DO, X, ...)  OP(DO(X), FE_29(OP, DO, __VA_ARGS__))
#define FE_31(OP, DO, X, ...)  OP(DO(X), FE_30(OP, DO, __VA_ARGS__))
#define FE_32(OP, DO, X, ...)  OP(DO(X), FE_31(OP, DO, __VA_ARGS__))
#define FE_33(OP, DO, X, ...)  OP(DO(X), FE_32(OP, DO, __VA_ARGS__))
#define FE_34(OP, DO, X, ...)  OP(DO(X), FE_33(OP, DO, __VA_ARGS__))
#define FE_35(OP, DO, X, ...)  OP(DO(X), FE_34(OP, DO, __VA_ARGS__))
#define FE_36(OP, DO, X, ...)  OP(DO(X), FE_35(OP, DO, __VA_ARGS__))
#define FE_37(OP, DO, X, ...)  OP(DO(X), FE_36(OP, DO, __VA_ARGS__))
#define FE_38(OP, DO, X, ...)  OP(DO(X), FE_37(OP, DO, __VA_ARGS__))
#define FE_39(OP, DO, X, ...)  OP(DO(X), FE_38(OP, DO, __VA_ARGS__))
#define FE_40(OP, DO, X, ...)  OP(DO(X), FE_39(OP, DO, __VA_ARGS__))
#define FE_41(OP, DO, X, ...)  OP(DO(X), FE_40(OP, DO, __VA_ARGS__))
#define FE_42(OP, DO, X, ...)  OP(DO(X), FE_41(OP, DO, __VA_ARGS__))
#define FE_43(OP, DO, X, ...)  OP(DO(X), FE_42(OP, DO, __VA_ARGS__))
#define FE_44(OP, DO, X, ...)  OP(DO(X), FE_43(OP, DO, __VA_ARGS__))
#define FE_45(OP, DO, X, ...)  OP(DO(X), FE_44(OP, DO, __VA_ARGS__))
#define FE_46(OP, DO, X, ...)  OP(DO(X), FE_45(OP, DO, __VA_ARGS__))
#define FE_47(OP, DO, X, ...)  OP(DO(X), FE_46(OP, DO, __VA_ARGS__))
#define FE_48(OP, DO, X, ...)  OP(DO(X), FE_47(OP, DO, __VA_ARGS__))
#define FE_49(OP, DO, X, ...)  OP(DO(X), FE_48(OP, DO, __VA_ARGS__))
#define FE_50(OP, DO, X, ...)  OP(DO(X), FE_49(OP, DO, __VA_ARGS__))
#define FE_51(OP, DO, X, ...)  OP(DO(X), FE_50(OP, DO, __VA_ARGS__))
#define FE_52(OP, DO, X, ...)  OP(DO(X), FE_51(OP, DO, __VA_ARGS__))
#define FE_53(OP, DO, X, ...)  OP(DO(X), FE_52(OP, DO, __VA_ARGS__))
#define FE_54(OP, DO, X, ...)  OP(DO(X), FE_53(OP, DO, __VA_ARGS__))
#define FE_55(OP, DO, X, ...)  OP(DO(X), FE_54(OP, DO, __VA_ARGS__))
#define FE_56(OP, DO, X, ...)  OP(DO(X), FE_55(OP, DO, __VA_ARGS__))
#define FE_57(OP, DO, X, ...)  OP(DO(X), FE_56(OP, DO, __VA_ARGS__))
#define FE_58(OP, DO, X, ...)  OP(DO(X), FE_57(OP, DO, __VA_ARGS__))
#define FE_59(OP, DO, X, ...)  OP(DO(X), FE_58(OP, DO, __VA_ARGS__))
#define FE_60(OP, DO, X, ...)  OP(DO(X), FE_59(OP, DO, __VA_ARGS__))
#define FE_61(OP, DO, X, ...)  OP(DO(X), FE_60(OP, DO, __VA_ARGS__))
#define FE_62(OP, DO, X, ...)  OP(DO(X), FE_61(OP, DO, __VA_ARGS__))
#define FE_63(OP, DO, X, ...)  OP(DO(X), FE_62(OP, DO, __VA_ARGS__))
#define FE_64(OP, DO, X, ...)  OP(DO(X), FE_63(OP, DO, __VA_ARGS__))
#define FE_65(OP, DO, X, ...)  OP(DO(X), FE_64(OP, DO, __VA_ARGS__))
#define FE_66(OP, DO, X, ...)  OP(DO(X), FE_65(OP, DO, __VA_ARGS__))
#define FE_67(OP, DO, X, ...)  OP(DO(X), FE_66(OP, DO, __VA_ARGS__))
#define FE_68(OP, DO, X, ...)  OP(DO(X), FE_67(OP, DO, __VA_ARGS__))
#define FE_69(OP, DO, X, ...)  OP(DO(X), FE_68(OP, DO, __VA_ARGS__))
#define FE_70(OP, DO, X, ...)  OP(DO(X), FE_69(OP, DO, __VA_ARGS__))
#define FE_71(OP, DO, X, ...)  OP(DO(X), FE_70(OP, DO, __VA_ARGS__))
#define FE_72(OP, DO, X, ...)  OP(DO(X), FE_71(OP, DO, __VA_ARGS__))
#define FE_73(OP, DO, X, ...)  OP(DO(X), FE_72(OP, DO, __VA_ARGS__))
#define FE_74(OP, DO, X, ...)  OP(DO(X), FE_73(OP, DO, __VA_ARGS__))
#define FE_75(OP, DO, X, ...)  OP(DO(X), FE_74(OP, DO, __VA_ARGS__))
#define FE_76(OP, DO, X, ...)  OP(DO(X), FE_75(OP, DO, __VA_ARGS__))
#define FE_77(OP, DO, X, ...)  OP(DO(X), FE_76(OP, DO, __VA_ARGS__))
#define FE_78(OP, DO, X, ...)  OP(DO(X), FE_77(OP, DO, __VA_ARGS__))
#define FE_79(OP, DO, X, ...)  OP(DO(X), FE_78(OP, DO, __VA_ARGS__))
#define FE_80(OP, DO, X, ...)  OP(DO(X), FE_79(OP, DO, __VA_ARGS__))
#define FE_81(OP, DO, X, ...)  OP(DO(X), FE_80(OP, DO, __VA_ARGS__))
#define FE_82(OP, DO, X, ...)  OP(DO(X), FE_81(OP, DO, __VA_ARGS__))
#define FE_83(OP, DO, X, ...)  OP(DO(X), FE_82(OP, DO, __VA_ARGS__))
#define FE_84(OP, DO, X, ...)  OP(DO(X), FE_83(OP, DO, __VA_ARGS__))
#define FE_85(OP, DO, X, ...)  OP(DO(X), FE_84(OP, DO, __VA_ARGS__))
#define FE_86(OP, DO, X, ...)  OP(DO(X), FE_85(OP, DO, __VA_ARGS__))
#define FE_87(OP, DO, X, ...)  OP(DO(X), FE_86(OP, DO, __VA_ARGS__))
#define FE_88(OP, DO, X, ...)  OP(DO(X), FE_87(OP, DO, __VA_ARGS__))
#define FE_89(OP, DO, X, ...)  OP(DO(X), FE_88(OP, DO, __VA_ARGS__))
#define FE_90(OP, DO, X, ...)  OP(DO(X), FE_89(OP, DO, __VA_ARGS__))
#define FE_91(OP, DO, X, ...)  OP(DO(X), FE_90(OP, DO, __VA_ARGS__))
#define FE_92(OP, DO, X, ...)  OP(DO(X), FE_91(OP, DO, __VA_ARGS__))
#define FE_93(OP, DO, X, ...)  OP(DO(X), FE_92(OP, DO, __VA_ARGS__))
#define FE_94(OP, DO, X, ...)  OP(DO(X), FE_93(OP, DO, __VA_ARGS__))
#define FE_95(OP, DO, X, ...)  OP(DO(X), FE_94(OP, DO, __VA_ARGS__))
#define FE_96(OP, DO, X, ...)  OP(DO(X), FE_95(OP, DO, __VA_ARGS__))
#define FE_97(OP, DO, X, ...)  OP(DO(X), FE_96(OP, DO, __VA_ARGS__))
#define FE_98(OP, DO, X, ...)  OP(DO(X), FE_97(OP, DO, __VA_ARGS__))
#define FE_99(OP, DO, X, ...)  OP(DO(X), FE_98(OP, DO, __VA_ARGS__))
#define FE_100(OP, DO, X, ...) OP(DO(X), FE_99(OP, DO, __VA_ARGS__))

#define FOR_EACH(OP,NAME,...) \
	APPLY( CONCAT( FE_, N_ARG(__VA_ARGS__)), OP, NAME, __VA_ARGS__)

#define FOLD(OP,...) \
	FOR_EACH( OP, EXPAND, __VA_ARGS__)
#endif//aw_meta_pp_for_each_h
