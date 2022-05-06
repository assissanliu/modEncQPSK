#include "StdAfx.h"
#include "Algorithm.h"
#include "Innovations.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CAlgorithm, CDialog)

CAlgorithm::CAlgorithm(CWnd* pParent /*=NULL*/)
           : CDialog(IDD_DIALOG1, pParent)
{
}

CAlgorithm::~CAlgorithm()
{
}

void CAlgorithm::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlgorithm, CDialog)
    ON_BN_CLICKED(IDOK, &CAlgorithm::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CAlgorithm::OnBnClickedCancel)
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

void CAlgorithm::Reset(const float *InitParam)
{
    //初始化处理
    m_InputBuf.resize(0);
    m_OutputBuf1.resize(0);
    m_OutputBuf2.resize(0);
}

//QPSK调制映射
void CAlgorithm::RunAlgorithm(const float *InitParam, const float *pdInput, const int InputSize,
                             int& OutputSize, float& OutputRate, float **pdOutput1, float **pdOutput2)
{
    //输入信号速率
    float    inputRate = InitParam[0];

    //数据填充
    for (int idx = 0;idx<InputSize;idx++)
        m_InputBuf.push_back((pdInput[idx]>0.5f) ? -1 : 1);

    //调制映射参数调整
    OutputSize = int(m_InputBuf.size()/QM);
    int vInputLen = OutputSize*QM;
    OutputRate = inputRate/QM;

    //分配空间
    vector<int>    dat_ip(vInputLen);
    vector<double> dat_opi(OutputSize);
    vector<double> dat_opq(OutputSize);
    //获取数据
    dat_ip.assign(m_InputBuf.begin(), m_InputBuf.begin() + vInputLen);
    //输入缓存数据删除
    m_InputBuf.erase(m_InputBuf.begin(), m_InputBuf.begin() + vInputLen);
    //调制映射
    encQPSK(&dat_ip[0], &dat_opi[0], &dat_opq[0], OutputSize);
    //输出端口
    m_OutputBuf1.resize(OutputSize);
    m_OutputBuf2.resize(OutputSize);
    for (int jdx = 0;jdx<OutputSize;jdx++)
    {
        m_OutputBuf1[jdx] = float(dat_opi[jdx]);
        m_OutputBuf2[jdx] = float(dat_opq[jdx]);
    }
    //释放空间
    dat_opi.clear();
    dat_opq.clear();
    //端口分配
    if (OutputSize > 0)
    {
        *pdOutput1 = &m_OutputBuf1[0];
        *pdOutput2 = &m_OutputBuf2[0];
    }
}

void CAlgorithm::encQPSK(const int* pInNRZ, double* pOutI, double* pOutQ, int outLen) const
{
    for (int i = 0; i< outLen; ++i)
    {
        const int* pRef = &pInNRZ[2 * i];
        const int pos = 2 - pRef[0] - ((pRef[1] + 1) >> 1);
        assert(pos >= 0 && pos<4);
        pOutI[i] = invSQRT2*MAP_TAB_I[pos];
        pOutQ[i] = invSQRT2*MAP_TAB_Q[pos];
    }
}

//界面控制
void CAlgorithm::OnBnClickedOk()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnBnClickedCancel()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnEnChangeEdit()
{
    ShowWindow(SW_HIDE);
}

void CAlgorithm::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);
    if (bShow)
    {
        CString value2str;
    }
}

BOOL CAlgorithm::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}
