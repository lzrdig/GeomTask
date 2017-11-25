
//***************************************************************************
//
// GlobalVar.h - Header for class CGlobalVar
//
//***************************************************************************

 
// Pre-compiler instructions
#ifndef GLOBALVAR_H


//***************************************************************************
// List of 'array' arguments for class CGlobalVar

const int DT = 10044;
const int TMIN = 10045;
const int TMAX = 10046;
const int VFAST = 10047;
const int VSLOW = 10048;
const int NGRID = 10049;
const int NBUFFER = 10050;
const int OMEGA_S = 10051;
const int OMEGA_I = 10052;
const int OMEGA_P = 10053;
const int I_TERM = 10054;
const int PEAKPOW_S = 10055;
const int PEAKPOW_I = 10056;
const int PEAKPOW_P = 10057;
const int PEAKIR_S = 10058;
const int PEAKIR_I = 10059;
const int PEAKIR_P = 10060;
const int PEAKFL_S = 10061;
const int PEAKFL_I = 10062;
const int PEAKFL_P = 10063;
const int IROUT_S = 10064;
const int IROUT_I = 10065;
const int IROUT_P = 10066;
const int EPULSE_S = 10067;
const int EPULSE_I = 10068;
const int EPULSE_P = 10069;
const int NTGRID = 10070;



//***************************************************************************
// Definition of class CGlobalVar

class CGlobalVar
{
public:

// Class constructor 
	CGlobalVar(){};

// Class destructor
	~CGlobalVar(){};

// Member functions
	void	dSetGlobal(int array, double val);
	void	lSetGlobal(int array, long val);
	double	dGetGlobal(int array);
	long	lGetGlobal(int array);
	

// Class variables
private:
	double m_Dt;			// Time step [sec]
	double m_Tmin, m_Tmax;	// Minimum and maximum times
		
	double m_vfast,m_vslow;		// Fast and slow waves (gvi)
			
	double m_omega_s,m_omega_i,m_omega_p;	// frequencies (rad/s)
	double m_I_term;						// term for intensities
	double m_peakPow_s, m_peakPow_i, m_peakPow_p;	// peak power [W]
	double m_peakIr_s, m_peakIr_i, m_peakIr_p;		// peak irradiance [J/m^2]
	double m_peakFl_s, m_peakFl_i, m_peakFl_p;		// peak fluence [W/m^2]
	double m_IrOut_s, m_IrOut_i, m_IrOut_p;			// output peak irradiance [J/m^2]
	double m_Epulse_s, m_Epulse_i, m_Epulse_p;		// output pulse energy [J]

	long m_Ntot;			// 6*Ngrid
	long m_Ngrid;			// Total number of FFT grid points
	long m_Ntotal;			// Total number of time points over all pulses (3*nt)
	long m_Nbuffer;			// Total number of buffer points
	long m_Nt;				// Number of time points over a pulse
};


#define GLOBALVAR_H
#endif