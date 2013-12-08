main:
	BeginFunc 32 ;
	_tmp0 = 10 ;
	c = _tmp0 ;
	_tmp1 = -1 ;
	_tmp2 = _tmp1 * c ;
	_tmp3 = 25 ;
	_tmp4 = _tmp2 + _tmp3 ;
	_tmp5 = 3 ;
	_tmp6 = _tmp4 / _tmp5 ;
	c = _tmp6 ;
	PushParam c ;
	LCall _PrintInt ;
	PopParams 4 ;
	EndFunc ;
