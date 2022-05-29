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
 * Reverses the order of arguments
 */
#define REVERSE( ... ) APPLY_N(REVERSE_, __VA_ARGS__)

#define REVERSE_0( ... )
#define REVERSE_1( ... )    __VA_ARGS__
#define REVERSE_2( X, ... ) __VA_ARGS__, X
#define REVERSE_3( X, ... ) REVERSE_2(__VA_ARGS__), X
#define REVERSE_4( X, ... ) REVERSE_3(__VA_ARGS__), X
#define REVERSE_5( X, ... ) REVERSE_4(__VA_ARGS__), X
#define REVERSE_6( X, ... ) REVERSE_5(__VA_ARGS__), X
#define REVERSE_7( X, ... ) REVERSE_6(__VA_ARGS__), X
#define REVERSE_8( X, ... ) REVERSE_7(__VA_ARGS__), X
#define REVERSE_9( X, ... ) REVERSE_8(__VA_ARGS__), X
#define REVERSE_10( X, ... ) REVERSE_9(__VA_ARGS__), X
#define REVERSE_11( X, ... ) REVERSE_10(__VA_ARGS__), X
#define REVERSE_12( X, ... ) REVERSE_11(__VA_ARGS__), X
#define REVERSE_13( X, ... ) REVERSE_12(__VA_ARGS__), X
#define REVERSE_14( X, ... ) REVERSE_13(__VA_ARGS__), X
#define REVERSE_15( X, ... ) REVERSE_14(__VA_ARGS__), X
#define REVERSE_16( X, ... ) REVERSE_15(__VA_ARGS__), X
#define REVERSE_17( X, ... ) REVERSE_16(__VA_ARGS__), X
#define REVERSE_18( X, ... ) REVERSE_17(__VA_ARGS__), X
#define REVERSE_19( X, ... ) REVERSE_18(__VA_ARGS__), X
#define REVERSE_20( X, ... ) REVERSE_19(__VA_ARGS__), X
#define REVERSE_21( X, ... ) REVERSE_20(__VA_ARGS__), X
#define REVERSE_22( X, ... ) REVERSE_21(__VA_ARGS__), X
#define REVERSE_23( X, ... ) REVERSE_22(__VA_ARGS__), X
#define REVERSE_24( X, ... ) REVERSE_23(__VA_ARGS__), X
#define REVERSE_25( X, ... ) REVERSE_24(__VA_ARGS__), X
#define REVERSE_26( X, ... ) REVERSE_25(__VA_ARGS__), X
#define REVERSE_27( X, ... ) REVERSE_26(__VA_ARGS__), X
#define REVERSE_28( X, ... ) REVERSE_27(__VA_ARGS__), X
#define REVERSE_29( X, ... ) REVERSE_28(__VA_ARGS__), X
#define REVERSE_30( X, ... ) REVERSE_29(__VA_ARGS__), X
#define REVERSE_31( X, ... ) REVERSE_30(__VA_ARGS__), X
#define REVERSE_32( X, ... ) REVERSE_31(__VA_ARGS__), X
#define REVERSE_33( X, ... ) REVERSE_32(__VA_ARGS__), X
#define REVERSE_34( X, ... ) REVERSE_33(__VA_ARGS__), X
#define REVERSE_35( X, ... ) REVERSE_34(__VA_ARGS__), X
#define REVERSE_36( X, ... ) REVERSE_35(__VA_ARGS__), X
#define REVERSE_37( X, ... ) REVERSE_36(__VA_ARGS__), X
#define REVERSE_38( X, ... ) REVERSE_37(__VA_ARGS__), X
#define REVERSE_39( X, ... ) REVERSE_38(__VA_ARGS__), X
#define REVERSE_40( X, ... ) REVERSE_39(__VA_ARGS__), X
#define REVERSE_41( X, ... ) REVERSE_40(__VA_ARGS__), X
#define REVERSE_42( X, ... ) REVERSE_41(__VA_ARGS__), X
#define REVERSE_43( X, ... ) REVERSE_42(__VA_ARGS__), X
#define REVERSE_44( X, ... ) REVERSE_43(__VA_ARGS__), X
#define REVERSE_45( X, ... ) REVERSE_44(__VA_ARGS__), X
#define REVERSE_46( X, ... ) REVERSE_45(__VA_ARGS__), X
#define REVERSE_47( X, ... ) REVERSE_46(__VA_ARGS__), X
#define REVERSE_48( X, ... ) REVERSE_47(__VA_ARGS__), X
#define REVERSE_49( X, ... ) REVERSE_48(__VA_ARGS__), X
#define REVERSE_50( X, ... ) REVERSE_49(__VA_ARGS__), X
#define REVERSE_51( X, ... ) REVERSE_50(__VA_ARGS__), X
#define REVERSE_52( X, ... ) REVERSE_51(__VA_ARGS__), X
#define REVERSE_53( X, ... ) REVERSE_52(__VA_ARGS__), X
#define REVERSE_54( X, ... ) REVERSE_53(__VA_ARGS__), X
#define REVERSE_55( X, ... ) REVERSE_54(__VA_ARGS__), X
#define REVERSE_56( X, ... ) REVERSE_55(__VA_ARGS__), X
#define REVERSE_57( X, ... ) REVERSE_56(__VA_ARGS__), X
#define REVERSE_58( X, ... ) REVERSE_57(__VA_ARGS__), X
#define REVERSE_59( X, ... ) REVERSE_58(__VA_ARGS__), X
#define REVERSE_60( X, ... ) REVERSE_59(__VA_ARGS__), X
#define REVERSE_61( X, ... ) REVERSE_60(__VA_ARGS__), X
#define REVERSE_62( X, ... ) REVERSE_61(__VA_ARGS__), X
#define REVERSE_63( X, ... ) REVERSE_62(__VA_ARGS__), X
#define REVERSE_64( X, ... ) REVERSE_63(__VA_ARGS__), X
#define REVERSE_65( X, ... ) REVERSE_64(__VA_ARGS__), X
#define REVERSE_66( X, ... ) REVERSE_65(__VA_ARGS__), X
#define REVERSE_67( X, ... ) REVERSE_66(__VA_ARGS__), X
#define REVERSE_68( X, ... ) REVERSE_67(__VA_ARGS__), X
#define REVERSE_69( X, ... ) REVERSE_68(__VA_ARGS__), X
#define REVERSE_70( X, ... ) REVERSE_69(__VA_ARGS__), X
#define REVERSE_71( X, ... ) REVERSE_70(__VA_ARGS__), X
#define REVERSE_72( X, ... ) REVERSE_71(__VA_ARGS__), X
#define REVERSE_73( X, ... ) REVERSE_72(__VA_ARGS__), X
#define REVERSE_74( X, ... ) REVERSE_73(__VA_ARGS__), X
#define REVERSE_75( X, ... ) REVERSE_74(__VA_ARGS__), X
#define REVERSE_76( X, ... ) REVERSE_75(__VA_ARGS__), X
#define REVERSE_77( X, ... ) REVERSE_76(__VA_ARGS__), X
#define REVERSE_78( X, ... ) REVERSE_77(__VA_ARGS__), X
#define REVERSE_79( X, ... ) REVERSE_78(__VA_ARGS__), X
#define REVERSE_80( X, ... ) REVERSE_79(__VA_ARGS__), X
#define REVERSE_81( X, ... ) REVERSE_80(__VA_ARGS__), X
#define REVERSE_82( X, ... ) REVERSE_81(__VA_ARGS__), X
#define REVERSE_83( X, ... ) REVERSE_82(__VA_ARGS__), X
#define REVERSE_84( X, ... ) REVERSE_83(__VA_ARGS__), X
#define REVERSE_85( X, ... ) REVERSE_84(__VA_ARGS__), X
#define REVERSE_86( X, ... ) REVERSE_85(__VA_ARGS__), X
#define REVERSE_87( X, ... ) REVERSE_86(__VA_ARGS__), X
#define REVERSE_88( X, ... ) REVERSE_87(__VA_ARGS__), X
#define REVERSE_89( X, ... ) REVERSE_88(__VA_ARGS__), X
#define REVERSE_90( X, ... ) REVERSE_89(__VA_ARGS__), X
#define REVERSE_91( X, ... ) REVERSE_90(__VA_ARGS__), X
#define REVERSE_92( X, ... ) REVERSE_91(__VA_ARGS__), X
#define REVERSE_93( X, ... ) REVERSE_92(__VA_ARGS__), X
#define REVERSE_94( X, ... ) REVERSE_93(__VA_ARGS__), X
#define REVERSE_95( X, ... ) REVERSE_94(__VA_ARGS__), X
#define REVERSE_96( X, ... ) REVERSE_95(__VA_ARGS__), X
#define REVERSE_97( X, ... ) REVERSE_96(__VA_ARGS__), X
#define REVERSE_98( X, ... ) REVERSE_97(__VA_ARGS__), X
#define REVERSE_99( X, ... ) REVERSE_98(__VA_ARGS__), X
#define REVERSE_100( X, ... ) REVERSE_99(__VA_ARGS__), X

#endif//aw_meta_pp_reverse_h
