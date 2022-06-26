/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_meta_pp_reverse_h
#define aw_meta_pp_reverse_h
#include "apply_n.h"

/*!
 * \brief Reverses the order of arguments.
 * \note It inserts a space between each argument, so take that into account.
 */
#define AW_REVERSE( ... ) AW_APPLY_N(AW_REVERSE_, __VA_ARGS__)

#define AW_REVERSE_0( ... )
#define AW_REVERSE_1( ... )    __VA_ARGS__
#define AW_REVERSE_2( X, ... ) __VA_ARGS__, X
#define AW_REVERSE_3( X, ... )   AW_REVERSE_2(__VA_ARGS__), X
#define AW_REVERSE_4( X, ... )   AW_REVERSE_3(__VA_ARGS__), X
#define AW_REVERSE_5( X, ... )   AW_REVERSE_4(__VA_ARGS__), X
#define AW_REVERSE_6( X, ... )   AW_REVERSE_5(__VA_ARGS__), X
#define AW_REVERSE_7( X, ... )   AW_REVERSE_6(__VA_ARGS__), X
#define AW_REVERSE_8( X, ... )   AW_REVERSE_7(__VA_ARGS__), X
#define AW_REVERSE_9( X, ... )   AW_REVERSE_8(__VA_ARGS__), X
#define AW_REVERSE_10( X, ... )  AW_REVERSE_9(__VA_ARGS__), X
#define AW_REVERSE_11( X, ... )  AW_REVERSE_10(__VA_ARGS__), X
#define AW_REVERSE_12( X, ... )  AW_REVERSE_11(__VA_ARGS__), X
#define AW_REVERSE_13( X, ... )  AW_REVERSE_12(__VA_ARGS__), X
#define AW_REVERSE_14( X, ... )  AW_REVERSE_13(__VA_ARGS__), X
#define AW_REVERSE_15( X, ... )  AW_REVERSE_14(__VA_ARGS__), X
#define AW_REVERSE_16( X, ... )  AW_REVERSE_15(__VA_ARGS__), X
#define AW_REVERSE_17( X, ... )  AW_REVERSE_16(__VA_ARGS__), X
#define AW_REVERSE_18( X, ... )  AW_REVERSE_17(__VA_ARGS__), X
#define AW_REVERSE_19( X, ... )  AW_REVERSE_18(__VA_ARGS__), X
#define AW_REVERSE_20( X, ... )  AW_REVERSE_19(__VA_ARGS__), X
#define AW_REVERSE_21( X, ... )  AW_REVERSE_20(__VA_ARGS__), X
#define AW_REVERSE_22( X, ... )  AW_REVERSE_21(__VA_ARGS__), X
#define AW_REVERSE_23( X, ... )  AW_REVERSE_22(__VA_ARGS__), X
#define AW_REVERSE_24( X, ... )  AW_REVERSE_23(__VA_ARGS__), X
#define AW_REVERSE_25( X, ... )  AW_REVERSE_24(__VA_ARGS__), X
#define AW_REVERSE_26( X, ... )  AW_REVERSE_25(__VA_ARGS__), X
#define AW_REVERSE_27( X, ... )  AW_REVERSE_26(__VA_ARGS__), X
#define AW_REVERSE_28( X, ... )  AW_REVERSE_27(__VA_ARGS__), X
#define AW_REVERSE_29( X, ... )  AW_REVERSE_28(__VA_ARGS__), X
#define AW_REVERSE_30( X, ... )  AW_REVERSE_29(__VA_ARGS__), X
#define AW_REVERSE_31( X, ... )  AW_REVERSE_30(__VA_ARGS__), X
#define AW_REVERSE_32( X, ... )  AW_REVERSE_31(__VA_ARGS__), X
#define AW_REVERSE_33( X, ... )  AW_REVERSE_32(__VA_ARGS__), X
#define AW_REVERSE_34( X, ... )  AW_REVERSE_33(__VA_ARGS__), X
#define AW_REVERSE_35( X, ... )  AW_REVERSE_34(__VA_ARGS__), X
#define AW_REVERSE_36( X, ... )  AW_REVERSE_35(__VA_ARGS__), X
#define AW_REVERSE_37( X, ... )  AW_REVERSE_36(__VA_ARGS__), X
#define AW_REVERSE_38( X, ... )  AW_REVERSE_37(__VA_ARGS__), X
#define AW_REVERSE_39( X, ... )  AW_REVERSE_38(__VA_ARGS__), X
#define AW_REVERSE_40( X, ... )  AW_REVERSE_39(__VA_ARGS__), X
#define AW_REVERSE_41( X, ... )  AW_REVERSE_40(__VA_ARGS__), X
#define AW_REVERSE_42( X, ... )  AW_REVERSE_41(__VA_ARGS__), X
#define AW_REVERSE_43( X, ... )  AW_REVERSE_42(__VA_ARGS__), X
#define AW_REVERSE_44( X, ... )  AW_REVERSE_43(__VA_ARGS__), X
#define AW_REVERSE_45( X, ... )  AW_REVERSE_44(__VA_ARGS__), X
#define AW_REVERSE_46( X, ... )  AW_REVERSE_45(__VA_ARGS__), X
#define AW_REVERSE_47( X, ... )  AW_REVERSE_46(__VA_ARGS__), X
#define AW_REVERSE_48( X, ... )  AW_REVERSE_47(__VA_ARGS__), X
#define AW_REVERSE_49( X, ... )  AW_REVERSE_48(__VA_ARGS__), X
#define AW_REVERSE_50( X, ... )  AW_REVERSE_49(__VA_ARGS__), X
#define AW_REVERSE_51( X, ... )  AW_REVERSE_50(__VA_ARGS__), X
#define AW_REVERSE_52( X, ... )  AW_REVERSE_51(__VA_ARGS__), X
#define AW_REVERSE_53( X, ... )  AW_REVERSE_52(__VA_ARGS__), X
#define AW_REVERSE_54( X, ... )  AW_REVERSE_53(__VA_ARGS__), X
#define AW_REVERSE_55( X, ... )  AW_REVERSE_54(__VA_ARGS__), X
#define AW_REVERSE_56( X, ... )  AW_REVERSE_55(__VA_ARGS__), X
#define AW_REVERSE_57( X, ... )  AW_REVERSE_56(__VA_ARGS__), X
#define AW_REVERSE_58( X, ... )  AW_REVERSE_57(__VA_ARGS__), X
#define AW_REVERSE_59( X, ... )  AW_REVERSE_58(__VA_ARGS__), X
#define AW_REVERSE_60( X, ... )  AW_REVERSE_59(__VA_ARGS__), X
#define AW_REVERSE_61( X, ... )  AW_REVERSE_60(__VA_ARGS__), X
#define AW_REVERSE_62( X, ... )  AW_REVERSE_61(__VA_ARGS__), X
#define AW_REVERSE_63( X, ... )  AW_REVERSE_62(__VA_ARGS__), X
#define AW_REVERSE_64( X, ... )  AW_REVERSE_63(__VA_ARGS__), X
#define AW_REVERSE_65( X, ... )  AW_REVERSE_64(__VA_ARGS__), X
#define AW_REVERSE_66( X, ... )  AW_REVERSE_65(__VA_ARGS__), X
#define AW_REVERSE_67( X, ... )  AW_REVERSE_66(__VA_ARGS__), X
#define AW_REVERSE_68( X, ... )  AW_REVERSE_67(__VA_ARGS__), X
#define AW_REVERSE_69( X, ... )  AW_REVERSE_68(__VA_ARGS__), X
#define AW_REVERSE_70( X, ... )  AW_REVERSE_69(__VA_ARGS__), X
#define AW_REVERSE_71( X, ... )  AW_REVERSE_70(__VA_ARGS__), X
#define AW_REVERSE_72( X, ... )  AW_REVERSE_71(__VA_ARGS__), X
#define AW_REVERSE_73( X, ... )  AW_REVERSE_72(__VA_ARGS__), X
#define AW_REVERSE_74( X, ... )  AW_REVERSE_73(__VA_ARGS__), X
#define AW_REVERSE_75( X, ... )  AW_REVERSE_74(__VA_ARGS__), X
#define AW_REVERSE_76( X, ... )  AW_REVERSE_75(__VA_ARGS__), X
#define AW_REVERSE_77( X, ... )  AW_REVERSE_76(__VA_ARGS__), X
#define AW_REVERSE_78( X, ... )  AW_REVERSE_77(__VA_ARGS__), X
#define AW_REVERSE_79( X, ... )  AW_REVERSE_78(__VA_ARGS__), X
#define AW_REVERSE_80( X, ... )  AW_REVERSE_79(__VA_ARGS__), X
#define AW_REVERSE_81( X, ... )  AW_REVERSE_80(__VA_ARGS__), X
#define AW_REVERSE_82( X, ... )  AW_REVERSE_81(__VA_ARGS__), X
#define AW_REVERSE_83( X, ... )  AW_REVERSE_82(__VA_ARGS__), X
#define AW_REVERSE_84( X, ... )  AW_REVERSE_83(__VA_ARGS__), X
#define AW_REVERSE_85( X, ... )  AW_REVERSE_84(__VA_ARGS__), X
#define AW_REVERSE_86( X, ... )  AW_REVERSE_85(__VA_ARGS__), X
#define AW_REVERSE_87( X, ... )  AW_REVERSE_86(__VA_ARGS__), X
#define AW_REVERSE_88( X, ... )  AW_REVERSE_87(__VA_ARGS__), X
#define AW_REVERSE_89( X, ... )  AW_REVERSE_88(__VA_ARGS__), X
#define AW_REVERSE_90( X, ... )  AW_REVERSE_89(__VA_ARGS__), X
#define AW_REVERSE_91( X, ... )  AW_REVERSE_90(__VA_ARGS__), X
#define AW_REVERSE_92( X, ... )  AW_REVERSE_91(__VA_ARGS__), X
#define AW_REVERSE_93( X, ... )  AW_REVERSE_92(__VA_ARGS__), X
#define AW_REVERSE_94( X, ... )  AW_REVERSE_93(__VA_ARGS__), X
#define AW_REVERSE_95( X, ... )  AW_REVERSE_94(__VA_ARGS__), X
#define AW_REVERSE_96( X, ... )  AW_REVERSE_95(__VA_ARGS__), X
#define AW_REVERSE_97( X, ... )  AW_REVERSE_96(__VA_ARGS__), X
#define AW_REVERSE_98( X, ... )  AW_REVERSE_97(__VA_ARGS__), X
#define AW_REVERSE_99( X, ... )  AW_REVERSE_98(__VA_ARGS__), X
#define AW_REVERSE_100( X, ... ) AW_REVERSE_99(__VA_ARGS__), X

#endif//aw_meta_pp_reverse_h
