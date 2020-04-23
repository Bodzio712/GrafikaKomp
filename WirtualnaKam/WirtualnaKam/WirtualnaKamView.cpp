
// WirtualnaKamView.cpp: implementacja klasy CWirtualnaKamView
//

#include "pch.h"
#include "framework.h"
// Element SHARED_HANDLERS można zdefiniować w projekcie ATL z implementacją podglądu, miniaturze
// procedury obsługi serializacji i filtrów wyszukiwania oraz umożliwia udostępnianie kodu dokumentu w tym projekcie.
#ifndef SHARED_HANDLERS
#include "WirtualnaKam.h"
#endif

#include "WirtualnaKamDoc.h"
#include "WirtualnaKamView.h"
#include "Kamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Kamera kam;

// CWirtualnaKamView

IMPLEMENT_DYNCREATE(CWirtualnaKamView, CView)

BEGIN_MESSAGE_MAP(CWirtualnaKamView, CView)
	// Standardowe polecenia drukowania
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWirtualnaKamView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Tworzenie/niszczenie obiektu CWirtualnaKamView

CWirtualnaKamView::CWirtualnaKamView() noexcept
{
	// TODO: tutaj dodaj kod konstruowania

}

CWirtualnaKamView::~CWirtualnaKamView()
{
}

BOOL CWirtualnaKamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: zmodyfikuj klasę Window lub style w tym miejscu, modyfikując
	//  styl kaskadowy CREATESTRUCT

	return CView::PreCreateWindow(cs);
}

// Rysowanie obiektu CWirtualnaKamView

void CWirtualnaKamView::OnDraw(CDC* pDC)
{
	CWirtualnaKamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	Prostokat rect = Prostokat(Punkt(50, 50, 10), Punkt(100, 50, 10), Punkt(100, 100, 10), Punkt(50, 100, 10));

	if (!pDoc)
		return;

	// TODO: tutaj dodaj kod rysowania danych natywnych
	auto p1 = kam.ObliczPozycjePunktu(rect.w1);
	auto p2 = kam.ObliczPozycjePunktu(rect.w2);
	auto p3 = kam.ObliczPozycjePunktu(rect.w3);
	auto p4 = kam.ObliczPozycjePunktu(rect.w4);

	pDC->MoveTo(p1.x, p1.y);
	pDC->LineTo(p2.x, p2.y);
	pDC->LineTo(p3.x, p3.y);
	pDC->LineTo(p4.x, p4.y);
	pDC->LineTo(p1.x, p1.y);
}


// Drukowanie obiektu CWirtualnaKamView


void CWirtualnaKamView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWirtualnaKamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// domyślne przygotowanie
	return DoPreparePrinting(pInfo);
}

void CWirtualnaKamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: dodaj kolejne inicjowanie przed rozpoczęciem drukowania
}

void CWirtualnaKamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: dodaj czyszczenie po drukowaniu
}

void CWirtualnaKamView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWirtualnaKamView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Diagnostyka klasy CWirtualnaKamView

#ifdef _DEBUG
void CWirtualnaKamView::AssertValid() const
{
	CView::AssertValid();
}

void CWirtualnaKamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWirtualnaKamDoc* CWirtualnaKamView::GetDocument() const // wbudowana jest wersja bez debugowania
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWirtualnaKamDoc)));
	return (CWirtualnaKamDoc*)m_pDocument;
}
#endif //_DEBUG


// Procedury obsługi komunikatów CWirtualnaKamView
