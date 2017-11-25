

// Pre-compiler instructions
#include "stdafx.h"
#include "PW2dMix.h"

#include "DecInclude.h"

#include "PW2dMixDoc.h"
#include "OglView.h"

#include "GLDemoView.h"

#include "../CylinderLIB/Cylinder.h"


#pragma warning(disable:4244)


using namespace std;
using namespace GeomTask;
using namespace OpenGLui;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


bool m_bStopBbopo;	// global variable for SetStop and GetStop


/////////////////////////////////////////////////////////////////////////////
// CPW2dMixView

IMPLEMENT_DYNCREATE(CPW2dMixView, CFormView)

BEGIN_MESSAGE_MAP(CPW2dMixView, CFormView)
	//{{AFX_MSG_MAP(CPW2dMixView)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)

	ON_EN_CHANGE(IDC_TOP_Y, OnChangePulseId)
	ON_EN_CHANGE(IDC_TOP_Z, OnChangePulsePump)
	ON_EN_CHANGE(IDC_TOP_X, OnChangePulseSig)

	ON_EN_SETFOCUS(IDC_TOP_Y, OnSetfocusPulseId)
	ON_EN_SETFOCUS(IDC_TOP_Z, OnSetfocusPulsePump)
	ON_EN_SETFOCUS(IDC_TOP_X, OnSetfocusPulseSig)

	ON_EN_SETFOCUS(IDC_3DPOINT_Z, OnSetfocus3dPtYpos)
	ON_EN_SETFOCUS(IDC_3DPOINT_Y, OnSetfocus3dPtZpos)
	ON_EN_SETFOCUS(IDC_3DPOINT_X, OnSetfocus3dPtXpos)

	ON_EN_CHANGE(IDC_3DPOINT_Y, OnChangeEnergyIdle)
	ON_EN_CHANGE(IDC_3DPOINT_X, OnChangeEnergySignal)
	ON_EN_CHANGE(IDC_3DPOINT_Z, OnChangeEnergyPump)

	ON_EN_SETFOCUS(IDC_BOTTOM_Z, OnSetfocusBeamdiamPump)
	ON_EN_SETFOCUS(IDC_BOTTOM_Y, OnSetfocusBeamdiamId)
	ON_EN_SETFOCUS(IDC_BOTTOM_X, OnSetfocusBeamdiamSig)

	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP

	ON_EN_SETFOCUS(IDC_BOTTOMRADIUS, &CPW2dMixView::OnEnSetfocusRadius)
	ON_EN_CHANGE(IDC_BOTTOMRADIUS, &CPW2dMixView::OnEnChangeRadius)
	ON_EN_SETFOCUS(IDC_NUMSLICES, &CPW2dMixView::OnEnSetfocusNumslices)
	ON_EN_SETFOCUS(IDC_NUMSTACKS, &CPW2dMixView::OnEnSetfocusNumstacks)
	ON_BN_CLICKED(IDC_CALCULATE, &CPW2dMixView::OnBnClickedCalculate)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPW2dMixView construction/destruction

CPW2dMixView::CPW2dMixView()
	: CFormView(CPW2dMixView::IDD)
	, m_BottomRadius(0)
	, m_TopRadius(0)
	, m_nSlices(0)
	, m_nStacks(0)
	, m_sCalcDistance(_T(""))
	, m_dEndPtX(0)
	, m_dEndPtY(0)
	, m_dEndPtZ(0)
	, m_bBox(TRUE)
	, m_bAxis(TRUE)
	, m_sMapType(_T("Grid"))
{
	//{{AFX_DATA_INIT(CPW2dMixView)
	m_Bottom_Y = 0.0;
	m_Bottom_Z = 0.0;
	m_Bottom_X = 0.0;

	m_Top_Y = 0.0;
	m_Top_Z = 0.0;
	m_Top_X = 0.0;

	m_Point3D_Y = 0.0;
	m_Point3D_Z = 0.0;
	m_Point3D_X = 0.0;
	//}}AFX_DATA_INIT
}

CPW2dMixView::~CPW2dMixView()
{
}

