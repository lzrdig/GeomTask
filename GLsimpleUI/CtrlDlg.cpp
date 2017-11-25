#include "stdafx.h"
#include "AppMain.h"
#include "DialogGLDlg.h"
#include "CtrlDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtrlDlg dialog

CCtrlDlg::CCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCtrlDlg::IDD, pParent)
	, m_dPoint3D_X(1.5)
	, m_dPoint3D_Y(1.5)
	, m_dPoint3D_Z(1.5)
	, m_dBottomX(0)
	, m_dBottomY(0)
	, m_dBottomZ(0)
	, m_dTopX(0)
	, m_dTopY(0)
	, m_dTopZ(1.0)
	, m_dBottomRadius(1.0)
	, m_dTopRadius(1.0)
	, m_nSlices(8)
	, m_nStacks(8)
{
	//{{AFX_DATA_INIT(CCtrlDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	m_hGLContext = NULL;
	m_GLPixelIndex = 0;

	m_size = 1.5;
	m_exp = 9;

	m_RightButtonDown = FALSE;
	m_LeftButtonDown = FALSE;

	Point3D bottomPt{ (float)m_dBottomX,(float)m_dBottomY,(float)m_dBottomZ };
	Point3D topPt{ (float)m_dTopX,(float)m_dTopY,(float)m_dTopZ };

	m_cylObj.setRadius(m_dBottomRadius);	
	m_cylObj.setBottomPt(bottomPt);
	m_cylObj.setTopPt(topPt);
}

void CCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCtrlDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_3DPOINT_X, m_dPoint3D_X);
	DDX_Text(pDX, IDC_3DPOINT_Y, m_dPoint3D_Y);
	DDX_Text(pDX, IDC_3DPOINT_Z, m_dPoint3D_Z);
	DDX_Text(pDX, IDC_BOTTOM_X, m_dBottomX);
	DDX_Text(pDX, IDC_BOTTOM_Y, m_dBottomY);
	DDX_Text(pDX, IDC_BOTTOM_Z, m_dBottomZ);
	DDX_Text(pDX, IDC_TOP_X, m_dTopX);
	DDX_Text(pDX, IDC_TOP_Y, m_dTopY);
	DDX_Text(pDX, IDC_TOP_Z, m_dTopZ);
	DDX_Text(pDX, IDC_BOTTOMRADIUS, m_dBottomRadius);
	DDX_Text(pDX, IDC_TOPRADIUS, m_dTopRadius);
	DDX_Text(pDX, IDC_NUMSLICES, m_nSlices);
	DDX_Text(pDX, IDC_NUMSTACKS, m_nStacks);
}

BEGIN_MESSAGE_MAP(CCtrlDlg, CDialog)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//ON_COMMAND(ID_POPUP_ROTATE, OnPopupRotate)
	//ON_COMMAND(ID_POPUP_SIZE_DECREASE, OnPopupSizeDecrease)
	//ON_COMMAND(ID_POPUP_SIZE_INCREASE, OnPopupSizeIncrease)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SHOWGL_BTN, &CCtrlDlg::OnBnClickedShowglBtn)
	ON_EN_CHANGE(IDC_BOTTOMRADIUS, &CCtrlDlg::OnEnChangeBottomradius)
	ON_EN_UPDATE(IDC_BOTTOMRADIUS, &CCtrlDlg::OnEnUpdateBottomradius)
	ON_BN_CLICKED(IDC_UPDATEGL_BTN, &CCtrlDlg::OnBnClickedUpdateglBtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtrlDlg message handlers

BOOL CCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

									// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting

		//SwapBuffers(dc.m_ps.hdc);
		CDialog::OnPaint();

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

int CCtrlDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CCtrlDlg::OnDestroy()
{
	CDialog::OnDestroy();
}

void CCtrlDlg::OnBnClickedShowglBtn()
{
	//try {
		if (&m_dlgGL != NULL)
		{
			if (!m_bGLwndCreated) {
				m_bGLwndCreated = m_dlgGL.Create(IDD_GLVIEW_DLG, NULL);
				m_dlgGL.m_pCtrlDlg = (CDialog*)this;
				m_bGLwndOpen = m_bGLwndCreated;
			}
			if (!m_bGLwndOpen) {
				m_dlgGL.ShowWindow(SW_SHOW);
				SendParamsToGLwnd();
				m_bGLwndOpen = true;
			}
			
		}		
	//}
	//catch(exception&){}
}

void CCtrlDlg::OnEnChangeBottomradius()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CCtrlDlg::OnEnUpdateBottomradius()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	if (&m_dlgGL != NULL)
	{
		//if (m_bGLwndOpen) {
		//	m_dlgGL.dBottomCenter = m_cylObj.getBottomCenter();
		//	m_dlgGL.dTopCenter = m_cylObj.getTopCenter();
		//	m_dlgGL.dBottomRadius = m_cylObj.getRadius();
		//	m_dlgGL.DrawCylinder();
		//	m_dlgGL.UpdateWindow();
		//}
	}
}

void CCtrlDlg::OnBnClickedUpdateglBtn()
{
	UpdateData(true);

	Point3D tmp{ 0.0f,0.0f,0.0f };

	tmp = { (float)m_dBottomX,(float)m_dBottomY,(float)m_dBottomZ };
	m_cylObj.setBottomPt(tmp);
	tmp = { (float)m_dTopX,(float)m_dTopY,(float)m_dTopZ };
	m_cylObj.setTopPt(tmp);
	m_cylObj.setRadius(m_dBottomRadius);

	if (&m_dlgGL != NULL)
	{
		if (m_bGLwndOpen) {
			SendParamsToGLwnd();
		}
	}
}

void CCtrlDlg::SendParamsToGLwnd()
{
	m_dlgGL.dBottomCenter = m_cylObj.getBottomCenter();
	m_dlgGL.dTopCenter = m_cylObj.getTopCenter();
	m_dlgGL.dBottomRadius = m_dBottomRadius;
	m_dlgGL.m_trgtPt.x = (float)m_dPoint3D_X;
	m_dlgGL.m_trgtPt.y = (float)m_dPoint3D_Y;
	m_dlgGL.m_trgtPt.z = (float)m_dPoint3D_Z;
	m_dlgGL.nSlices = m_nSlices;
	m_dlgGL.nStacks = m_nStacks;

	m_dlgGL.DrawScene();
	m_dlgGL.UpdateWindow();
}
