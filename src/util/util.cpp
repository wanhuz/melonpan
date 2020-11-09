#include "util.h"
#include <qimage.h>




/*QPixmap to Leptonica's Pix conversion*/
Pix* Util::qPixMap2PIX(QPixmap* pixmap) {
	Pix* pix;
	QImage qimage;
	l_uint32* lines;
	
	qimage = QImage(pixmap->toImage());

	int dpm = 300 / 0.0254; // ~300 DPI
	qimage.setDotsPerMeterX(dpm);
	qimage.setDotsPerMeterY(dpm);

	qimage = qimage.rgbSwapped();
	int width = qimage.width();
	int height = qimage.height();
	int depth = qimage.depth();
	int wpl = qimage.bytesPerLine() / 4;

	pix = pixCreate(width, height, depth);
	pixSetWpl(pix, wpl);
	pixSetColormap(pix, NULL);
	l_uint32* datas = pix->data;

	for (int y = 0; y < height; y++) {
		lines = datas + y * wpl;
		QByteArray a((const char*)qimage.scanLine(y), qimage.bytesPerLine());
		for (int j = 0; j < a.size(); j++) {
			*((l_uint8*)lines + j) = a[j];
		}
	}
	return pixEndianByteSwapNew(pix);
}

