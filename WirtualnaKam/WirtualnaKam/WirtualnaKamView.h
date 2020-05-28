
// WirtualnaKamView.h: interfejs klasy CWirtualnaKamView
//

#pragma once

#include <list>

class Czworokat;
class Poligon;

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
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

private:
	void WczytajFigury();
	void WczytajPoligon(Czworokat c, POINT* pt);
	void SortujPoligony();
	void NarysujPoligon(CDC* pDC, Poligon p);
	void NarysujCzworokat(CDC* pDC, Czworokat c);
	void NapiszInstrukcje(CDC* pDC);
	//void DodajWielokaty();
	//void PodzielWielokat(Czworokat c);

private:
	std::list<Czworokat>		lstCzworokaty;
	std::list<Poligon>			lstPoligony;
	POINT punkty[1000][4];

};

#ifndef _DEBUG  // debuguj wersję w elemencie WirtualnaKamView.cpp
inline CWirtualnaKamDoc* CWirtualnaKamView::GetDocument() const
   { return reinterpret_cast<CWirtualnaKamDoc*>(m_pDocument); }
#endif

