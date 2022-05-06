#pragma once

#define QM 2
const double invSQRT2 = 0.70710678118654752440084436210485;
//码元与相角对应关系 11-(pi/4),10-(-pi/4),01-(3pi/4),00-(-3pi/4)
//{1, 1}, { 1,-1 }, { -1, 1 }, { -1,-1 },
const int MAP_TAB_I[4] = { 1, 1,-1, -1};
const int MAP_TAB_Q[4] = { 1,-1, 1, -1};

class CAlgorithm : public CDialog
{
    DECLARE_DYNAMIC(CAlgorithm)

public:
    CAlgorithm(CWnd* pParent = NULL);   // 标准构造函数
    virtual ~CAlgorithm();

    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnEnChangeEdit();
    virtual BOOL OnInitDialog();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum {  IDD = IDD_DIALOG1 };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

public:
    void Reset(const float *InitParam);
    void RunAlgorithm(const float *InitParam, const float *pdInput, const int InputSize,
                      int& OutputSize, float& OutputRate, float **pdOutput1, float **pdOutput2);

private:
    //输入数据缓存
    vector<int> m_InputBuf;
    //输出数据缓存
    vector<float> m_OutputBuf1;
    vector<float> m_OutputBuf2;
    //映射主函数
    void encQPSK(const int* pInNRZ, double* pOutI, double* pOutQ, int outLen) const;
};