void CPW2dMixView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPW2dMixView)
	DDX_Control(pDX, IDC_PROG_RUN, m_cProgRun);

	DDX_Text(pDX, IDC_BOTTOM_Y, m_Bottom_Y);
	DDX_Text(pDX, IDC_BOTTOM_Z, m_Bottom_Z);
	DDX_Text(pDX, IDC_BOTTOM_X, m_Bottom_X);

	DDX_Text(pDX, IDC_TOP_Y, m_Top_Y);
	DDX_Text(pDX, IDC_TOP_Z, m_Top_Z);
	DDX_Text(pDX, IDC_TOP_X, m_Top_X);

	DDX_Text(pDX, IDC_3DPOINT_Y, m_Point3D_Y);
	DDX_Text(pDX, IDC_3DPOINT_Z, m_Point3D_Z);
	DDX_Text(pDX, IDC_3DPOINT_X, m_Point3D_X);

	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_BOTTOMRADIUS, m_BottomRadius);
	DDX_Text(pDX, IDC_TOPRADIUS, m_TopRadius);
	DDX_Text(pDX, IDC_NUMSLICES, m_nSlices);
	DDX_Text(pDX, IDC_NUMSTACKS, m_nStacks);
	DDX_Text(pDX, IDC_CALCRESULT, m_sCalcDistance);
	DDX_Text(pDX, IDC_ENDPT_X, m_dEndPtX);
	DDX_Text(pDX, IDC_ENDPT_Y, m_dEndPtY);
	DDX_Text(pDX, IDC_ENDPT_Z, m_dEndPtZ);
	DDX_Check(pDX, IDC_BOX, m_bBox);
	DDX_Check(pDX, IDC_AXIS, m_bAxis);
	DDX_CBString(pDX, IDC_COMBO1, m_sMapType);
}



/////////////////////////////////////////////////////////////////////////////
// CPW2dMixView diagnostics

#ifdef _DEBUG
void CPW2dMixView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPW2dMixView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPW2dMixDoc* CPW2dMixView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPW2dMixDoc)));
	return (CPW2dMixDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPW2dMixView message handlers

void CPW2dMixView::OnInitialUpdate() 
{

	// Resize the main frame to fit the size of the dialog area
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit(false);


	// Set dialog boxes to their corresponding values

	m_Point3D_X = 0.0;
	m_Point3D_Y = 0.2;
	m_Point3D_Z = 0.0;

	m_Bottom_X = 0.0;
	m_Bottom_Y = 0.0;
	m_Bottom_Z = 0.0;

	m_Top_X = 0.0;
	m_Top_Y = 0.0;
	m_Top_Z = 0.5;

	m_BottomRadius = 0.1;
	m_TopRadius = 0.1;

	m_nSlices = 16;
	m_nStacks = 16;

	// Initially disable the buttons
	SetEnableBtns(false);

	CFormView::OnInitialUpdate();

	CreatePlotWnd();

}	// End OnInitialUpdate


HBRUSH CPW2dMixView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// Set the text colors for Signal,Idler, and Pump in the dialog box
	if(pWnd->GetDlgCtrlID() == IDC_TEXT_SIGNAL)
		pDC->SetTextColor(RGB(255,0,0));
	if(pWnd->GetDlgCtrlID() == IDC_TEXT_IDLER)
		pDC->SetTextColor(RGB(0,0,255));
	if(pWnd->GetDlgCtrlID() == IDC_TEXT_PUMP)
		pDC->SetTextColor(RGB(0,100,0));

	return hbr;

}	// End OnCtlColor


