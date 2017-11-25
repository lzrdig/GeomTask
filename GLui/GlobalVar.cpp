
//***************************************************************************
//
// Class CGlobalVar
//
// List of member functions:
//
//  * dSetGlobal(int array, double val)
//
//         Sets the value of the 'array' argument to the type double 'val'.
//
//      Example:  pGlobalVar->dSetGlobal(NOISEBANDWIDTH,14.2) sets the value
//                              of 'Noisebandwidth' = 14.2
//
//  * lSetGlobal(int array, long val)
//
//         Same as above, only for type long 'val'.
//
//      Example:  pGlobalVar->lSetGlobal(NBUFFER,40) sets 'Nbuffer' = 40
//
//
//  * cSetGlobal(int array, float rval, float ival)
//
//         Same as above, but for type complex (real = 'rval', imag = 'ival')
//
//      Example:  pGlobalVar->cSetGlobal(PHASESHIFT_S,5.6,8.7) sets 
//								'Phaseshift_s' to Real = 5.6, Imag = 8.7 
//
//  *  dGetGlobal(int array)
//
//          Returns the type double value for the variable 'array'
//
//       Example:  pGlobalVar->dGetGlobal(VFAST) returns the value for 'vfast'
//
//
//  *  lGetGlobal(int array)
//
//          Same as above, but for type long.
//
//       Example:  pGlobalVar->lGetGlobal(NGRID) returns the value for 'ngrid'
//
//
//  *  cGetGlobal(int array,int r_or_i)
//
//          Same as above, but for type complex. Returns values for either
//          real or imaginary part, but not both.  
//          (Note: r_or_i = REAL or IMAG, defined in 'DecInclude.h')
//
//       Example:  pGlobalVar->cGetGlobal(IDSHIFT,REAL) returns real part of
//                               variable 'Idshift'
//
//       Example:  pGlobalVar->cGetGlobal(PUMPSHIFT,IMAG) returns imaginary
//                               part of 'Pumpshift'
//
//
//  (Note: for a complete list of the 'array' arguments, see 'GlobalVar.h')
//
//***************************************************************************


// Pre-compiler instructions
#include "StdAfx.h"
#include "DecInclude.h"
#include "GlobalVar.h"


//***************************************************************************
// Function dSetGlobal
 
void CGlobalVar::dSetGlobal(int array, double val)
{
	switch (array)
	{
	case DT:
		m_Dt = val;
		break;
	case TMIN:
		m_Tmin = val;
		break;
	case TMAX:
		m_Tmax = val;
		break;
	case VFAST:
		m_vfast = val;
		break;
	case VSLOW:
		m_vslow = val;
		break;
	case OMEGA_S:
		m_omega_s = val;
		break;
	case OMEGA_I:
		m_omega_i = val;
		break;
	case OMEGA_P:
		m_omega_p = val;
		break;
	case I_TERM:
		m_I_term = val;
		break;
	case PEAKPOW_S:
		m_peakPow_s = val;
		break;
	case PEAKPOW_I:
		m_peakPow_i = val;
		break;
	case PEAKPOW_P:
		m_peakPow_p = val;
		break;
	case PEAKIR_S:
		m_peakIr_s = val;
		break;
	case PEAKIR_I:
		m_peakIr_i = val;
		break;
	case PEAKIR_P:
		m_peakIr_p = val;
		break;
	case PEAKFL_S:
		m_peakFl_s = val;
		break;
	case PEAKFL_I:
		m_peakFl_i = val;
		break;
	case PEAKFL_P:
		m_peakFl_p = val;
		break;
	case IROUT_S:
		m_IrOut_s = val;
		break;
	case IROUT_I:
		m_IrOut_i = val;
		break;
	case IROUT_P:
		m_IrOut_p = val;
		break;
	case EPULSE_S:
		m_Epulse_s = val;
		break;
	case EPULSE_I:
		m_Epulse_i = val;
		break;
	case EPULSE_P:
		m_Epulse_p = val;
		break;
	default:
		break;
	}	

}


//***************************************************************************
// Function lSetGlobal 

void CGlobalVar::lSetGlobal(int array, long val)
{
	switch(array)
	{
	case NGRID:
		m_Ngrid = val;
		break;
	case NBUFFER:
		m_Nbuffer = val;
		break;
	case NTGRID:
		m_Nt = val;
		break;
	default:
		break;
	}
}

//***************************************************************************
// Function dGetGlobal 

double CGlobalVar::dGetGlobal(int array)
{

	switch (array)
	{
	case DT:
		return m_Dt;
		break;
	case TMIN:
		return m_Tmin;
		break;
	case TMAX:
		return m_Tmax;
		break;
	case VFAST:
		return m_vfast;
		break;
	case VSLOW:
		return m_vslow;
		break;
	case OMEGA_S:
		return m_omega_s;
		break;
	case OMEGA_I:
		return m_omega_i;
		break;
	case OMEGA_P:
		return m_omega_p;
		break;
	case I_TERM:
		return m_I_term;
		break;
	case PEAKPOW_S:
		return m_peakPow_s;
		break;
	case PEAKPOW_I:
		return m_peakPow_i;
		break;
	case PEAKPOW_P:
		return m_peakPow_p;
		break;
	case PEAKIR_S:
		return m_peakIr_s;
		break;
	case PEAKIR_I:
		return m_peakIr_i;
		break;
	case PEAKIR_P:
		return m_peakIr_p;
		break;
	case PEAKFL_S:
		return m_peakFl_s;
		break;
	case PEAKFL_I:
		return m_peakFl_i;
		break;
	case PEAKFL_P:
		return m_peakFl_p;
		break;
	case IROUT_S:
		return m_IrOut_s;
		break;
	case IROUT_I:
		return m_IrOut_i;
		break;
	case IROUT_P:
		return m_IrOut_p;
		break;
	case EPULSE_S:
		return m_Epulse_s;
		break;
	case EPULSE_I:
		return m_Epulse_i;
		break;
	case EPULSE_P:
		return m_Epulse_p;
		break;
	default:
		return 0.0;
		break;
	}	
}


//***************************************************************************
// Function lGetGlobal 

long CGlobalVar::lGetGlobal(int array)
{
	switch (array)
	{
	case NGRID:
		return m_Ngrid;
		break;
	case NBUFFER:
		return m_Nbuffer;
		break;
	case NTGRID:
		return m_Nt;
		break;
	default:
		return 0;
		break;
	}	
}





