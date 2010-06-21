#include <stdlib.h>
#include <iup.h>
#include <iupgl.h>
#include <cd.h>

#include "simple.h"

#ifdef USE_OPENGL
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#endif

int cmdExit(void)
{
  return IUP_CLOSE;
}

void simple_loadled (void);

/* USE_OPENGL - add to linker:
iupgl
opengl32
glu32
cdgl
ftgl
*/

int main(int argc, char** argv)
{
  IupOpen(&argc, &argv);                        

#ifdef USE_CONTEXTPLUS
  cdInitContextPlus();
#endif
#ifdef USE_OPENGL
  IupGLCanvasOpen();
#endif

  simple_loadled();
#ifdef USE_OPENGL
  {
    Ihandle* dialog = IupGetHandle("SimpleDialog");
    Ihandle* canvas = IupGetHandle("SimpleCanvas");
    IupDestroy(canvas);
    canvas = IupGLCanvas("SimpleRepaint");
    IupSetHandle("SimpleCanvas", canvas);
    IupAppend(dialog, canvas);
  }
#endif

  IupSetAttribute(IupGetHandle("SimpleDialog"), "PLACEMENT", "MAXIMIZED");
  IupShow(IupGetHandle("SimpleDialog"));

  SimpleCreateCanvas((char*)IupGetHandle("SimpleCanvas"));

  IupSetFunction("cmdExit", (Icallback) cmdExit);

  IupSetFunction("SimplePlayClipboard", (Icallback) SimplePlayClipboard);
  IupSetFunction("SimplePlayCGMText", (Icallback) SimplePlayCGMText);
  IupSetFunction("SimplePlayCGMBin", (Icallback) SimplePlayCGMBin);
  IupSetFunction("SimplePlayMetafile", (Icallback) SimplePlayMetafile);
  IupSetFunction("SimplePlayWMF", (Icallback) SimplePlayWMF);
  IupSetFunction("SimplePlayEMF", (Icallback) SimplePlayEMF);

  IupSetFunction("SimpleDrawDebug", (Icallback) SimpleDrawDebug);
  IupSetFunction("SimpleDrawWindow", (Icallback) SimpleDrawWindow);
  IupSetFunction("SimpleDrawCGMText", (Icallback) SimpleDrawCGMText);
  IupSetFunction("SimpleDrawCGMBin", (Icallback) SimpleDrawCGMBin);
  IupSetFunction("SimpleDrawDXF", (Icallback) SimpleDrawDXF);
  IupSetFunction("SimpleDrawDGN", (Icallback) SimpleDrawDGN);
  IupSetFunction("SimpleDrawEMF", (Icallback) SimpleDrawEMF);
  IupSetFunction("SimpleDrawMetafile", (Icallback) SimpleDrawMetafile);
  IupSetFunction("SimpleDrawPDF", (Icallback) SimpleDrawPDF);
  IupSetFunction("SimpleDrawPS", (Icallback) SimpleDrawPS);
  IupSetFunction("SimpleDrawEPS", (Icallback) SimpleDrawEPS);
  IupSetFunction("SimpleDrawSVG", (Icallback) SimpleDrawSVG);
  IupSetFunction("SimpleDrawWMF", (Icallback) SimpleDrawWMF);
  IupSetFunction("SimpleDrawPrint", (Icallback) SimpleDrawPrint);
  IupSetFunction("SimpleDrawPrintDialog", (Icallback) SimpleDrawPrintDialog);
  IupSetFunction("SimpleDrawClipboardBitmap", (Icallback) SimpleDrawClipboardBitmap);
  IupSetFunction("SimpleDrawClipboardMetafile", (Icallback) SimpleDrawClipboardMetafile);
  IupSetFunction("SimpleDrawClipboardEMF", (Icallback) SimpleDrawClipboardEMF);
  IupSetFunction("SimpleDrawImage", (Icallback) SimpleDrawImage);
  IupSetFunction("SimpleDrawImageRGB", (Icallback) SimpleDrawImageRGB);
  IupSetFunction("SimpleDrawSimulate", (Icallback) SimpleDrawSimulate);

#ifdef USE_OPENGL
  IupSetFunction("SimpleDrawGL", (Icallback) SimpleDrawGL);
#endif

  IupSetFunction("SimpleNotXor", (Icallback) SimpleNotXor);
  IupSetFunction("SimpleXor", (Icallback) SimpleXor);
  IupSetFunction("SimpleReplace", (Icallback) SimpleReplace);
  IupSetFunction("SimpleClippingOff", (Icallback) SimpleClippingOff);
  IupSetFunction("SimpleClippingArea", (Icallback) SimpleClippingArea);
  IupSetFunction("SimpleClippingPolygon", (Icallback) SimpleClippingPolygon);
  IupSetFunction("SimpleClippingRegion", (Icallback) SimpleClippingRegion);
  IupSetFunction("SimpleContextPlus", (Icallback) SimpleContextPlus);
  IupSetFunction("SimpleTransform", (Icallback) SimpleTransform);

  IupSetFunction("SimpleDrawAll", (Icallback) SimpleDrawAll);
  IupSetFunction("SimpleDrawTextAlign", (Icallback) SimpleDrawTextAlign);
  IupSetFunction("SimpleDrawTextFonts", (Icallback) SimpleDrawTextFonts);
  IupSetFunction("SimpleDrawTest", (Icallback) SimpleDrawTest);

  IupSetFunction("SimpleRepaint", (Icallback) SimpleDrawRepaint);

  SimpleDrawWindow();

#ifdef USE_OPENGL
  {
    Ihandle* canvas = IupGetHandle("SimpleCanvas");
    int w = IupGetInt(canvas, "RASTERSIZE");
    int h = IupGetInt2(canvas, "RASTERSIZE");
    IupGLMakeCurrent(canvas);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
#endif

  IupMainLoop();

  SimpleKillCanvas();

  IupClose();

  return EXIT_SUCCESS;
}
