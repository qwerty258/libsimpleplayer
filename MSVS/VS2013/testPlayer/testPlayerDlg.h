
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
    float m_handle1_percentage;
    afx_msg void OnClickedButtonHandle1Play();
    afx_msg void OnClickedButtonHandle1Pause();
    afx_msg void OnClickedButtonHandle1Stop();
    afx_msg void OnClickedButtonHandle1SetSpeed();
    afx_msg void OnClickedButtonHandle1GetPercentage();
    afx_msg void OnClickedButtonHandle1SetPercentage();
};
