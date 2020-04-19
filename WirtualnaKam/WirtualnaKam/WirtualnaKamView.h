
// WirtualnaKamView.h: interfejs klasy CWirtualnaKamView
//

#pragma once


class CWirtualnaKamView : public CView
{
protected: // utwórz tylko na podstawie serializacji
	CWirtualnaKamView() noexcept;
	DECLARE_DYNCREATE(CWirtualnaKamView)

// Atrybuty
public:
	CWirtualnaKamDoc* GetDocument() const;

// Operacje
public:

// Przesłania
public:
	virtual void OnDraw(CDC* pDC);  // zastąpiony, aby narysować ten widok
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementacja
public:
	virtual ~CWirtualnaKamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Wygenerowano funkcje mapy komunikatów
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debuguj wersję w elemencie WirtualnaKamView.cpp
inline CWirtualnaKamDoc* CWirtualnaKamView::GetDocument() const
   { return reinterpret_cast<CWirtualnaKamDoc*>(m_pDocument); }
#endif

