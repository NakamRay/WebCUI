{-# OPTIONS_GHC -w #-}
module Parser where
import Lexer
import DataType
import Unbound.LocallyNameless
import qualified Data.Array as Happy_Data_Array
import qualified Data.Bits as Bits
import Control.Applicative(Applicative(..))
import Control.Monad (ap)

-- parser produced by Happy Version 1.19.11

data HappyAbsSyn t7 t8 t9 t10 t11 t12 t13 t14 t15 t16 t17 t18 t19 t20 t21 t22
	= HappyTerminal (Token)
	| HappyErrorToken Int
	| HappyAbsSyn7 t7
	| HappyAbsSyn8 t8
	| HappyAbsSyn9 t9
	| HappyAbsSyn10 t10
	| HappyAbsSyn11 t11
	| HappyAbsSyn12 t12
	| HappyAbsSyn13 t13
	| HappyAbsSyn14 t14
	| HappyAbsSyn15 t15
	| HappyAbsSyn16 t16
	| HappyAbsSyn17 t17
	| HappyAbsSyn18 t18
	| HappyAbsSyn19 t19
	| HappyAbsSyn20 t20
	| HappyAbsSyn21 t21
	| HappyAbsSyn22 t22

happyExpList :: Happy_Data_Array.Array Int Int
happyExpList = Happy_Data_Array.listArray (0,549) ([0,50240,512,24,0,0,4128,0,0,4096,4,34816,16392,768,0,3140,32800,1,0,0,0,0,33617,57375,0,35200,3073,48,16384,196,6146,0,0,0,8,0,0,2048,0,6280,64,3,0,0,0,0,2048,0,0,20736,2049,96,32768,137,12300,0,17472,512,24,0,0,2048,0,4368,128,6,0,0,0,0,0,0,0,0,0,0,0,128,0,0,0,0,0,0,256,0,0,0,0,0,0,0,0,0,1024,0,0,17408,32269,896,0,0,0,0,0,8,0,32768,49545,28687,0,50240,2016,56,0,0,3072,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,16384,0,0,0,0,0,0,8256,0,544,752,16,0,0,1040,0,2696,1088,3,0,1,0,0,64,0,0,8192,0,0,32768,232,12292,0,0,4096,0,24576,42,3073,0,0,0,0,0,0,512,0,0,0,0,0,0,192,0,32785,32791,0,43136,20417,112,0,16,0,0,32768,0,0,0,2,0,0,256,0,0,17408,32271,896,0,2048,128,0,21248,8067,224,0,0,0,0,0,0,16,0,0,8,0,0,0,0,34816,16408,768,0,3140,32800,1,0,0,0,0,0,0,0,2176,3008,64,16384,196,6146,0,0,0,8,0,128,0,0,136,188,4,17408,24064,768,0,0,0,0,0,0,0,0,0,32,0,0,0,0,8192,34,3073,0,4368,128,6,0,0,0,0,0,0,0,8704,4098,192,0,0,16384,0,0,0,0,0,512,0,0,0,0,0,0,0,2,0,8192,0,0,0,1,0,0,0,0,0,0,0,0,0,16,0,0,2048,0,0,0,272,0,0,16384,1024,0,4096,64,0,0,0,0,1,8704,12032,256,0,0,0,0,0,8194,0,0,0,0,0,544,752,16,4096,30721,2049,0,0,0,0,0,0,0,0,34,47,1,4352,6016,128,0,0,0,0,0,0,0,0,512,0,0,0,0,0,0,0,0,0,1860,32800,1,8704,4098,192,0,0,0,0,0,8,0,0,0,0,0,2048,1,0,0,0,0,0,7816,252,7,17408,8204,384,0,1698,49279,1,0,0,64,32768,392,12292,0,50240,512,24,8192,42,3077,0,0,0,4,34816,16392,768,0,8704,0,0,0,0,0,0,0,0,0,0,4,0,0,0,4096,0,0,0,0,0,0,0,0,0,512,0,2048,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4096,0,0,128,0,0,272,376,8,0,0,512,0,0,0,0,0,0,128,0,0,0,0,0,0,0,0,0,0,0,64,1,0,0,0,0,0
	])

{-# NOINLINE happyExpListPerState #-}
happyExpListPerState st =
    token_strs_expected
  where token_strs = ["error","%dummy","%start_happyParseExp","%start_happyParseTypeContext","%start_happyParseEnv","%start_happyParseTerm","Start","exps","recExps","caseExps","inj","exp","prod","sum","type","typeContext","env","decl","terms","recTerms","caseTerms","term","'('","')'","'['","']'","'{'","'}'","'.'","','","'\955'","'\923'","':'","'->'","'=>'","'+'","'-'","'\8704'","INT","BOOL","UNIT","'case'","'<'","'>'","'='","'of'","'Empty'","'succ'","'pred'","'true'","'false'","NUM","ID","TyID","%eof"]
        bit_start = st * 55
        bit_end = (st + 1) * 55
        read_bit = readArrayBit happyExpList
        bits = map read_bit [bit_start..bit_end - 1]
        bits_indexed = zip bits [0..54]
        token_strs_expected = concatMap f bits_indexed
        f (False, _) = []
        f (True, nr) = [token_strs !! nr]

action_0 (23) = happyShift action_7
action_0 (27) = happyShift action_8
action_0 (31) = happyShift action_9
action_0 (32) = happyShift action_10
action_0 (42) = happyShift action_11
action_0 (52) = happyShift action_12
action_0 (53) = happyShift action_13
action_0 (11) = happyGoto action_5
action_0 (12) = happyGoto action_28
action_0 _ = happyFail (happyExpListPerState 0)

action_1 (47) = happyShift action_26
action_1 (54) = happyShift action_27
action_1 (16) = happyGoto action_25
action_1 _ = happyFail (happyExpListPerState 1)

action_2 (47) = happyShift action_23
action_2 (53) = happyShift action_24
action_2 (17) = happyGoto action_21
action_2 (18) = happyGoto action_22
action_2 _ = happyFail (happyExpListPerState 2)

action_3 (23) = happyShift action_15
action_3 (27) = happyShift action_16
action_3 (31) = happyShift action_17
action_3 (42) = happyShift action_18
action_3 (52) = happyShift action_19
action_3 (53) = happyShift action_20
action_3 (22) = happyGoto action_14
action_3 _ = happyFail (happyExpListPerState 3)

action_4 (23) = happyShift action_7
action_4 (27) = happyShift action_8
action_4 (31) = happyShift action_9
action_4 (32) = happyShift action_10
action_4 (42) = happyShift action_11
action_4 (52) = happyShift action_12
action_4 (53) = happyShift action_13
action_4 (11) = happyGoto action_5
action_4 (12) = happyGoto action_6
action_4 _ = happyFail (happyExpListPerState 4)

action_5 _ = happyReduce_23

action_6 (23) = happyShift action_31
action_6 (27) = happyShift action_32
action_6 (29) = happyShift action_33
action_6 (31) = happyShift action_9
action_6 (32) = happyShift action_10
action_6 (38) = happyShift action_34
action_6 (39) = happyShift action_35
action_6 (40) = happyShift action_36
action_6 (41) = happyShift action_37
action_6 (42) = happyShift action_11
action_6 (43) = happyShift action_38
action_6 (52) = happyShift action_12
action_6 (53) = happyShift action_13
action_6 (54) = happyShift action_39
action_6 (11) = happyGoto action_5
action_6 (12) = happyGoto action_29
action_6 (15) = happyGoto action_30
action_6 _ = happyFail (happyExpListPerState 6)

action_7 (23) = happyShift action_7
action_7 (24) = happyShift action_63
action_7 (27) = happyShift action_8
action_7 (31) = happyShift action_9
action_7 (32) = happyShift action_10
action_7 (42) = happyShift action_11
action_7 (43) = happyShift action_64
action_7 (52) = happyShift action_12
action_7 (53) = happyShift action_13
action_7 (11) = happyGoto action_5
action_7 (12) = happyGoto action_62
action_7 _ = happyFail (happyExpListPerState 7)

action_8 (23) = happyShift action_7
action_8 (27) = happyShift action_8
action_8 (31) = happyShift action_9
action_8 (32) = happyShift action_10
action_8 (42) = happyShift action_11
action_8 (52) = happyShift action_12
action_8 (53) = happyShift action_61
action_8 (8) = happyGoto action_58
action_8 (9) = happyGoto action_59
action_8 (11) = happyGoto action_5
action_8 (12) = happyGoto action_60
action_8 _ = happyFail (happyExpListPerState 8)

action_9 (53) = happyShift action_57
action_9 _ = happyFail (happyExpListPerState 9)

action_10 (54) = happyShift action_56
action_10 _ = happyFail (happyExpListPerState 10)

action_11 (23) = happyShift action_7
action_11 (27) = happyShift action_8
action_11 (31) = happyShift action_9
action_11 (32) = happyShift action_10
action_11 (42) = happyShift action_11
action_11 (52) = happyShift action_12
action_11 (53) = happyShift action_13
action_11 (11) = happyGoto action_5
action_11 (12) = happyGoto action_55
action_11 _ = happyFail (happyExpListPerState 11)

action_12 _ = happyReduce_16

action_13 (33) = happyShift action_54
action_13 _ = happyReduce_15

action_14 (23) = happyShift action_15
action_14 (27) = happyShift action_16
action_14 (29) = happyShift action_53
action_14 (31) = happyShift action_17
action_14 (42) = happyShift action_18
action_14 (52) = happyShift action_19
action_14 (53) = happyShift action_20
action_14 (55) = happyAccept
action_14 (22) = happyGoto action_52
action_14 _ = happyFail (happyExpListPerState 14)

action_15 (23) = happyShift action_15
action_15 (24) = happyShift action_50
action_15 (27) = happyShift action_16
action_15 (31) = happyShift action_17
action_15 (42) = happyShift action_18
action_15 (43) = happyShift action_51
action_15 (52) = happyShift action_19
action_15 (53) = happyShift action_20
action_15 (22) = happyGoto action_49
action_15 _ = happyFail (happyExpListPerState 15)

action_16 (23) = happyShift action_15
action_16 (27) = happyShift action_16
action_16 (31) = happyShift action_17
action_16 (42) = happyShift action_18
action_16 (52) = happyShift action_19
action_16 (53) = happyShift action_48
action_16 (19) = happyGoto action_45
action_16 (20) = happyGoto action_46
action_16 (22) = happyGoto action_47
action_16 _ = happyFail (happyExpListPerState 16)

action_17 (53) = happyShift action_44
action_17 _ = happyFail (happyExpListPerState 17)

action_18 (23) = happyShift action_15
action_18 (27) = happyShift action_16
action_18 (31) = happyShift action_17
action_18 (42) = happyShift action_18
action_18 (52) = happyShift action_19
action_18 (53) = happyShift action_20
action_18 (22) = happyGoto action_43
action_18 _ = happyFail (happyExpListPerState 18)

action_19 _ = happyReduce_57

action_20 _ = happyReduce_56

action_21 (55) = happyAccept
action_21 _ = happyFail (happyExpListPerState 21)

action_22 (30) = happyShift action_42
action_22 _ = happyReduce_44

action_23 _ = happyReduce_46

action_24 (33) = happyShift action_41
action_24 _ = happyFail (happyExpListPerState 24)

action_25 (55) = happyAccept
action_25 _ = happyFail (happyExpListPerState 25)

action_26 _ = happyReduce_43

action_27 (30) = happyShift action_40
action_27 _ = happyReduce_41

action_28 (23) = happyShift action_31
action_28 (27) = happyShift action_32
action_28 (29) = happyShift action_33
action_28 (31) = happyShift action_9
action_28 (32) = happyShift action_10
action_28 (38) = happyShift action_34
action_28 (39) = happyShift action_35
action_28 (40) = happyShift action_36
action_28 (41) = happyShift action_37
action_28 (42) = happyShift action_11
action_28 (43) = happyShift action_38
action_28 (52) = happyShift action_12
action_28 (53) = happyShift action_13
action_28 (54) = happyShift action_39
action_28 (55) = happyAccept
action_28 (11) = happyGoto action_5
action_28 (12) = happyGoto action_29
action_28 (15) = happyGoto action_30
action_28 _ = happyFail (happyExpListPerState 28)

action_29 (29) = happyShift action_33
action_29 (38) = happyShift action_34
action_29 (39) = happyShift action_35
action_29 (40) = happyShift action_36
action_29 (41) = happyShift action_37
action_29 (43) = happyShift action_38
action_29 (54) = happyShift action_39
action_29 (11) = happyGoto action_5
action_29 (12) = happyGoto action_29
action_29 (15) = happyGoto action_30
action_29 _ = happyReduce_20

action_30 (34) = happyShift action_101
action_30 _ = happyReduce_26

action_31 (23) = happyShift action_31
action_31 (24) = happyShift action_63
action_31 (27) = happyShift action_32
action_31 (31) = happyShift action_9
action_31 (32) = happyShift action_10
action_31 (38) = happyShift action_34
action_31 (39) = happyShift action_35
action_31 (40) = happyShift action_36
action_31 (41) = happyShift action_37
action_31 (42) = happyShift action_11
action_31 (43) = happyShift action_100
action_31 (52) = happyShift action_12
action_31 (53) = happyShift action_13
action_31 (54) = happyShift action_39
action_31 (11) = happyGoto action_5
action_31 (12) = happyGoto action_62
action_31 (15) = happyGoto action_99
action_31 _ = happyFail (happyExpListPerState 31)

action_32 (23) = happyShift action_31
action_32 (27) = happyShift action_32
action_32 (31) = happyShift action_9
action_32 (32) = happyShift action_10
action_32 (38) = happyShift action_34
action_32 (39) = happyShift action_35
action_32 (40) = happyShift action_36
action_32 (41) = happyShift action_37
action_32 (42) = happyShift action_11
action_32 (43) = happyShift action_38
action_32 (52) = happyShift action_12
action_32 (53) = happyShift action_98
action_32 (54) = happyShift action_39
action_32 (8) = happyGoto action_58
action_32 (9) = happyGoto action_59
action_32 (11) = happyGoto action_5
action_32 (12) = happyGoto action_60
action_32 (13) = happyGoto action_95
action_32 (14) = happyGoto action_96
action_32 (15) = happyGoto action_97
action_32 _ = happyFail (happyExpListPerState 32)

action_33 (52) = happyShift action_93
action_33 (53) = happyShift action_94
action_33 _ = happyFail (happyExpListPerState 33)

action_34 (54) = happyShift action_92
action_34 _ = happyFail (happyExpListPerState 34)

action_35 _ = happyReduce_32

action_36 _ = happyReduce_33

action_37 _ = happyReduce_40

action_38 (53) = happyShift action_91
action_38 (14) = happyGoto action_90
action_38 _ = happyFail (happyExpListPerState 38)

action_39 _ = happyReduce_34

action_40 (47) = happyShift action_26
action_40 (54) = happyShift action_27
action_40 (16) = happyGoto action_89
action_40 _ = happyFail (happyExpListPerState 40)

action_41 (23) = happyShift action_75
action_41 (27) = happyShift action_76
action_41 (38) = happyShift action_34
action_41 (39) = happyShift action_35
action_41 (40) = happyShift action_36
action_41 (41) = happyShift action_37
action_41 (43) = happyShift action_38
action_41 (54) = happyShift action_39
action_41 (15) = happyGoto action_88
action_41 _ = happyFail (happyExpListPerState 41)

action_42 (47) = happyShift action_23
action_42 (53) = happyShift action_24
action_42 (17) = happyGoto action_87
action_42 (18) = happyGoto action_22
action_42 _ = happyFail (happyExpListPerState 42)

action_43 (23) = happyShift action_15
action_43 (27) = happyShift action_16
action_43 (29) = happyShift action_53
action_43 (31) = happyShift action_17
action_43 (42) = happyShift action_18
action_43 (46) = happyShift action_86
action_43 (52) = happyShift action_19
action_43 (53) = happyShift action_20
action_43 (22) = happyGoto action_52
action_43 _ = happyFail (happyExpListPerState 43)

action_44 (29) = happyShift action_85
action_44 _ = happyFail (happyExpListPerState 44)

action_45 (28) = happyShift action_84
action_45 _ = happyFail (happyExpListPerState 45)

action_46 (28) = happyShift action_83
action_46 _ = happyFail (happyExpListPerState 46)

action_47 (23) = happyShift action_15
action_47 (27) = happyShift action_16
action_47 (29) = happyShift action_53
action_47 (30) = happyShift action_82
action_47 (31) = happyShift action_17
action_47 (42) = happyShift action_18
action_47 (52) = happyShift action_19
action_47 (53) = happyShift action_20
action_47 (22) = happyGoto action_52
action_47 _ = happyReduce_48

action_48 (45) = happyShift action_81
action_48 _ = happyReduce_56

action_49 (23) = happyShift action_15
action_49 (24) = happyShift action_80
action_49 (27) = happyShift action_16
action_49 (29) = happyShift action_53
action_49 (31) = happyShift action_17
action_49 (42) = happyShift action_18
action_49 (52) = happyShift action_19
action_49 (53) = happyShift action_20
action_49 (22) = happyGoto action_52
action_49 _ = happyFail (happyExpListPerState 49)

action_50 _ = happyReduce_54

action_51 (53) = happyShift action_79
action_51 _ = happyFail (happyExpListPerState 51)

action_52 (29) = happyShift action_53
action_52 (22) = happyGoto action_52
action_52 _ = happyReduce_61

action_53 (52) = happyShift action_77
action_53 (53) = happyShift action_78
action_53 _ = happyFail (happyExpListPerState 53)

action_54 (23) = happyShift action_75
action_54 (27) = happyShift action_76
action_54 (38) = happyShift action_34
action_54 (39) = happyShift action_35
action_54 (40) = happyShift action_36
action_54 (41) = happyShift action_37
action_54 (43) = happyShift action_38
action_54 (54) = happyShift action_39
action_54 (15) = happyGoto action_74
action_54 _ = happyFail (happyExpListPerState 54)

action_55 (23) = happyShift action_31
action_55 (27) = happyShift action_32
action_55 (29) = happyShift action_33
action_55 (31) = happyShift action_9
action_55 (32) = happyShift action_10
action_55 (38) = happyShift action_34
action_55 (39) = happyShift action_35
action_55 (40) = happyShift action_36
action_55 (41) = happyShift action_37
action_55 (42) = happyShift action_11
action_55 (43) = happyShift action_38
action_55 (46) = happyShift action_73
action_55 (52) = happyShift action_12
action_55 (53) = happyShift action_13
action_55 (54) = happyShift action_39
action_55 (11) = happyGoto action_5
action_55 (12) = happyGoto action_29
action_55 (15) = happyGoto action_30
action_55 _ = happyFail (happyExpListPerState 55)

action_56 (29) = happyShift action_72
action_56 _ = happyFail (happyExpListPerState 56)

action_57 (33) = happyShift action_71
action_57 _ = happyFail (happyExpListPerState 57)

action_58 (28) = happyShift action_70
action_58 _ = happyFail (happyExpListPerState 58)

action_59 (28) = happyShift action_69
action_59 _ = happyFail (happyExpListPerState 59)

action_60 (23) = happyShift action_31
action_60 (27) = happyShift action_32
action_60 (29) = happyShift action_33
action_60 (30) = happyShift action_68
action_60 (31) = happyShift action_9
action_60 (32) = happyShift action_10
action_60 (38) = happyShift action_34
action_60 (39) = happyShift action_35
action_60 (40) = happyShift action_36
action_60 (41) = happyShift action_37
action_60 (42) = happyShift action_11
action_60 (43) = happyShift action_38
action_60 (52) = happyShift action_12
action_60 (53) = happyShift action_13
action_60 (54) = happyShift action_39
action_60 (11) = happyGoto action_5
action_60 (12) = happyGoto action_29
action_60 (15) = happyGoto action_30
action_60 _ = happyReduce_5

action_61 (33) = happyShift action_54
action_61 (45) = happyShift action_67
action_61 _ = happyReduce_15

action_62 (23) = happyShift action_31
action_62 (24) = happyShift action_66
action_62 (27) = happyShift action_32
action_62 (29) = happyShift action_33
action_62 (31) = happyShift action_9
action_62 (32) = happyShift action_10
action_62 (38) = happyShift action_34
action_62 (39) = happyShift action_35
action_62 (40) = happyShift action_36
action_62 (41) = happyShift action_37
action_62 (42) = happyShift action_11
action_62 (43) = happyShift action_38
action_62 (52) = happyShift action_12
action_62 (53) = happyShift action_13
action_62 (54) = happyShift action_39
action_62 (11) = happyGoto action_5
action_62 (12) = happyGoto action_29
action_62 (15) = happyGoto action_30
action_62 _ = happyFail (happyExpListPerState 62)

action_63 _ = happyReduce_12

action_64 (53) = happyShift action_65
action_64 _ = happyFail (happyExpListPerState 64)

action_65 (45) = happyShift action_124
action_65 _ = happyFail (happyExpListPerState 65)

action_66 _ = happyReduce_13

action_67 (23) = happyShift action_7
action_67 (27) = happyShift action_8
action_67 (31) = happyShift action_9
action_67 (32) = happyShift action_10
action_67 (42) = happyShift action_11
action_67 (52) = happyShift action_12
action_67 (53) = happyShift action_13
action_67 (11) = happyGoto action_5
action_67 (12) = happyGoto action_123
action_67 _ = happyFail (happyExpListPerState 67)

action_68 (23) = happyShift action_7
action_68 (27) = happyShift action_8
action_68 (31) = happyShift action_9
action_68 (32) = happyShift action_10
action_68 (42) = happyShift action_11
action_68 (52) = happyShift action_12
action_68 (53) = happyShift action_13
action_68 (8) = happyGoto action_122
action_68 (11) = happyGoto action_5
action_68 (12) = happyGoto action_60
action_68 _ = happyFail (happyExpListPerState 68)

action_69 _ = happyReduce_21

action_70 _ = happyReduce_18

action_71 (23) = happyShift action_75
action_71 (27) = happyShift action_76
action_71 (38) = happyShift action_34
action_71 (39) = happyShift action_35
action_71 (40) = happyShift action_36
action_71 (41) = happyShift action_37
action_71 (43) = happyShift action_38
action_71 (54) = happyShift action_39
action_71 (15) = happyGoto action_121
action_71 _ = happyFail (happyExpListPerState 71)

action_72 (23) = happyShift action_7
action_72 (27) = happyShift action_8
action_72 (31) = happyShift action_9
action_72 (32) = happyShift action_10
action_72 (42) = happyShift action_11
action_72 (52) = happyShift action_12
action_72 (53) = happyShift action_13
action_72 (11) = happyGoto action_5
action_72 (12) = happyGoto action_120
action_72 _ = happyFail (happyExpListPerState 72)

action_73 (53) = happyShift action_119
action_73 (10) = happyGoto action_118
action_73 _ = happyFail (happyExpListPerState 73)

action_74 (34) = happyShift action_101
action_74 _ = happyReduce_14

action_75 (23) = happyShift action_75
action_75 (27) = happyShift action_76
action_75 (38) = happyShift action_34
action_75 (39) = happyShift action_35
action_75 (40) = happyShift action_36
action_75 (41) = happyShift action_37
action_75 (43) = happyShift action_38
action_75 (54) = happyShift action_39
action_75 (15) = happyGoto action_99
action_75 _ = happyFail (happyExpListPerState 75)

action_76 (23) = happyShift action_75
action_76 (27) = happyShift action_76
action_76 (38) = happyShift action_34
action_76 (39) = happyShift action_35
action_76 (40) = happyShift action_36
action_76 (41) = happyShift action_37
action_76 (43) = happyShift action_38
action_76 (53) = happyShift action_91
action_76 (54) = happyShift action_39
action_76 (13) = happyGoto action_95
action_76 (14) = happyGoto action_96
action_76 (15) = happyGoto action_97
action_76 _ = happyFail (happyExpListPerState 76)

action_77 _ = happyReduce_60

action_78 _ = happyReduce_63

action_79 (45) = happyShift action_117
action_79 _ = happyFail (happyExpListPerState 79)

action_80 _ = happyReduce_55

action_81 (23) = happyShift action_15
action_81 (27) = happyShift action_16
action_81 (31) = happyShift action_17
action_81 (42) = happyShift action_18
action_81 (52) = happyShift action_19
action_81 (53) = happyShift action_20
action_81 (22) = happyGoto action_116
action_81 _ = happyFail (happyExpListPerState 81)

action_82 (23) = happyShift action_15
action_82 (27) = happyShift action_16
action_82 (31) = happyShift action_17
action_82 (42) = happyShift action_18
action_82 (52) = happyShift action_19
action_82 (53) = happyShift action_20
action_82 (19) = happyGoto action_115
action_82 (22) = happyGoto action_47
action_82 _ = happyFail (happyExpListPerState 82)

action_83 _ = happyReduce_62

action_84 _ = happyReduce_59

action_85 (23) = happyShift action_15
action_85 (27) = happyShift action_16
action_85 (31) = happyShift action_17
action_85 (42) = happyShift action_18
action_85 (52) = happyShift action_19
action_85 (53) = happyShift action_20
action_85 (22) = happyGoto action_114
action_85 _ = happyFail (happyExpListPerState 85)

action_86 (53) = happyShift action_113
action_86 (21) = happyGoto action_112
action_86 _ = happyFail (happyExpListPerState 86)

action_87 _ = happyReduce_45

action_88 (34) = happyShift action_101
action_88 _ = happyReduce_47

action_89 _ = happyReduce_42

action_90 (44) = happyShift action_111
action_90 _ = happyFail (happyExpListPerState 90)

action_91 (33) = happyShift action_110
action_91 _ = happyFail (happyExpListPerState 91)

action_92 (29) = happyShift action_109
action_92 _ = happyFail (happyExpListPerState 92)

action_93 _ = happyReduce_19

action_94 _ = happyReduce_22

action_95 (28) = happyShift action_108
action_95 _ = happyFail (happyExpListPerState 95)

action_96 (28) = happyShift action_107
action_96 _ = happyFail (happyExpListPerState 96)

action_97 (30) = happyShift action_106
action_97 (34) = happyShift action_101
action_97 _ = happyReduce_27

action_98 (33) = happyShift action_105
action_98 (45) = happyShift action_67
action_98 _ = happyReduce_15

action_99 (24) = happyShift action_104
action_99 (34) = happyShift action_101
action_99 _ = happyFail (happyExpListPerState 99)

action_100 (53) = happyShift action_103
action_100 (14) = happyGoto action_90
action_100 _ = happyFail (happyExpListPerState 100)

action_101 (23) = happyShift action_75
action_101 (27) = happyShift action_76
action_101 (38) = happyShift action_34
action_101 (39) = happyShift action_35
action_101 (40) = happyShift action_36
action_101 (41) = happyShift action_37
action_101 (43) = happyShift action_38
action_101 (54) = happyShift action_39
action_101 (15) = happyGoto action_102
action_101 _ = happyFail (happyExpListPerState 101)

action_102 (34) = happyShift action_101
action_102 _ = happyReduce_35

action_103 (33) = happyShift action_110
action_103 (45) = happyShift action_124
action_103 _ = happyFail (happyExpListPerState 103)

action_104 _ = happyReduce_31

action_105 (23) = happyShift action_75
action_105 (27) = happyShift action_76
action_105 (38) = happyShift action_34
action_105 (39) = happyShift action_35
action_105 (40) = happyShift action_36
action_105 (41) = happyShift action_37
action_105 (43) = happyShift action_38
action_105 (54) = happyShift action_39
action_105 (15) = happyGoto action_135
action_105 _ = happyFail (happyExpListPerState 105)

action_106 (23) = happyShift action_75
action_106 (27) = happyShift action_76
action_106 (38) = happyShift action_34
action_106 (39) = happyShift action_35
action_106 (40) = happyShift action_36
action_106 (41) = happyShift action_37
action_106 (43) = happyShift action_38
action_106 (54) = happyShift action_39
action_106 (13) = happyGoto action_134
action_106 (15) = happyGoto action_97
action_106 _ = happyFail (happyExpListPerState 106)

action_107 _ = happyReduce_37

action_108 _ = happyReduce_36

action_109 (23) = happyShift action_75
action_109 (27) = happyShift action_76
action_109 (38) = happyShift action_34
action_109 (39) = happyShift action_35
action_109 (40) = happyShift action_36
action_109 (41) = happyShift action_37
action_109 (43) = happyShift action_38
action_109 (54) = happyShift action_39
action_109 (15) = happyGoto action_133
action_109 _ = happyFail (happyExpListPerState 109)

action_110 (23) = happyShift action_75
action_110 (27) = happyShift action_76
action_110 (38) = happyShift action_34
action_110 (39) = happyShift action_35
action_110 (40) = happyShift action_36
action_110 (41) = happyShift action_37
action_110 (43) = happyShift action_38
action_110 (54) = happyShift action_39
action_110 (15) = happyGoto action_132
action_110 _ = happyFail (happyExpListPerState 110)

action_111 _ = happyReduce_38

action_112 _ = happyReduce_65

action_113 (35) = happyShift action_131
action_113 _ = happyFail (happyExpListPerState 113)

action_114 (23) = happyShift action_15
action_114 (27) = happyShift action_16
action_114 (29) = happyShift action_53
action_114 (31) = happyShift action_17
action_114 (42) = happyShift action_18
action_114 (52) = happyShift action_19
action_114 (53) = happyShift action_20
action_114 (22) = happyGoto action_52
action_114 _ = happyReduce_58

action_115 _ = happyReduce_49

action_116 (23) = happyShift action_15
action_116 (27) = happyShift action_16
action_116 (29) = happyShift action_53
action_116 (30) = happyShift action_130
action_116 (31) = happyShift action_17
action_116 (42) = happyShift action_18
action_116 (52) = happyShift action_19
action_116 (53) = happyShift action_20
action_116 (22) = happyGoto action_52
action_116 _ = happyReduce_50

action_117 (23) = happyShift action_15
action_117 (27) = happyShift action_16
action_117 (31) = happyShift action_17
action_117 (42) = happyShift action_18
action_117 (52) = happyShift action_19
action_117 (53) = happyShift action_20
action_117 (22) = happyGoto action_129
action_117 _ = happyFail (happyExpListPerState 117)

action_118 _ = happyReduce_24

action_119 (35) = happyShift action_128
action_119 _ = happyFail (happyExpListPerState 119)

action_120 (23) = happyShift action_31
action_120 (27) = happyShift action_32
action_120 (29) = happyShift action_33
action_120 (31) = happyShift action_9
action_120 (32) = happyShift action_10
action_120 (38) = happyShift action_34
action_120 (39) = happyShift action_35
action_120 (40) = happyShift action_36
action_120 (41) = happyShift action_37
action_120 (42) = happyShift action_11
action_120 (43) = happyShift action_38
action_120 (52) = happyShift action_12
action_120 (53) = happyShift action_13
action_120 (54) = happyShift action_39
action_120 (11) = happyGoto action_5
action_120 (12) = happyGoto action_29
action_120 (15) = happyGoto action_30
action_120 _ = happyReduce_25

action_121 (29) = happyShift action_127
action_121 (34) = happyShift action_101
action_121 _ = happyFail (happyExpListPerState 121)

action_122 _ = happyReduce_6

action_123 (23) = happyShift action_31
action_123 (27) = happyShift action_32
action_123 (29) = happyShift action_33
action_123 (30) = happyShift action_126
action_123 (31) = happyShift action_9
action_123 (32) = happyShift action_10
action_123 (38) = happyShift action_34
action_123 (39) = happyShift action_35
action_123 (40) = happyShift action_36
action_123 (41) = happyShift action_37
action_123 (42) = happyShift action_11
action_123 (43) = happyShift action_38
action_123 (52) = happyShift action_12
action_123 (53) = happyShift action_13
action_123 (54) = happyShift action_39
action_123 (11) = happyGoto action_5
action_123 (12) = happyGoto action_29
action_123 (15) = happyGoto action_30
action_123 _ = happyReduce_7

action_124 (23) = happyShift action_7
action_124 (27) = happyShift action_8
action_124 (31) = happyShift action_9
action_124 (32) = happyShift action_10
action_124 (42) = happyShift action_11
action_124 (52) = happyShift action_12
action_124 (53) = happyShift action_13
action_124 (11) = happyGoto action_5
action_124 (12) = happyGoto action_125
action_124 _ = happyFail (happyExpListPerState 124)

action_125 (23) = happyShift action_31
action_125 (27) = happyShift action_32
action_125 (29) = happyShift action_33
action_125 (31) = happyShift action_9
action_125 (32) = happyShift action_10
action_125 (38) = happyShift action_34
action_125 (39) = happyShift action_35
action_125 (40) = happyShift action_36
action_125 (41) = happyShift action_37
action_125 (42) = happyShift action_11
action_125 (43) = happyShift action_38
action_125 (44) = happyShift action_145
action_125 (52) = happyShift action_12
action_125 (53) = happyShift action_13
action_125 (54) = happyShift action_39
action_125 (11) = happyGoto action_5
action_125 (12) = happyGoto action_29
action_125 (15) = happyGoto action_30
action_125 _ = happyFail (happyExpListPerState 125)

action_126 (53) = happyShift action_144
action_126 (9) = happyGoto action_143
action_126 _ = happyFail (happyExpListPerState 126)

action_127 (23) = happyShift action_7
action_127 (27) = happyShift action_8
action_127 (31) = happyShift action_9
action_127 (32) = happyShift action_10
action_127 (42) = happyShift action_11
action_127 (52) = happyShift action_12
action_127 (53) = happyShift action_13
action_127 (11) = happyGoto action_5
action_127 (12) = happyGoto action_142
action_127 _ = happyFail (happyExpListPerState 127)

action_128 (23) = happyShift action_7
action_128 (27) = happyShift action_8
action_128 (31) = happyShift action_9
action_128 (32) = happyShift action_10
action_128 (42) = happyShift action_11
action_128 (52) = happyShift action_12
action_128 (53) = happyShift action_13
action_128 (11) = happyGoto action_5
action_128 (12) = happyGoto action_141
action_128 _ = happyFail (happyExpListPerState 128)

action_129 (23) = happyShift action_15
action_129 (27) = happyShift action_16
action_129 (29) = happyShift action_53
action_129 (31) = happyShift action_17
action_129 (42) = happyShift action_18
action_129 (44) = happyShift action_140
action_129 (52) = happyShift action_19
action_129 (53) = happyShift action_20
action_129 (22) = happyGoto action_52
action_129 _ = happyFail (happyExpListPerState 129)

action_130 (53) = happyShift action_139
action_130 (20) = happyGoto action_138
action_130 _ = happyFail (happyExpListPerState 130)

action_131 (23) = happyShift action_15
action_131 (27) = happyShift action_16
action_131 (31) = happyShift action_17
action_131 (42) = happyShift action_18
action_131 (52) = happyShift action_19
action_131 (53) = happyShift action_20
action_131 (22) = happyGoto action_137
action_131 _ = happyFail (happyExpListPerState 131)

action_132 (30) = happyShift action_136
action_132 (34) = happyShift action_101
action_132 _ = happyReduce_29

action_133 (34) = happyShift action_101
action_133 _ = happyReduce_39

action_134 _ = happyReduce_28

action_135 (28) = happyReduce_29
action_135 (30) = happyShift action_136
action_135 (34) = happyShift action_101
action_135 _ = happyReduce_14

action_136 (53) = happyShift action_91
action_136 (14) = happyGoto action_150
action_136 _ = happyFail (happyExpListPerState 136)

action_137 (23) = happyShift action_15
action_137 (27) = happyShift action_16
action_137 (29) = happyShift action_53
action_137 (30) = happyShift action_149
action_137 (31) = happyShift action_17
action_137 (42) = happyShift action_18
action_137 (52) = happyShift action_19
action_137 (53) = happyShift action_20
action_137 (22) = happyGoto action_52
action_137 _ = happyReduce_52

action_138 _ = happyReduce_51

action_139 (45) = happyShift action_81
action_139 _ = happyFail (happyExpListPerState 139)

action_140 (24) = happyShift action_148
action_140 _ = happyFail (happyExpListPerState 140)

action_141 (23) = happyShift action_31
action_141 (27) = happyShift action_32
action_141 (29) = happyShift action_33
action_141 (30) = happyShift action_147
action_141 (31) = happyShift action_9
action_141 (32) = happyShift action_10
action_141 (38) = happyShift action_34
action_141 (39) = happyShift action_35
action_141 (40) = happyShift action_36
action_141 (41) = happyShift action_37
action_141 (42) = happyShift action_11
action_141 (43) = happyShift action_38
action_141 (52) = happyShift action_12
action_141 (53) = happyShift action_13
action_141 (54) = happyShift action_39
action_141 (11) = happyGoto action_5
action_141 (12) = happyGoto action_29
action_141 (15) = happyGoto action_30
action_141 _ = happyReduce_9

action_142 (23) = happyShift action_31
action_142 (27) = happyShift action_32
action_142 (29) = happyShift action_33
action_142 (31) = happyShift action_9
action_142 (32) = happyShift action_10
action_142 (38) = happyShift action_34
action_142 (39) = happyShift action_35
action_142 (40) = happyShift action_36
action_142 (41) = happyShift action_37
action_142 (42) = happyShift action_11
action_142 (43) = happyShift action_38
action_142 (52) = happyShift action_12
action_142 (53) = happyShift action_13
action_142 (54) = happyShift action_39
action_142 (11) = happyGoto action_5
action_142 (12) = happyGoto action_29
action_142 (15) = happyGoto action_30
action_142 _ = happyReduce_17

action_143 _ = happyReduce_8

action_144 (45) = happyShift action_67
action_144 _ = happyFail (happyExpListPerState 144)

action_145 (33) = happyShift action_146
action_145 _ = happyFail (happyExpListPerState 145)

action_146 (23) = happyShift action_75
action_146 (27) = happyShift action_76
action_146 (38) = happyShift action_34
action_146 (39) = happyShift action_35
action_146 (40) = happyShift action_36
action_146 (41) = happyShift action_37
action_146 (43) = happyShift action_38
action_146 (54) = happyShift action_39
action_146 (15) = happyGoto action_153
action_146 _ = happyFail (happyExpListPerState 146)

action_147 (53) = happyShift action_119
action_147 (10) = happyGoto action_152
action_147 _ = happyFail (happyExpListPerState 147)

action_148 _ = happyReduce_64

action_149 (53) = happyShift action_113
action_149 (21) = happyGoto action_151
action_149 _ = happyFail (happyExpListPerState 149)

action_150 _ = happyReduce_30

action_151 _ = happyReduce_53

action_152 _ = happyReduce_10

action_153 (24) = happyShift action_154
action_153 (34) = happyShift action_101
action_153 _ = happyFail (happyExpListPerState 153)

action_154 _ = happyReduce_11

happyReduce_4 = happySpecReduce_1  7 happyReduction_4
happyReduction_4 (HappyAbsSyn12  happy_var_1)
	 =  HappyAbsSyn7
		 (happy_var_1
	)
happyReduction_4 _  = notHappyAtAll 

happyReduce_5 = happySpecReduce_1  8 happyReduction_5
happyReduction_5 (HappyAbsSyn12  happy_var_1)
	 =  HappyAbsSyn8
		 ([happy_var_1]
	)
happyReduction_5 _  = notHappyAtAll 

happyReduce_6 = happySpecReduce_3  8 happyReduction_6
happyReduction_6 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn12  happy_var_1)
	 =  HappyAbsSyn8
		 (happy_var_1 : happy_var_3
	)
happyReduction_6 _ _ _  = notHappyAtAll 

happyReduce_7 = happySpecReduce_3  9 happyReduction_7
happyReduction_7 (HappyAbsSyn12  happy_var_3)
	_
	(HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn9
		 ([(happy_var_1, happy_var_3)]
	)
happyReduction_7 _ _ _  = notHappyAtAll 

happyReduce_8 = happyReduce 5 9 happyReduction_8
happyReduction_8 ((HappyAbsSyn9  happy_var_5) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn12  happy_var_3) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_1)) `HappyStk`
	happyRest)
	 = HappyAbsSyn9
		 ((happy_var_1, happy_var_3) : happy_var_5
	) `HappyStk` happyRest

