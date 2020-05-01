
// WirtualnaKamView.cpp: implementacja klasy CWirtualnaKamView
//

#include "pch.h"
#include "framework.h"
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

/////////////////////////////////////////////////////////////////////////////
// Kwanty ruchu kamery
#define KROK_RUCH	1
#define KROK_OBR	0.03
#define KROK_ZOOM	0.05

#define SKALA_OGRANICZEN 1.5

IMPLEMENT_DYNCREATE(CWirtualnaKamView, CView)

BEGIN_MESSAGE_MAP(CWirtualnaKamView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWirtualnaKamView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

CWirtualnaKamView::CWirtualnaKamView() noexcept
{
	// TODO: tutaj dodaj kod konstruowania
}

CWirtualnaKamView::~CWirtualnaKamView()
{
}

BOOL CWirtualnaKamView::PreCreateWindow(CREATESTRUCT& cs)
{
	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	kam.szer = rect.Width();
	kam.wys = rect.Height();

	WczytajFigury();

	return CView::PreCreateWindow(cs);
}

// Rysowanie obiektu CWirtualnaKamView

void CWirtualnaKamView::OnDraw(CDC* pDC)
{
	CWirtualnaKamDoc* pDoc = GetDocument();
	std::list<Czworokat>::iterator it;
	ASSERT_VALID(pDoc);

	if (!pDoc)
		return;

	pDoc->SetTitle(L"Scena domyślna");

	for (it = lstCzworokaty.begin(); it != lstCzworokaty.end(); ++it)
	{
		NarysujCzworokat(pDC, (*it));
	}

	NapiszInstrukcje(pDC);
}

void CWirtualnaKamView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWirtualnaKamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CWirtualnaKamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CWirtualnaKamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CWirtualnaKamView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}
/////////////////////////////////////////////////////////////////////////////
// Bindowanie klawiszy
BOOL CWirtualnaKamView::PreTranslateMessage(MSG* pMsg)
{
	int i=0;
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_UP:
			kam.RuchY(KROK_RUCH);
			Invalidate();
			break;
		case VK_DOWN:
			kam.RuchY(-KROK_RUCH);
			Invalidate();
			break;
		case VK_LEFT:
			kam.RuchZ(KROK_RUCH);
			Invalidate();
			break;
		case VK_RIGHT:
			kam.RuchZ(-KROK_RUCH);
			Invalidate();
			break;
		case 0x57:
			kam.RuchX(KROK_RUCH);
			Invalidate();
			break;
		case 0x53:
			kam.RuchX(-KROK_RUCH);
			Invalidate();
			break;
		case VK_NUMPAD2:
			kam.ObrotOX(KROK_OBR);
			Invalidate();
			break;
		case VK_NUMPAD8:
			kam.ObrotOX(-KROK_OBR);
			Invalidate();
			break;
		case VK_NUMPAD4:
			kam.ObrotOY(KROK_OBR);
			Invalidate();
			break;
		case VK_NUMPAD6:
			kam.ObrotOY(-KROK_OBR);
			Invalidate();
			break;
		case VK_PRIOR:
			kam.ObrotOZ(KROK_OBR);
			Invalidate();
			break;
		case VK_NEXT:
			kam.ObrotOZ(-KROK_OBR);
			Invalidate();
			break;
		case 0x45:
			kam.Zoom(KROK_ZOOM);
			Invalidate();
			break;
		case 0x51:
			kam.Zoom(-KROK_ZOOM);
			Invalidate();
			break;
		default:
			break;
		}
	}
	return __super::PreTranslateMessage(pMsg);
}

void CWirtualnaKamView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

#ifdef _DEBUG
void CWirtualnaKamView::AssertValid() const
{
	CView::AssertValid();
}

void CWirtualnaKamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWirtualnaKamDoc* CWirtualnaKamView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWirtualnaKamDoc)));
	return (CWirtualnaKamDoc*)m_pDocument;
}
#endif //_DEBUG}

