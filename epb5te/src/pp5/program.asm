abmain:
	BeginFunc 16 ;
	_tmp0 = 4 ;
	PushParam _tmp0 ;
	_tmp1 = 5 ;
	PushParam _tmp1 ;
	_tmp2 = LCall _test ;
	PopParams 8 ;
	c = _tmp2 ;
	PushParam c ;
	LCall _PrintInt ;
	PopParams 4 ;
	EndFunc ;
_test:
	BeginFunc 4 ;
	_tmp3 = a + b ;
	Return _tmp3 ;
	EndFunc ;