//***************************************************************************
// Refresh Button is used to kick off the drawing of the scene
//
//*************************************************************************** 
void CPW2dMixView::OnRefresh() 
{
	// Set the text box to 'Stop' or 'Run', depending on the current status 
	CString str; 
	GetDlgItemText(IDC_REFRESH, str);

	
	// Update form's data
	//UpdateData();

	// Test for errors on the input form
	bool Error = TestForErrors();
	if(Error)
	{
		SetDlgItemText(IDC_REFRESH,"Run");
		return;
	}

	// Disable the other buttons
	SetEnableBtns(false);

	// Set the flags for Spectrum and Intensity to false
	m_bSpectrum = false;
	m_bIntensity = false;

	// Set the normalization variables to zero
	m_SpNorm_s    = 0.0;
	m_SpNorm_i    = 0.0;
	m_SpNorm_p    = 0.0;
	m_IntNorm_max = 0.0;

	SetDlgItemText(IDC_HELPBOX,"Initializing...");

	SetDlgItemText(IDC_REFRESH, "Refreshing");

	BeginWaitCursor();

	//Sleep(1000);

	// Plot it in the GL window if it is open
	CPW2dMixApp* theApp = (CPW2dMixApp*)AfxGetApp();
	CFrameWnd* pPlot = theApp->pPlotWnd;
	if (pPlot)
	{
		CGLDemoView* theView = (CGLDemoView*)pPlot->GetActiveView();

		OpenGLui::Point3D dBottomPt{0, 0, 0};
		OpenGLui::Point3D dTopPt{0, 0, 1.0f};
		double dBottomRadius = 0.0f;
		double dTopRadius = 0.0f;
		int nSlices, nStacks;
		OpenGLui::Point3D dTestPt{ 0, 0, 3.0f };

		CString val = "";

		GetDlgItemText(IDC_BOTTOM_Y, val);
		dBottomPt.y = atof(val);
		GetDlgItemText(IDC_BOTTOM_Z, val);
		dBottomPt.z = atof(val);
		GetDlgItemText(IDC_BOTTOM_X, val);
		dBottomPt.x = atof(val);

		GetDlgItemText(IDC_TOP_Y, val);
		dTopPt.y = atof(val);
		GetDlgItemText(IDC_TOP_Z, val);
		dTopPt.z = atof(val);
		GetDlgItemText(IDC_TOP_X, val);
		dTopPt.x = atof(val);

		GetDlgItemText(IDC_BOTTOMRADIUS, val);
		dBottomRadius = atof(val);
		GetDlgItemText(IDC_TOPRADIUS, val);
		dTopRadius = atof(val);

		GetDlgItemText(IDC_NUMSLICES, val);
		nSlices = atoi(val);
		GetDlgItemText(IDC_NUMSTACKS, val);
		nStacks = atoi(val);

		GetDlgItemText(IDC_3DPOINT_Y, val);
		dTestPt.y = atof(val);
		GetDlgItemText(IDC_3DPOINT_Z, val);
		dTestPt.z = atof(val);
		GetDlgItemText(IDC_3DPOINT_X, val);
		dTestPt.x = atof(val);

		UpdateData();

		theView->m_bAxis = m_bAxis;
		theView->m_bBox = m_bBox;
		theView->m_sMapType = m_sMapType;

		OpenGLui::Point3D dFoundPt{(float)m_dEndPtX, (float)m_dEndPtY, (float)m_dEndPtZ};
		theView->SetupScene(dBottomPt, dTopPt, dBottomRadius, dTopRadius, m_nSlices, m_nStacks, dTestPt, dFoundPt);

		theView->InvalidateRect(NULL);
	}

	EndWaitCursor();


	// Enable the buttons
	SetEnableBtns(TRUE);


	SetDlgItemText(IDC_REFRESH,str);


	SetDlgItemText(IDC_HELPBOX,"Done.");

}	// End OnRefresh

//***************************************************************************
// Calculate Button is used to calculate the distance from the test point
// to the nearest point on the cylinder surface
//***************************************************************************
void CPW2dMixView::OnBnClickedCalculate()
{
	Cylinder* cylObj;
	
	UpdateData(true);

	GeomTask::Point3D tstPt{ m_Point3D_X,m_Point3D_Y,m_Point3D_Z };
	GeomTask::Point3D bottomPt{ m_Bottom_X, m_Bottom_Y,m_Bottom_Z };
	GeomTask::Point3D topPt{ m_Top_X, m_Top_Y,m_Top_Z };

	cylObj = new Cylinder(m_BottomRadius, bottomPt, topPt);

	double distance = cylObj->DistanceFromPtToCyl(tstPt);

	m_sCalcDistance.Format("%5.2f", distance);
	m_dEndPtX = cylObj->GetFoundPt().x;
	m_dEndPtY = cylObj->GetFoundPt().y;
	m_dEndPtZ = cylObj->GetFoundPt().z;

	UpdateData(false);

	OnRefresh();

	delete cylObj;
}

//***************************************************************************
//
// TestForErrors will verify that the input parameters are valid
// for running the program
// 
//***************************************************************************
bool CPW2dMixView::TestForErrors()
{

//***************************************************************************
// Test for negative input values

	//if(m_Deff < 0)
	//{
	//	SetDlgItemText(IDC_HELPBOX,"ERROR: Deff must be greater than or equal to zero.");
	//	return true;
	//}
	//else if(m_Deltak < 0)
	//{
	//	SetDlgItemText(IDC_HELPBOX,"ERROR: Deltak must be greater than or equal to zero.");
	//	return true;
	//}
	//else return false;




// Default return value
	return false;
}

