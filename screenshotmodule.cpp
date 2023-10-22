#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

struct Screenshot
{
    Display *display;
    Window root;
    Screenshot()
    {
        display = XOpenDisplay(NULL);
        root = DefaultRootWindow(display);
    }
    Screenshot(const Screenshot &sc) = delete;
    ~Screenshot()
    {
        XDestroyWindow(display, root);
        XCloseDisplay(display);
    }
};

Screenshot screenshot{};

static PyObject *method_take(PyObject *self, PyObject *args)
{

    int xx, yy, W, H;
    unsigned char *data;
    Py_ssize_t count;

    if (!PyArg_ParseTuple(args, "iiiis#", &xx, &yy, &W, &H, &data, &count))
    {
        return NULL;
    }

    // PySys_WriteStdout("%d\n", xx);
    // PySys_WriteStdout("%d\n", screenshot.test);
    // PySys_WriteStdout("%d\n", yy);
    // PySys_WriteStdout("%d\n", W);
    // PySys_WriteStdout("%d\n", H);
    // PySys_WriteStdout("%ld\n", count);

    XImage *image = XGetImage(screenshot.display, screenshot.root, xx, yy, W, H, AllPlanes, ZPixmap);

    unsigned long red_mask = image->red_mask;
    unsigned long green_mask = image->green_mask;
    unsigned long blue_mask = image->blue_mask;
    int x, y;
    int ii = 0;
    for (y = 0; y < H; y++)
    {
        for (x = 0; x < W; x++)
        {
            unsigned long pixel = XGetPixel(image, x, y);
            unsigned char blue = (pixel & blue_mask);
            unsigned char green = (pixel & green_mask) >> 8;
            unsigned char red = (pixel & red_mask) >> 16;

            // PySys_WriteStdout("ii %s\n", std::to_string(ii).c_str());
            data[ii + 2] = blue;
            data[ii + 1] = green;
            data[ii + 0] = red;
            ii += 3;
        }
    }

    XDestroyImage(image);

    Py_RETURN_NONE;
}

static PyMethodDef ScreenshotMethods[] = {
    {"take", method_take, METH_VARARGS, "Take a screenshot image"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef screenshotmodule = {
    PyModuleDef_HEAD_INIT,
    "screenshot",
    "Python interface for taking a screenshot image",
    -1,
    ScreenshotMethods};

PyMODINIT_FUNC PyInit_screenshot(void)
{
    PyObject *module = PyModule_Create(&screenshotmodule);

    return module;
}