happyReduce_9 = happySpecReduce_3  10 happyReduction_9
happyReduction_9 (HappyAbsSyn12  happy_var_3)
	_
	(HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn10
		 ([(happy_var_1, happy_var_3)]
	)
happyReduction_9 _ _ _  = notHappyAtAll 

happyReduce_10 = happyReduce 5 10 happyReduction_10
happyReduction_10 ((HappyAbsSyn10  happy_var_5) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn12  happy_var_3) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_1)) `HappyStk`
	happyRest)
	 = HappyAbsSyn10
		 ((happy_var_1, happy_var_3) : happy_var_5
	) `HappyStk` happyRest

happyReduce_11 = happyReduce 9 11 happyReduction_11
happyReduction_11 (_ `HappyStk`
	(HappyAbsSyn15  happy_var_8) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn12  happy_var_5) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_3)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn11
		 (Inj happy_var_3 happy_var_5 happy_var_8
	) `HappyStk` happyRest

happyReduce_12 = happySpecReduce_2  12 happyReduction_12
happyReduction_12 _
	_
	 =  HappyAbsSyn12
		 (U
	)

happyReduce_13 = happySpecReduce_3  12 happyReduction_13
happyReduction_13 _
	(HappyAbsSyn12  happy_var_2)
	_
	 =  HappyAbsSyn12
		 (happy_var_2
	)