//***************************************************************************
//
// SetEnableBtns will enable or disable the Spectra, Irradiance
// and Print buttons.  It will also disable the scrollbar and 
// zoom buttons if bEnableBtns = false.
//
// SetEnableBtns is called in the OnChange function for each 
// edit control so that another case must be run if any of the 
// variables are changed.
//
//***************************************************************************
void CPW2dMixView::SetEnableBtns(bool bEnableBtns)
{
	//GetDlgItem(IDC_INTENSITY)->EnableWindow(bEnableBtns);	
	bEnableBtns = true;
}


// ************ Event Handlers for edit controls ********************

void CPW2dMixView::OnChangeEnergyIdle() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangeEnergySignal() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangeEnergyPump() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangeBeamdiamId() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangeBeamdiamPump() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangeBeamdiamSig() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangePulseId() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangePulsePump() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnChangePulseSig() 
{
	SetEnableBtns(FALSE);
}

void CPW2dMixView::OnEnChangeRadius()
{

}

//***************************************************************************
// 
// OnSetfocus is called for each edit control in order to display
// help text in the edit box IDC_HELPBOX for each of the different
// variables.
//
//***************************************************************************

void CPW2dMixView::OnSetfocus3dPtXpos() 
{
	CString str = CString("X coordinate of the 3D point");
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnSetfocus3dPtYpos() 
{
	CString str = CString("Y coordinate of the 3D point") ;
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnSetfocus3dPtZpos() 
{
	CString str = CString("Z coordinate of the 3D point");
	SetDlgItemText(IDC_HELPBOX, str);
}

void CPW2dMixView::OnSetfocusBeamdiamId() 
{
	CString str = "Bottom center point coordinate X.";
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnSetfocusBeamdiamPump() 
{
	CString str = "Bottom center point coordinate Y.";
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnSetfocusBeamdiamSig() 
{
	CString str = "Bottom center point coordinate Z.";
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnSetfocusPulseId() 
{
	CString str = "Top center point coordinate X.";
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnSetfocusPulsePump() 
{
	CString str = "Top center point coordinate Y.";
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnSetfocusPulseSig() 
{
	CString str = "Top center point coordinate Z.";
	SetDlgItemText(IDC_HELPBOX,str);
}

void CPW2dMixView::OnEnSetfocusRadius()
{
	CString str = "The radius value for the cylinder's base circle/disk.";
	SetDlgItemText(IDC_HELPBOX, str);
}

void CPW2dMixView::OnEnSetfocusNumslices()
{
	CString str = "Specify number of slices to be used when drawing the cylinder (it does not affect the calculation).";
	SetDlgItemText(IDC_HELPBOX, str);
}

void CPW2dMixView::OnEnSetfocusNumstacks()
{
	CString str = "Specify number of stacks to be used when drawing the cylinder (it does not affect the calculation).";
	SetDlgItemText(IDC_HELPBOX, str);
}

// ************ End of Event Handlers ********************


bool CPW2dMixView::CreatePlotWnd()
{
	//********** Create a GL type of plot window *************
	// Create GL window's context with the view
	CCreateContext GLcontext;
	GLcontext.m_pNewViewClass = RUNTIME_CLASS(CGLDemoView);

	// Create window's frame and attach the view to it
	CFrameWnd* pPlotWnd = new CFrameWnd;

	// set the pointer to the current frame
	GLcontext.m_pCurrentFrame = pPlotWnd;
	
	// set the size of the window
	CRect rect(290,10, 740, 400);
	// create the window itself
	pPlotWnd->Create(NULL, "Chart", WS_CHILD, rect, this);
	// create the view and attach it to the frame
	CWnd* pView = pPlotWnd->CreateView(&GLcontext);
	pPlotWnd->SetActiveView((CView*) pView);

	// set the application's pointer to the plot window
	// in order to find the window from anywhere in the application
	CPW2dMixApp* theMixApp = (CPW2dMixApp*)AfxGetApp();
	theMixApp->pPlotWnd = pPlotWnd;

	pPlotWnd->ShowWindow(SW_SHOW);
	pPlotWnd->UpdateWindow();

	//********************************
	// Create the main toolbar	
	if (!m_wndToolBar.Create(pPlotWnd, WS_CHILD | WS_VISIBLE| CBRS_BOTTOM 
										| CBRS_TOOLTIPS | CBRS_FLYBY ) 
		||	!m_wndToolBar.LoadToolBar(IDR_VIEW_CONTROL))
	{
		TRACE0("Failed to create toolbar\n");
		AfxMessageBox("Failed to create a toolbar");      // fail to create
	}
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	pPlotWnd->EnableDocking(CBRS_ALIGN_ANY);
	pPlotWnd->DockControlBar(&m_wndToolBar);


	//*********************************************************

	return true;

}


