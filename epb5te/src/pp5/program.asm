main:
	BeginFunc 16 ;
	_tmp0 = 10 ;
	c = _tmp0 ;
	_tmp1 = 11 ;
	_tmp2 = c + _tmp1 ;
	c = _tmp2 ;
	PushParam c ;
	LCall _PrintInt ;
	PopParams 4 ;
	EndFunc ;
