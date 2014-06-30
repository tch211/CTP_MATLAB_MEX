#ifndef FUNCTION_CALL_BACK_H
#define FUNCTION_CALL_BACK_H

#include "CTPStruct.h"
#include "ThostTraderApi\ThostFtdcUserApiStruct.h"
#include "CLock.h"
#include <list>
#include <Windows.h>
#include <map>
using namespace std;
class FunctionCallBackSet
{

    
public:
    static bool bIsGetInst;
    
    static CRITICAL_SECTION f_csInstrument;
    static list<string> lstAllInstruments;
    static string strAllIns;
    
    static HANDLE h_connected;
    
    static CRITICAL_SECTION m_csInstPrice;
    static map<string, CThostFtdcDepthMarketDataField> m_instPrice;
    FunctionCallBackSet()
    {
        bIsGetInst = false;
        h_connected = CreateEvent(NULL, TRUE, FALSE, NULL);
        lstAllInstruments.clear();
        strAllIns = "";
        m_instPrice.clear();
        InitializeCriticalSection(&f_csInstrument);
        InitializeCriticalSection(&m_csInstPrice);
    }
    ~FunctionCallBackSet()
    {
        CloseHandle(h_connected);
        DeleteCriticalSection(&f_csInstrument);
        DeleteCriticalSection(&m_csInstPrice);
    }

    CThostFtdcDepthMarketDataField &GetInstrumentInfo(string ins)
    {
        CLock cl(&m_csInstPrice);
        return m_instPrice[ins];
    }
    static void __stdcall OnConnect(void* pApi, CThostFtdcRspUserLoginField *pRspUserLogin, ConnectionStatus result);//���Ӻ�Ľ��״̬
    static void __stdcall OnDisconnect(void* pApi, CThostFtdcRspInfoField *pRspInfo, ConnectionStatus step);//����ʱ������״̬
    static void __stdcall OnErrRtnOrderAction(void* pTraderApi, CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);
    static void __stdcall OnErrRtnOrderInsert(void* pTraderApi, CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
    static void __stdcall OnRspError(void* pApi, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspOrderAction(void* pTraderApi, CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspOrderInsert(void* pTraderApi, CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryDepthMarketData(void* pTraderApi, CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInstrument(void* pTraderApi, CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInstrumentCommissionRate(void* pTraderApi, CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInstrumentMarginRate(void* pTraderApi, CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInvestorPosition(void* pTraderApi, CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryInvestorPositionDetail(void* pTraderApi, CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryOrder(void* pTraderApi, CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryTrade(void* pTraderApi, CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRspQryTradingAccount(void* pTraderApi, CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    static void __stdcall OnRtnDepthMarketData(void* pMdUserApi, CThostFtdcDepthMarketDataField *pDepthMarketData);
    static void __stdcall OnRtnInstrumentStatus(void* pTraderApi, CThostFtdcInstrumentStatusField *pInstrumentStatus);
    static void __stdcall OnRtnOrder(void* pTraderApi, CThostFtdcOrderField *pOrder);
    static void __stdcall OnRtnTrade(void* pTraderApi, CThostFtdcTradeField *pTrade);
    
};

#endif