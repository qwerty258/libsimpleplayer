
// testPlayerDlg.h : header file
//

#pragma once

#include <libSimplePlayer.h>

// CtestPlayerDlg dialog
class CtestPlayerDlg : public CDialogEx
{
    // Construction
public:
    CtestPlayerDlg(CWnd* pParent = NULL);	// standard constructor

    // Dialog Data
    enum
    {
        IDD = IDD_TESTPLAYER_DIALOG
    };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL DestroyWindow();
    uint32_t m_play_handle1;
    float m_handle1_speed;
    afx_msg void OnClickedButtonPlay();
    afx_msg void OnClickedButtonPause();
    afx_msg void OnClickedButtonStop();
    afx_msg void OnClickedButtonSetSpeed();
};