happyReduction_13 _ _ _  = notHappyAtAll 

happyReduce_14 = happySpecReduce_3  12 happyReduction_14
happyReduction_14 (HappyAbsSyn15  happy_var_3)
	_
	(HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn12
		 (C (string2Name happy_var_1 :: TmName) happy_var_3
	)
happyReduction_14 _ _ _  = notHappyAtAll 

happyReduce_15 = happySpecReduce_1  12 happyReduction_15
happyReduction_15 (HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn12
		 (V (string2Name happy_var_1 :: TmName)
	)
happyReduction_15 _  = notHappyAtAll 

happyReduce_16 = happySpecReduce_1  12 happyReduction_16
happyReduction_16 (HappyTerminal (Num happy_var_1))
	 =  HappyAbsSyn12
		 (N happy_var_1
	)
happyReduction_16 _  = notHappyAtAll 

happyReduce_17 = happyReduce 6 12 happyReduction_17
happyReduction_17 ((HappyAbsSyn12  happy_var_6) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn15  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn12
		 (L (bind ((string2Name happy_var_2 :: TmName), Embed happy_var_4) happy_var_6)
	) `HappyStk` happyRest

happyReduce_18 = happySpecReduce_3  12 happyReduction_18
happyReduction_18 _
	(HappyAbsSyn8  happy_var_2)
	_
	 =  HappyAbsSyn12
		 (T happy_var_2
	)
happyReduction_18 _ _ _  = notHappyAtAll 

happyReduce_19 = happySpecReduce_3  12 happyReduction_19
happyReduction_19 (HappyTerminal (Num happy_var_3))
	_
	(HappyAbsSyn12  happy_var_1)
	 =  HappyAbsSyn12
		 (P happy_var_1 happy_var_3
	)
happyReduction_19 _ _ _  = notHappyAtAll 

happyReduce_20 = happySpecReduce_2  12 happyReduction_20
happyReduction_20 (HappyAbsSyn12  happy_var_2)
	(HappyAbsSyn12  happy_var_1)
	 =  HappyAbsSyn12
		 (A happy_var_1 happy_var_2
	)
happyReduction_20 _ _  = notHappyAtAll 

happyReduce_21 = happySpecReduce_3  12 happyReduction_21
happyReduction_21 _
	(HappyAbsSyn9  happy_var_2)
	_
	 =  HappyAbsSyn12
		 (R happy_var_2
	)
happyReduction_21 _ _ _  = notHappyAtAll 

happyReduce_22 = happySpecReduce_3  12 happyReduction_22
happyReduction_22 (HappyTerminal (ID happy_var_3))
	_
	(HappyAbsSyn12  happy_var_1)
	 =  HappyAbsSyn12
		 (F happy_var_1 happy_var_3
	)
happyReduction_22 _ _ _  = notHappyAtAll 

happyReduce_23 = happySpecReduce_1  12 happyReduction_23
happyReduction_23 (HappyAbsSyn11  happy_var_1)
	 =  HappyAbsSyn12
		 (happy_var_1
	)
happyReduction_23 _  = notHappyAtAll 

happyReduce_24 = happyReduce 4 12 happyReduction_24
happyReduction_24 ((HappyAbsSyn10  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn12  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn12
		 (Case happy_var_2 happy_var_4
	) `HappyStk` happyRest

happyReduce_25 = happyReduce 4 12 happyReduction_25
happyReduction_25 ((HappyAbsSyn12  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TyID happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn12
		 (TyL (bind (string2Name happy_var_2 :: TyName) happy_var_4)
	) `HappyStk` happyRest

happyReduce_26 = happySpecReduce_2  12 happyReduction_26
happyReduction_26 (HappyAbsSyn15  happy_var_2)
	(HappyAbsSyn12  happy_var_1)
	 =  HappyAbsSyn12
		 (TyA happy_var_1 happy_var_2
	)
happyReduction_26 _ _  = notHappyAtAll 

happyReduce_27 = happySpecReduce_1  13 happyReduction_27
happyReduction_27 (HappyAbsSyn15  happy_var_1)
	 =  HappyAbsSyn13
		 ([happy_var_1]
	)
happyReduction_27 _  = notHappyAtAll 

happyReduce_28 = happySpecReduce_3  13 happyReduction_28
happyReduction_28 (HappyAbsSyn13  happy_var_3)
	_
	(HappyAbsSyn15  happy_var_1)
	 =  HappyAbsSyn13
		 (happy_var_1 : happy_var_3
	)
happyReduction_28 _ _ _  = notHappyAtAll 

happyReduce_29 = happySpecReduce_3  14 happyReduction_29
happyReduction_29 (HappyAbsSyn15  happy_var_3)
	_
	(HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn14
		 ([(happy_var_1, happy_var_3)]
	)
happyReduction_29 _ _ _  = notHappyAtAll 

happyReduce_30 = happyReduce 5 14 happyReduction_30
happyReduction_30 ((HappyAbsSyn14  happy_var_5) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn15  happy_var_3) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_1)) `HappyStk`
	happyRest)
	 = HappyAbsSyn14
		 ((happy_var_1, happy_var_3) : happy_var_5
	) `HappyStk` happyRest

happyReduce_31 = happySpecReduce_3  15 happyReduction_31
happyReduction_31 _
	(HappyAbsSyn15  happy_var_2)
	_
	 =  HappyAbsSyn15
		 (happy_var_2
	)
happyReduction_31 _ _ _  = notHappyAtAll 

happyReduce_32 = happySpecReduce_1  15 happyReduction_32
happyReduction_32 _
	 =  HappyAbsSyn15
		 (INT
	)

happyReduce_33 = happySpecReduce_1  15 happyReduction_33
happyReduction_33 _
	 =  HappyAbsSyn15
		 (BOOL
	)

happyReduce_34 = happySpecReduce_1  15 happyReduction_34
happyReduction_34 (HappyTerminal (TyID happy_var_1))
	 =  HappyAbsSyn15
		 (TyVar (string2Name happy_var_1 :: TyName)
	)
happyReduction_34 _  = notHappyAtAll 

happyReduce_35 = happySpecReduce_3  15 happyReduction_35
happyReduction_35 (HappyAbsSyn15  happy_var_3)
	_
	(HappyAbsSyn15  happy_var_1)
	 =  HappyAbsSyn15
		 (Arr happy_var_1 happy_var_3
	)
happyReduction_35 _ _ _  = notHappyAtAll 

happyReduce_36 = happySpecReduce_3  15 happyReduction_36
happyReduction_36 _
	(HappyAbsSyn13  happy_var_2)
	_
	 =  HappyAbsSyn15
		 (Prod happy_var_2
	)
happyReduction_36 _ _ _  = notHappyAtAll 

happyReduce_37 = happySpecReduce_3  15 happyReduction_37
happyReduction_37 _
	(HappyAbsSyn14  happy_var_2)
	_
	 =  HappyAbsSyn15
		 (Rec happy_var_2
	)
happyReduction_37 _ _ _  = notHappyAtAll 

happyReduce_38 = happySpecReduce_3  15 happyReduction_38
happyReduction_38 _
	(HappyAbsSyn14  happy_var_2)
	_
	 =  HappyAbsSyn15
		 (Var happy_var_2
	)
happyReduction_38 _ _ _  = notHappyAtAll 

happyReduce_39 = happyReduce 4 15 happyReduction_39
happyReduction_39 ((HappyAbsSyn15  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (TyID happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn15
		 (Poly (bind (string2Name happy_var_2 :: TyName) happy_var_4)
	) `HappyStk` happyRest

happyReduce_40 = happySpecReduce_1  15 happyReduction_40
happyReduction_40 _
	 =  HappyAbsSyn15
		 (Unit
	)

happyReduce_41 = happySpecReduce_1  16 happyReduction_41
happyReduction_41 (HappyTerminal (TyID happy_var_1))
	 =  HappyAbsSyn16
		 ([(string2Name happy_var_1 :: TyName)]
	)
happyReduction_41 _  = notHappyAtAll 

happyReduce_42 = happySpecReduce_3  16 happyReduction_42
happyReduction_42 (HappyAbsSyn16  happy_var_3)
	_
	(HappyTerminal (TyID happy_var_1))
	 =  HappyAbsSyn16
		 ((string2Name happy_var_1 :: TyName) : happy_var_3
	)
happyReduction_42 _ _ _  = notHappyAtAll 

happyReduce_43 = happySpecReduce_1  16 happyReduction_43
happyReduction_43 _
	 =  HappyAbsSyn16
		 ([]
	)

happyReduce_44 = happySpecReduce_1  17 happyReduction_44
happyReduction_44 (HappyAbsSyn18  happy_var_1)
	 =  HappyAbsSyn17
		 ([happy_var_1]
	)
happyReduction_44 _  = notHappyAtAll 

happyReduce_45 = happySpecReduce_3  17 happyReduction_45
happyReduction_45 (HappyAbsSyn17  happy_var_3)
	_
	(HappyAbsSyn18  happy_var_1)
	 =  HappyAbsSyn17
		 (happy_var_1 : happy_var_3
	)
happyReduction_45 _ _ _  = notHappyAtAll 

happyReduce_46 = happySpecReduce_1  17 happyReduction_46
happyReduction_46 _
	 =  HappyAbsSyn17
		 ([]
	)

happyReduce_47 = happySpecReduce_3  18 happyReduction_47
happyReduction_47 (HappyAbsSyn15  happy_var_3)
	_
	(HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn18
		 (((string2Name happy_var_1 :: TmName),happy_var_3)
	)
happyReduction_47 _ _ _  = notHappyAtAll 

happyReduce_48 = happySpecReduce_1  19 happyReduction_48
happyReduction_48 (HappyAbsSyn22  happy_var_1)
	 =  HappyAbsSyn19
		 ([happy_var_1]
	)
happyReduction_48 _  = notHappyAtAll 

happyReduce_49 = happySpecReduce_3  19 happyReduction_49
happyReduction_49 (HappyAbsSyn19  happy_var_3)
	_
	(HappyAbsSyn22  happy_var_1)
	 =  HappyAbsSyn19
		 (happy_var_1 : happy_var_3
	)
happyReduction_49 _ _ _  = notHappyAtAll 

happyReduce_50 = happySpecReduce_3  20 happyReduction_50
happyReduction_50 (HappyAbsSyn22  happy_var_3)
	_
	(HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn20
		 ([(happy_var_1, happy_var_3)]
	)
happyReduction_50 _ _ _  = notHappyAtAll 

happyReduce_51 = happyReduce 5 20 happyReduction_51
happyReduction_51 ((HappyAbsSyn20  happy_var_5) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn22  happy_var_3) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_1)) `HappyStk`
	happyRest)
	 = HappyAbsSyn20
		 ((happy_var_1, happy_var_3) : happy_var_5
	) `HappyStk` happyRest

happyReduce_52 = happySpecReduce_3  21 happyReduction_52
happyReduction_52 (HappyAbsSyn22  happy_var_3)
	_
	(HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn21
		 ([(happy_var_1, happy_var_3)]
	)
happyReduction_52 _ _ _  = notHappyAtAll 

happyReduce_53 = happyReduce 5 21 happyReduction_53
happyReduction_53 ((HappyAbsSyn21  happy_var_5) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn22  happy_var_3) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_1)) `HappyStk`
	happyRest)
	 = HappyAbsSyn21
		 ((happy_var_1, happy_var_3) : happy_var_5
	) `HappyStk` happyRest

happyReduce_54 = happySpecReduce_2  22 happyReduction_54
happyReduction_54 _
	_
	 =  HappyAbsSyn22
		 (U
	)

happyReduce_55 = happySpecReduce_3  22 happyReduction_55
happyReduction_55 _
	(HappyAbsSyn22  happy_var_2)
	_
	 =  HappyAbsSyn22
		 (happy_var_2
	)
happyReduction_55 _ _ _  = notHappyAtAll 

happyReduce_56 = happySpecReduce_1  22 happyReduction_56
happyReduction_56 (HappyTerminal (ID happy_var_1))
	 =  HappyAbsSyn22
		 (V (string2Name happy_var_1 :: TmName)
	)
happyReduction_56 _  = notHappyAtAll 

happyReduce_57 = happySpecReduce_1  22 happyReduction_57
happyReduction_57 (HappyTerminal (Num happy_var_1))
	 =  HappyAbsSyn22
		 (N happy_var_1
	)
happyReduction_57 _  = notHappyAtAll 

happyReduce_58 = happyReduce 4 22 happyReduction_58
happyReduction_58 ((HappyAbsSyn22  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_2)) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn22
		 (L (bind ((string2Name happy_var_2 :: TmName), Embed Unit) happy_var_4)
	) `HappyStk` happyRest

happyReduce_59 = happySpecReduce_3  22 happyReduction_59
happyReduction_59 _
	(HappyAbsSyn19  happy_var_2)
	_
	 =  HappyAbsSyn22
		 (T happy_var_2
	)
happyReduction_59 _ _ _  = notHappyAtAll 

happyReduce_60 = happySpecReduce_3  22 happyReduction_60
happyReduction_60 (HappyTerminal (Num happy_var_3))
	_
	(HappyAbsSyn22  happy_var_1)
	 =  HappyAbsSyn22
		 (P happy_var_1 happy_var_3
	)
happyReduction_60 _ _ _  = notHappyAtAll 

happyReduce_61 = happySpecReduce_2  22 happyReduction_61
happyReduction_61 (HappyAbsSyn22  happy_var_2)
	(HappyAbsSyn22  happy_var_1)
	 =  HappyAbsSyn22
		 (A happy_var_1 happy_var_2
	)
happyReduction_61 _ _  = notHappyAtAll 

happyReduce_62 = happySpecReduce_3  22 happyReduction_62
happyReduction_62 _
	(HappyAbsSyn20  happy_var_2)
	_
	 =  HappyAbsSyn22
		 (R happy_var_2
	)
happyReduction_62 _ _ _  = notHappyAtAll 

happyReduce_63 = happySpecReduce_3  22 happyReduction_63
happyReduction_63 (HappyTerminal (ID happy_var_3))
	_
	(HappyAbsSyn22  happy_var_1)
	 =  HappyAbsSyn22
		 (F happy_var_1 happy_var_3
	)
happyReduction_63 _ _ _  = notHappyAtAll 

happyReduce_64 = happyReduce 7 22 happyReduction_64
happyReduction_64 (_ `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn22  happy_var_5) `HappyStk`
	_ `HappyStk`
	(HappyTerminal (ID happy_var_3)) `HappyStk`
	_ `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn22
		 (Inj happy_var_3 happy_var_5 Unit
	) `HappyStk` happyRest

happyReduce_65 = happyReduce 4 22 happyReduction_65
happyReduction_65 ((HappyAbsSyn21  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn22  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn22
		 (Case happy_var_2 happy_var_4
	) `HappyStk` happyRest

happyNewToken action sts stk [] =
	action 55 55 notHappyAtAll (HappyState action) sts stk []

happyNewToken action sts stk (tk:tks) =
	let cont i = action i i tk (HappyState action) sts stk tks in
	case tk of {
	LPar -> cont 23;
	RPar -> cont 24;
	LSBracket -> cont 25;
	RSBracket -> cont 26;
	LBrace -> cont 27;
	RBrace -> cont 28;
	TDot -> cont 29;
	TCom -> cont 30;
	TLam -> cont 31;
	TLLam -> cont 32;
	TCol -> cont 33;
	TArrow -> cont 34;
	TLArrow -> cont 35;
	TPlus -> cont 36;
	TMinus -> cont 37;
	TAll -> cont 38;
	TINT -> cont 39;
	TBOOL -> cont 40;
	TUNIT -> cont 41;
	TCase -> cont 42;
	LAngle -> cont 43;
	RAngle -> cont 44;
	TEqual -> cont 45;
	TOf -> cont 46;
	Empty -> cont 47;
	TSucc -> cont 48;
	TPred -> cont 49;
	TTrue -> cont 50;
	TFalse -> cont 51;
	Num happy_dollar_dollar -> cont 52;
	ID happy_dollar_dollar -> cont 53;
	TyID happy_dollar_dollar -> cont 54;
	_ -> happyError' ((tk:tks), [])
	}

happyError_ explist 55 tk tks = happyError' (tks, explist)
happyError_ explist _ tk tks = happyError' ((tk:tks), explist)

newtype HappyIdentity a = HappyIdentity a
happyIdentity = HappyIdentity
happyRunIdentity (HappyIdentity a) = a

instance Functor HappyIdentity where
    fmap f (HappyIdentity a) = HappyIdentity (f a)

instance Applicative HappyIdentity where
    pure  = HappyIdentity
    (<*>) = ap
instance Monad HappyIdentity where
    return = pure
    (HappyIdentity p) >>= q = q p

happyThen :: () => HappyIdentity a -> (a -> HappyIdentity b) -> HappyIdentity b
happyThen = (>>=)
happyReturn :: () => a -> HappyIdentity a
happyReturn = (return)
happyThen1 m k tks = (>>=) m (\a -> k a tks)
happyReturn1 :: () => a -> b -> HappyIdentity a
happyReturn1 = \a tks -> (return) a
happyError' :: () => ([(Token)], [String]) -> HappyIdentity a
happyError' = HappyIdentity . (\(tokens, _) -> parseError tokens)
happyParseExp tks = happyRunIdentity happySomeParser where
 happySomeParser = happyThen (happyParse action_0 tks) (\x -> case x of {HappyAbsSyn12 z -> happyReturn z; _other -> notHappyAtAll })

happyParseTypeContext tks = happyRunIdentity happySomeParser where
 happySomeParser = happyThen (happyParse action_1 tks) (\x -> case x of {HappyAbsSyn16 z -> happyReturn z; _other -> notHappyAtAll })

happyParseEnv tks = happyRunIdentity happySomeParser where
 happySomeParser = happyThen (happyParse action_2 tks) (\x -> case x of {HappyAbsSyn17 z -> happyReturn z; _other -> notHappyAtAll })

happyParseTerm tks = happyRunIdentity happySomeParser where
 happySomeParser = happyThen (happyParse action_3 tks) (\x -> case x of {HappyAbsSyn22 z -> happyReturn z; _other -> notHappyAtAll })

happySeq = happyDontSeq


parseError :: [Token] -> a
parseError [] = error "Parse error at EOF"
parseError (t:ts) = error $ "Parse error: " ++ show t

parseExp         = happyParseExp . alexScanTokens
parseTypeContext = happyParseTypeContext . alexScanTokens
parseEnv         = happyParseEnv . alexScanTokens
parseTerm        = happyParseTerm . alexScanTokens
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "<built-in>" #-}
{-# LINE 1 "<command-line>" #-}







# 1 "/usr/include/stdc-predef.h" 1 3 4

# 17 "/usr/include/stdc-predef.h" 3 4











































{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "/usr/lib/ghc/include/ghcversion.h" #-}















{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "/tmp/ghc8336_0/ghc_2.h" #-}
































































































































































































{-# LINE 7 "<command-line>" #-}
{-# LINE 1 "templates/GenericTemplate.hs" #-}
-- Id: GenericTemplate.hs,v 1.26 2005/01/14 14:47:22 simonmar Exp 









{-# LINE 43 "templates/GenericTemplate.hs" #-}

data Happy_IntList = HappyCons Int Happy_IntList







{-# LINE 65 "templates/GenericTemplate.hs" #-}

{-# LINE 75 "templates/GenericTemplate.hs" #-}

{-# LINE 84 "templates/GenericTemplate.hs" #-}

infixr 9 `HappyStk`
data HappyStk a = HappyStk a (HappyStk a)

-----------------------------------------------------------------------------
-- starting the parse

happyParse start_state = happyNewToken start_state notHappyAtAll notHappyAtAll

-----------------------------------------------------------------------------
-- Accepting the parse

-- If the current token is (1), it means we've just accepted a partial
-- parse (a %partial parser).  We must ignore the saved token on the top of
-- the stack in this case.
happyAccept (1) tk st sts (_ `HappyStk` ans `HappyStk` _) =
        happyReturn1 ans
happyAccept j tk st sts (HappyStk ans _) = 
         (happyReturn1 ans)

-----------------------------------------------------------------------------
-- Arrays only: do the next action

{-# LINE 137 "templates/GenericTemplate.hs" #-}

{-# LINE 147 "templates/GenericTemplate.hs" #-}
indexShortOffAddr arr off = arr Happy_Data_Array.! off


{-# INLINE happyLt #-}
happyLt x y = (x < y)






readArrayBit arr bit =
    Bits.testBit (indexShortOffAddr arr (bit `div` 16)) (bit `mod` 16)






-----------------------------------------------------------------------------
-- HappyState data type (not arrays)



newtype HappyState b c = HappyState
        (Int ->                    -- token number
         Int ->                    -- token number (yes, again)
         b ->                           -- token semantic value
         HappyState b c ->              -- current state
         [HappyState b c] ->            -- state stack
         c)



-----------------------------------------------------------------------------
-- Shifting a token

happyShift new_state (1) tk st sts stk@(x `HappyStk` _) =
     let i = (case x of { HappyErrorToken (i) -> i }) in
--     trace "shifting the error token" $
     new_state i i tk (HappyState (new_state)) ((st):(sts)) (stk)

happyShift new_state i tk st sts stk =
     happyNewToken new_state ((st):(sts)) ((HappyTerminal (tk))`HappyStk`stk)

-- happyReduce is specialised for the common cases.

happySpecReduce_0 i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happySpecReduce_0 nt fn j tk st@((HappyState (action))) sts stk
     = action nt j tk st ((st):(sts)) (fn `HappyStk` stk)

happySpecReduce_1 i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happySpecReduce_1 nt fn j tk _ sts@(((st@(HappyState (action))):(_))) (v1`HappyStk`stk')
     = let r = fn v1 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_2 i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happySpecReduce_2 nt fn j tk _ ((_):(sts@(((st@(HappyState (action))):(_))))) (v1`HappyStk`v2`HappyStk`stk')
     = let r = fn v1 v2 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_3 i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happySpecReduce_3 nt fn j tk _ ((_):(((_):(sts@(((st@(HappyState (action))):(_))))))) (v1`HappyStk`v2`HappyStk`v3`HappyStk`stk')
     = let r = fn v1 v2 v3 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happyReduce k i fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happyReduce k nt fn j tk st sts stk
     = case happyDrop (k - ((1) :: Int)) sts of
         sts1@(((st1@(HappyState (action))):(_))) ->
                let r = fn stk in  -- it doesn't hurt to always seq here...
                happyDoSeq r (action nt j tk st1 sts1 r)

happyMonadReduce k nt fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happyMonadReduce k nt fn j tk st sts stk =
      case happyDrop k ((st):(sts)) of
        sts1@(((st1@(HappyState (action))):(_))) ->
          let drop_stk = happyDropStk k stk in
          happyThen1 (fn stk tk) (\r -> action nt j tk st1 sts1 (r `HappyStk` drop_stk))

happyMonad2Reduce k nt fn (1) tk st sts stk
     = happyFail [] (1) tk st sts stk
happyMonad2Reduce k nt fn j tk st sts stk =
      case happyDrop k ((st):(sts)) of
        sts1@(((st1@(HappyState (action))):(_))) ->
         let drop_stk = happyDropStk k stk





             _ = nt :: Int
             new_state = action

          in
          happyThen1 (fn stk tk) (\r -> happyNewToken new_state sts1 (r `HappyStk` drop_stk))

happyDrop (0) l = l
happyDrop n ((_):(t)) = happyDrop (n - ((1) :: Int)) t

happyDropStk (0) l = l
happyDropStk n (x `HappyStk` xs) = happyDropStk (n - ((1)::Int)) xs

-----------------------------------------------------------------------------
-- Moving to a new state after a reduction

{-# LINE 267 "templates/GenericTemplate.hs" #-}
happyGoto action j tk st = action j j tk (HappyState action)


-----------------------------------------------------------------------------
-- Error recovery ((1) is the error token)

-- parse error if we are in recovery and we fail again
happyFail explist (1) tk old_st _ stk@(x `HappyStk` _) =
     let i = (case x of { HappyErrorToken (i) -> i }) in
--      trace "failing" $ 
        happyError_ explist i tk

{-  We don't need state discarding for our restricted implementation of
    "error".  In fact, it can cause some bogus parses, so I've disabled it
    for now --SDM

-- discard a state
happyFail  (1) tk old_st (((HappyState (action))):(sts)) 
                                                (saved_tok `HappyStk` _ `HappyStk` stk) =
--      trace ("discarding state, depth " ++ show (length stk))  $
        action (1) (1) tk (HappyState (action)) sts ((saved_tok`HappyStk`stk))
-}

-- Enter error recovery: generate an error token,
--                       save the old token and carry on.
happyFail explist i tk (HappyState (action)) sts stk =
--      trace "entering error recovery" $
        action (1) (1) tk (HappyState (action)) sts ( (HappyErrorToken (i)) `HappyStk` stk)

-- Internal happy errors:

notHappyAtAll :: a
notHappyAtAll = error "Internal Happy error\n"

-----------------------------------------------------------------------------
-- Hack to get the typechecker to accept our action functions







-----------------------------------------------------------------------------
-- Seq-ing.  If the --strict flag is given, then Happy emits 
--      happySeq = happyDoSeq
-- otherwise it emits
--      happySeq = happyDontSeq

happyDoSeq, happyDontSeq :: a -> b -> b
happyDoSeq   a b = a `seq` b
happyDontSeq a b = b

-----------------------------------------------------------------------------
-- Don't inline any functions from the template.  GHC has a nasty habit
-- of deciding to inline happyGoto everywhere, which increases the size of
-- the generated parser quite a bit.

{-# LINE 333 "templates/GenericTemplate.hs" #-}
{-# NOINLINE happyShift #-}
{-# NOINLINE happySpecReduce_0 #-}
{-# NOINLINE happySpecReduce_1 #-}
{-# NOINLINE happySpecReduce_2 #-}
{-# NOINLINE happySpecReduce_3 #-}
{-# NOINLINE happyReduce #-}
{-# NOINLINE happyMonadReduce #-}
{-# NOINLINE happyGoto #-}
{-# NOINLINE happyFail #-}

-- end of Happy Template.