void CWirtualnaKamView::NarysujCzworokat(CDC* pDC, Czworokat c)
{
	// TODO: tutaj dodaj kod rysowania danych natywnych
	auto p1 = kam.ObliczPozycjePunktu(c.w1);
	auto p2 = kam.ObliczPozycjePunktu(c.w2);
	auto p3 = kam.ObliczPozycjePunktu(c.w3);
	auto p4 = kam.ObliczPozycjePunktu(c.w4);

	if (!(p1.x < (-kam.szer*SKALA_OGRANICZEN) || p1.x > ((1+SKALA_OGRANICZEN) * kam.szer) || p1.y < (-kam.wys*SKALA_OGRANICZEN) || p1.y > ((1+SKALA_OGRANICZEN) * kam.wys) || p1.odl < 0
		|| p2.x < (-kam.szer*SKALA_OGRANICZEN) || p2.x > ((1+SKALA_OGRANICZEN) * kam.szer) || p2.y < (-kam.wys*SKALA_OGRANICZEN) || p2.y >((1 + SKALA_OGRANICZEN) * kam.wys) || p2.odl < 0))
	{
		pDC->MoveTo(p1.x, p1.y);
		pDC->LineTo(p2.x, p2.y);
	}
	if (!(p2.x < (-kam.szer*SKALA_OGRANICZEN) || p2.x >((1+SKALA_OGRANICZEN) * kam.szer) || p2.y < (-kam.wys*SKALA_OGRANICZEN) || p2.y >((1+SKALA_OGRANICZEN) * kam.wys) || p1.odl < 0
		|| p3.x < (-kam.szer*SKALA_OGRANICZEN) || p3.x >((1+SKALA_OGRANICZEN) * kam.szer) || p3.y < (-kam.wys*SKALA_OGRANICZEN) || p3.y > 2 * ((1 + SKALA_OGRANICZEN) * kam.wys) || p2.odl < 0))
	{
		pDC->MoveTo(p2.x, p2.y);
		pDC->LineTo(p3.x, p3.y);
	}
	if (!(p3.x < (-kam.szer*SKALA_OGRANICZEN) || p3.x >((1+SKALA_OGRANICZEN) * kam.szer) || p3.y < (-kam.wys*SKALA_OGRANICZEN) || p3.y >((1+SKALA_OGRANICZEN) * kam.wys) || p1.odl < 0
		|| p4.x < (-kam.szer*SKALA_OGRANICZEN) || p4.x >((1+SKALA_OGRANICZEN) * kam.szer) || p4.y < (-kam.wys*SKALA_OGRANICZEN) || p4.y > 2 * ((1 + SKALA_OGRANICZEN) * kam.wys) || p2.odl < 0))
	{
		pDC->MoveTo(p3.x, p3.y);
		pDC->LineTo(p4.x, p4.y);
	}
	if (!(p4.x < (-kam.szer*SKALA_OGRANICZEN) || p4.x >((1+SKALA_OGRANICZEN) * kam.szer) || p4.y < (-kam.wys*SKALA_OGRANICZEN) || p4.y >((1+SKALA_OGRANICZEN) * kam.wys) || p1.odl < 0
		|| p1.x < (-kam.szer*SKALA_OGRANICZEN) || p1.x >((1+SKALA_OGRANICZEN) * kam.szer) || p1.y < (-kam.wys*SKALA_OGRANICZEN) || p1.y > 2 * ((1 + SKALA_OGRANICZEN) * kam.wys) || p2.odl < 0))
	{
		pDC->MoveTo(p4.x, p4.y);
		pDC->LineTo(p1.x, p1.y);
	}

	//if (!((p1.x < 0 || p1.x >kam.szer || p1.y < 0 || p1.y >kam.wys)
	//	&& !(p2.x < 0 || p2.x >kam.szer || p2.y < 0 || p2.y > kam.wys)))
	//{
	//	pDC->MoveTo(p1.x, p1.y);
	//	pDC->LineTo(p2.x, p2.y);
	//}
	//if (!((p2.x < 0 || p2.x >kam.szer || p2.y < 0 || p2.y >kam.wys)
	//	&& !(p3.x < 0 || p3.x >kam.szer || p3.y < 0 || p3.y > kam.wys)))
	//{
	//	pDC->MoveTo(p2.x, p2.y);
	//	pDC->LineTo(p3.x, p3.y);
	//}
	//if (!((p3.x < 0 || p3.x >kam.szer || p3.y < 0 || p3.y >kam.wys)
	//	&& !(p4.x < 0 || p4.x >kam.szer || p4.y < 0 || p4.y > kam.wys)))
	//{
	//	pDC->MoveTo(p3.x, p3.y);
	//	pDC->LineTo(p4.x, p4.y);
	//}
	//if (!((p4.x < 0 || p4.x > kam.szer || p4.y < 0 || p4.y >kam.wys)
	//	&& !(p1.x < 0 || p1.x > kam.szer || p1.y < 0 || p1.y > kam.wys)))
	//{
	//	pDC->MoveTo(p4.x, p4.y);
	//	pDC->LineTo(p1.x, p1.y);
	//}
}

void CWirtualnaKamView::NapiszInstrukcje(CDC* pDC)
{
	pDC->TextOut(10, 40, L"Strzałki - Ruch osie X i Y");
	pDC->TextOut(10, 60, L"W / S - Ruch przód / tył");
	pDC->TextOut(10, 80, L"Q / E - Zoom");
	pDC->TextOut(10, 100, L"Numpad 4 / 6 - Obrót oś OY");
	pDC->TextOut(10, 120, L"Numpad 2 / 8 - Obrót oś OX");
	pDC->TextOut(10, 140, L"Page Up / Page Down - Obrót oś OZ");
}

void CWirtualnaKamView::WczytajFigury()
{
	CStdioFile		file;
	CFileException	ex;
	CString			linia, punkt, poz;
	int				tabPoz[3];
	Punkt			tabPunkt[4];
	int				nPos, pPos;

	lstCzworokaty.clear();

	file.Open(L"..\\scena.csv", CFile::modeRead | CFile::typeText, &ex);
	while (file.ReadString(linia))
	{
		nPos = 0;
		for (int i = 0; i < 4; i++)
		{
			punkt = linia.Tokenize(L";", nPos);
			pPos = 0;
			for (int j = 0; j < 3; j++)
			{
				poz = punkt.Tokenize(L",", pPos);
				tabPoz[j] = _wtoi(poz);
			}
			tabPunkt[i] = Punkt(tabPoz[0], tabPoz[1], tabPoz[2]);
		}
		lstCzworokaty.push_back(Czworokat(tabPunkt[0], tabPunkt[1], tabPunkt[2], tabPunkt[3]));
	}
}