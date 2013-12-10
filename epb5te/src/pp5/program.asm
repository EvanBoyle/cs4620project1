Base_hi:
	BeginFunc 4 ;
	_tmp0 = 1 ;
	PushParam _tmp0 ;
	LCall _PrintInt ;
	PopParams 4 ;
	PushParam _tmp0 ;
	LCall _PrintInt ;
	PopParams 4 ;
	EndFunc ;
VTable Base =
	Base_hi,
; 
Derived_hi:
	BeginFunc 4 ;
	_tmp1 = 2 ;
	PushParam _tmp1 ;
	LCall _PrintInt ;
	PopParams 4 ;
	PushParam _tmp1 ;
	LCall _PrintInt ;
	PopParams 4 ;
	EndFunc ;
VTable Derived =
	Derived_hi,
; 
main:
	BeginFunc 16 ;
	_tmp2 = 4 ;
	PushParam _tmp2 ;
	_tmp3 = LCall _Alloc ;
	PopParams 4 ;
	_tmp4 = Base ;
	*(_tmp3) = _tmp4 ;
	b = _tmp3 ;
	EndFunc ;
