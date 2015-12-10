
// testPlayerDlg.h : header file
//

#pragma once

#include <libSimplePlayer.h>
#include "CStringToChar.h"

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
    uint32_t m_play_handle2;
    float m_handle1_percentage;
    float m_handle1_speed;
    float m_handle2_percentage;
    float m_handle2_speed;
    CString m_handle1_filepath;
    CString m_handle2_filepath;
    CString m_handle1_snapshot_path;
    CString m_handle2_snapshot_path;
    afx_msg void OnClickedButtonHandle1Play();
    afx_msg void OnClickedButtonHandle1Pause();
    afx_msg void OnClickedButtonHandle1Stop();
    afx_msg void OnClickedButtonHandle1SetSpeed();
    afx_msg void OnClickedButtonHandle1GetPercentage();
    afx_msg void OnClickedButtonHandle1SetPercentage();
    afx_msg void OnClickedButtonHandle1TakeSnapshot();
    afx_msg void OnClickedButtonHandle2Play();
    afx_msg void OnClickedButtonHandle2Pause();
    afx_msg void OnClickedButtonHandle2Stop();
    afx_msg void OnClickedButtonHandle2SetSpeed();
    afx_msg void OnClickedButtonHandle2GetPercentage();
    afx_msg void OnClickedButtonHandle2SetPercentage();
    afx_msg void OnClickedButtonHandle2TakeSnapshot();
    afx_msg void OnClickedButtonHandle1Apply();
    afx_msg void OnClickedButtonHandle2Apply();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
