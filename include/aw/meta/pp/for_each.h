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

#define FE_1(DO, X, ...) EXPAND(DO(X))
#define FE_2(DO, X, ...) EXPAND(DO(X)FE_1(DO, __VA_ARGS__))
#define FE_3(DO, X, ...) EXPAND(DO(X)FE_2(DO, __VA_ARGS__))
#define FE_4(DO, X, ...) EXPAND(DO(X)FE_3(DO, __VA_ARGS__))
#define FE_5(DO, X, ...) EXPAND(DO(X)FE_4(DO, __VA_ARGS__))
#define FE_6(DO, X, ...) EXPAND(DO(X)FE_5(DO, __VA_ARGS__))
#define FE_7(DO, X, ...) EXPAND(DO(X)FE_6(DO, __VA_ARGS__))
#define FE_8(DO, X, ...) EXPAND(DO(X)FE_7(DO, __VA_ARGS__))
#define FE_9(DO, X, ...) EXPAND(DO(X)FE_8(DO, __VA_ARGS__))
#define FE_10(DO, X, ...) EXPAND(DO(X)FE_9(DO, __VA_ARGS__))
#define FE_11(DO, X, ...) EXPAND(DO(X)FE_10(DO, __VA_ARGS__))
#define FE_12(DO, X, ...) EXPAND(DO(X)FE_11(DO, __VA_ARGS__))
#define FE_13(DO, X, ...) EXPAND(DO(X)FE_12(DO, __VA_ARGS__))
#define FE_14(DO, X, ...) EXPAND(DO(X)FE_13(DO, __VA_ARGS__))
#define FE_15(DO, X, ...) EXPAND(DO(X)FE_14(DO, __VA_ARGS__))
#define FE_16(DO, X, ...) EXPAND(DO(X)FE_15(DO, __VA_ARGS__))
#define FE_17(DO, X, ...) EXPAND(DO(X)FE_16(DO, __VA_ARGS__))
#define FE_18(DO, X, ...) EXPAND(DO(X)FE_17(DO, __VA_ARGS__))
#define FE_19(DO, X, ...) EXPAND(DO(X)FE_18(DO, __VA_ARGS__))
#define FE_20(DO, X, ...) EXPAND(DO(X)FE_19(DO, __VA_ARGS__))
#define FE_21(DO, X, ...) EXPAND(DO(X)FE_20(DO, __VA_ARGS__))
#define FE_22(DO, X, ...) EXPAND(DO(X)FE_21(DO, __VA_ARGS__))
#define FE_23(DO, X, ...) EXPAND(DO(X)FE_22(DO, __VA_ARGS__))
#define FE_24(DO, X, ...) EXPAND(DO(X)FE_23(DO, __VA_ARGS__))
#define FE_25(DO, X, ...) EXPAND(DO(X)FE_24(DO, __VA_ARGS__))
#define FE_26(DO, X, ...) EXPAND(DO(X)FE_25(DO, __VA_ARGS__))
#define FE_27(DO, X, ...) EXPAND(DO(X)FE_26(DO, __VA_ARGS__))
#define FE_28(DO, X, ...) EXPAND(DO(X)FE_27(DO, __VA_ARGS__))
#define FE_29(DO, X, ...) EXPAND(DO(X)FE_28(DO, __VA_ARGS__))
#define FE_30(DO, X, ...) EXPAND(DO(X)FE_29(DO, __VA_ARGS__))
#define FE_31(DO, X, ...) EXPAND(DO(X)FE_30(DO, __VA_ARGS__))
#define FE_32(DO, X, ...) EXPAND(DO(X)FE_31(DO, __VA_ARGS__))
#define FE_33(DO, X, ...) EXPAND(DO(X)FE_32(DO, __VA_ARGS__))
#define FE_34(DO, X, ...) EXPAND(DO(X)FE_33(DO, __VA_ARGS__))
#define FE_35(DO, X, ...) EXPAND(DO(X)FE_34(DO, __VA_ARGS__))
#define FE_36(DO, X, ...) EXPAND(DO(X)FE_35(DO, __VA_ARGS__))
#define FE_37(DO, X, ...) EXPAND(DO(X)FE_36(DO, __VA_ARGS__))
#define FE_38(DO, X, ...) EXPAND(DO(X)FE_37(DO, __VA_ARGS__))
#define FE_39(DO, X, ...) EXPAND(DO(X)FE_38(DO, __VA_ARGS__))
#define FE_40(DO, X, ...) EXPAND(DO(X)FE_39(DO, __VA_ARGS__))
#define FE_41(DO, X, ...) EXPAND(DO(X)FE_40(DO, __VA_ARGS__))
#define FE_42(DO, X, ...) EXPAND(DO(X)FE_41(DO, __VA_ARGS__))
#define FE_43(DO, X, ...) EXPAND(DO(X)FE_42(DO, __VA_ARGS__))
#define FE_44(DO, X, ...) EXPAND(DO(X)FE_43(DO, __VA_ARGS__))
#define FE_45(DO, X, ...) EXPAND(DO(X)FE_44(DO, __VA_ARGS__))
#define FE_46(DO, X, ...) EXPAND(DO(X)FE_45(DO, __VA_ARGS__))
#define FE_47(DO, X, ...) EXPAND(DO(X)FE_46(DO, __VA_ARGS__))
#define FE_48(DO, X, ...) EXPAND(DO(X)FE_47(DO, __VA_ARGS__))
#define FE_49(DO, X, ...) EXPAND(DO(X)FE_48(DO, __VA_ARGS__))
#define FE_50(DO, X, ...) EXPAND(DO(X)FE_49(DO, __VA_ARGS__))
#define FE_51(DO, X, ...) EXPAND(DO(X)FE_50(DO, __VA_ARGS__))
#define FE_52(DO, X, ...) EXPAND(DO(X)FE_51(DO, __VA_ARGS__))
#define FE_53(DO, X, ...) EXPAND(DO(X)FE_52(DO, __VA_ARGS__))
#define FE_54(DO, X, ...) EXPAND(DO(X)FE_53(DO, __VA_ARGS__))
#define FE_55(DO, X, ...) EXPAND(DO(X)FE_54(DO, __VA_ARGS__))
#define FE_56(DO, X, ...) EXPAND(DO(X)FE_55(DO, __VA_ARGS__))
#define FE_57(DO, X, ...) EXPAND(DO(X)FE_56(DO, __VA_ARGS__))
#define FE_58(DO, X, ...) EXPAND(DO(X)FE_57(DO, __VA_ARGS__))
#define FE_59(DO, X, ...) EXPAND(DO(X)FE_58(DO, __VA_ARGS__))
#define FE_60(DO, X, ...) EXPAND(DO(X)FE_59(DO, __VA_ARGS__))
#define FE_61(DO, X, ...) EXPAND(DO(X)FE_60(DO, __VA_ARGS__))
#define FE_62(DO, X, ...) EXPAND(DO(X)FE_61(DO, __VA_ARGS__))
#define FE_63(DO, X, ...) EXPAND(DO(X)FE_62(DO, __VA_ARGS__))
#define FE_64(DO, X, ...) EXPAND(DO(X)FE_63(DO, __VA_ARGS__))
#define FE_65(DO, X, ...) EXPAND(DO(X)FE_64(DO, __VA_ARGS__))
#define FE_66(DO, X, ...) EXPAND(DO(X)FE_65(DO, __VA_ARGS__))
#define FE_67(DO, X, ...) EXPAND(DO(X)FE_66(DO, __VA_ARGS__))
#define FE_68(DO, X, ...) EXPAND(DO(X)FE_67(DO, __VA_ARGS__))
#define FE_69(DO, X, ...) EXPAND(DO(X)FE_68(DO, __VA_ARGS__))
#define FE_70(DO, X, ...) EXPAND(DO(X)FE_69(DO, __VA_ARGS__))
#define FE_71(DO, X, ...) EXPAND(DO(X)FE_70(DO, __VA_ARGS__))
#define FE_72(DO, X, ...) EXPAND(DO(X)FE_71(DO, __VA_ARGS__))
#define FE_73(DO, X, ...) EXPAND(DO(X)FE_72(DO, __VA_ARGS__))
#define FE_74(DO, X, ...) EXPAND(DO(X)FE_73(DO, __VA_ARGS__))
#define FE_75(DO, X, ...) EXPAND(DO(X)FE_74(DO, __VA_ARGS__))
#define FE_76(DO, X, ...) EXPAND(DO(X)FE_75(DO, __VA_ARGS__))
#define FE_77(DO, X, ...) EXPAND(DO(X)FE_76(DO, __VA_ARGS__))
#define FE_78(DO, X, ...) EXPAND(DO(X)FE_77(DO, __VA_ARGS__))
#define FE_79(DO, X, ...) EXPAND(DO(X)FE_78(DO, __VA_ARGS__))
#define FE_80(DO, X, ...) EXPAND(DO(X)FE_79(DO, __VA_ARGS__))
#define FE_81(DO, X, ...) EXPAND(DO(X)FE_80(DO, __VA_ARGS__))
#define FE_82(DO, X, ...) EXPAND(DO(X)FE_81(DO, __VA_ARGS__))
#define FE_83(DO, X, ...) EXPAND(DO(X)FE_82(DO, __VA_ARGS__))
#define FE_84(DO, X, ...) EXPAND(DO(X)FE_83(DO, __VA_ARGS__))
#define FE_85(DO, X, ...) EXPAND(DO(X)FE_84(DO, __VA_ARGS__))
#define FE_86(DO, X, ...) EXPAND(DO(X)FE_85(DO, __VA_ARGS__))
#define FE_87(DO, X, ...) EXPAND(DO(X)FE_86(DO, __VA_ARGS__))
#define FE_88(DO, X, ...) EXPAND(DO(X)FE_87(DO, __VA_ARGS__))
#define FE_89(DO, X, ...) EXPAND(DO(X)FE_88(DO, __VA_ARGS__))
#define FE_90(DO, X, ...) EXPAND(DO(X)FE_89(DO, __VA_ARGS__))
#define FE_91(DO, X, ...) EXPAND(DO(X)FE_90(DO, __VA_ARGS__))
#define FE_92(DO, X, ...) EXPAND(DO(X)FE_91(DO, __VA_ARGS__))
#define FE_93(DO, X, ...) EXPAND(DO(X)FE_92(DO, __VA_ARGS__))
#define FE_94(DO, X, ...) EXPAND(DO(X)FE_93(DO, __VA_ARGS__))
#define FE_95(DO, X, ...) EXPAND(DO(X)FE_94(DO, __VA_ARGS__))
#define FE_96(DO, X, ...) EXPAND(DO(X)FE_95(DO, __VA_ARGS__))
#define FE_97(DO, X, ...) EXPAND(DO(X)FE_96(DO, __VA_ARGS__))
#define FE_98(DO, X, ...) EXPAND(DO(X)FE_97(DO, __VA_ARGS__))
#define FE_99(DO, X, ...) EXPAND(DO(X)FE_98(DO, __VA_ARGS__))
#define FE_100(DO, X, ...) EXPAND(DO(X)FE_99(DO, __VA_ARGS__))

/*!
 * Apply macro NAME to each argument
 */
#define FOR_EACH(NAME,...) \
	APPLY( CONCAT( FE_, N_ARG(__VA_ARGS__)), NAME, __VA_ARGS__)
	
#endif//aw_meta_pp_for_each_h
