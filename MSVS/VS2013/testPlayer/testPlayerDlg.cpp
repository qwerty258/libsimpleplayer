
// testPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testPlayer.h"
#include "testPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestPlayerDlg dialog



CtestPlayerDlg::CtestPlayerDlg(CWnd* pParent /*=NULL*/)
    :CDialogEx(CtestPlayerDlg::IDD, pParent),
    m_handle1_speed(0),
    m_handle1_percentage(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_HANDLE1_SPEED, m_handle1_speed);
    DDX_Text(pDX, IDC_EDIT_HANDLE1_PERCENTAGE, m_handle1_percentage);
}

BEGIN_MESSAGE_MAP(CtestPlayerDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_HANDLE1_PLAY, &CtestPlayerDlg::OnClickedButtonHandle1Play)
    ON_BN_CLICKED(IDC_BUTTON_HANDLE1_PAUSE, &CtestPlayerDlg::OnClickedButtonHandle1Pause)
    ON_BN_CLICKED(IDC_BUTTON_HANDLE1_STOP, &CtestPlayerDlg::OnClickedButtonHandle1Stop)
    ON_BN_CLICKED(IDC_BUTTON_HANDLE1_SET_SPEED, &CtestPlayerDlg::OnClickedButtonHandle1SetSpeed)
    ON_BN_CLICKED(IDC_BUTTON_HANDLE1_GET_PERCENTAGE, &CtestPlayerDlg::OnClickedButtonHandle1GetPercentage)
    ON_BN_CLICKED(IDC_BUTTON_HANDLE1_SET_PERCENTAGE, &CtestPlayerDlg::OnClickedButtonHandle1SetPercentage)
END_MESSAGE_MAP()


// CtestPlayerDlg message handlers

BOOL CtestPlayerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here
    m_handle1_speed = 1.0;
    UpdateData(FALSE);
    LSP_initial();
    LSP_get_idle_handle(&m_play_handle1);
    LSP_set_filepath(m_play_handle1, "E:\\C#FundamentalsForAbsoluteBeginnersM01_high.mp4");
    LSP_set_hwnd(m_play_handle1, GetDlgItem(IDC_PICTURE_AREA)->m_hWnd);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CtestPlayerDlg::OnPaint()
{
    if(IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CtestPlayerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



BOOL CtestPlayerDlg::DestroyWindow()
{
    // TODO: Add your specialized code here and/or call the base class
    LSP_uninitial();
    return CDialogEx::DestroyWindow();
}


void CtestPlayerDlg::OnClickedButtonHandle1Play()
{
    // TODO: Add your control notification handler code here
    LSP_play(m_play_handle1);
}


void CtestPlayerDlg::OnClickedButtonHandle1Pause()
{
    // TODO: Add your control notification handler code here
    LSP_pause(m_play_handle1);
}


void CtestPlayerDlg::OnClickedButtonHandle1Stop()
{
    // TODO: Add your control notification handler code here
    LSP_stop(m_play_handle1);
}


void CtestPlayerDlg::OnClickedButtonHandle1SetSpeed()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    LSP_set_speed(m_play_handle1, m_handle1_speed);
}


void CtestPlayerDlg::OnClickedButtonHandle1GetPercentage()
{
    // TODO: Add your control notification handler code here
    LSP_get_playing_percentage(m_play_handle1, &m_handle1_percentage);
    UpdateData(FALSE);
}


void CtestPlayerDlg::OnClickedButtonHandle1SetPercentage()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    LSP_set_playing_percentage(m_play_handle1, m_handle1_percentage);
}
