#include <Python.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <numeric>

#include <iostream>
#include <numpy/arrayobject.h>
#include <opencv2/opencv.hpp>

//#include "neural_object_detector.hpp"

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <vector>

PyObject *python_pedestrian_tracker_function;
npy_intp image_dimensions[3];


int init_python(int image_width, int image_height)
{
	Py_Initialize();

    PyObject *python_module_name = PyUnicode_DecodeFSDefault("demo");


	PyObject *python_module = PyImport_Import(python_module_name);

	if (python_module == NULL)
	{
        PyErr_Print();
		Py_Finalize();
		exit (printf("Error: The python_module could not be loaded.\nMay be PYTHON_PATH is not set.\n"));
	}
	Py_DECREF(python_module_name);

	import_array();

	python_pedestrian_tracker_function = PyObject_GetAttrString(python_module, (char *) "main");

	if (python_pedestrian_tracker_function == NULL || !PyCallable_Check(python_pedestrian_tracker_function))
	{
		Py_DECREF(python_module);
		Py_Finalize();
		exit (printf("Error: Could not load the python_semantic_segmentation_function.\n"));
	}

	image_dimensions[0] = image_height;           //create shape for numpy array
	image_dimensions[1] = image_width;
	image_dimensions[2] = 3;

	printf("------- Python Tracker Ready -------\n");
}


cv::Mat numpy_array_to_cv_mat(PyArrayObject* array) {
    npy_intp* shape = PyArray_DIMS(array);
    int ndims = PyArray_NDIM(array);

    // Cria uma matriz OpenCV vazia
    cv::Mat mat;
	std::cerr << ndims << std::endl;
    // Converte a matriz NumPy para uma matriz OpenCV
    switch (ndims) {
        case 2:
            mat = cv::Mat(shape[0], shape[1], CV_8UC3, PyArray_DATA(array)).clone();
			
            break;
        case 3:
            mat = cv::Mat(shape[0], shape[1], CV_8UC3, PyArray_DATA(array)).clone();			
            break;
        default:
            // Adicione tratamento para outros casos conforme necessário
            break;
    }

    return mat;
}



int
call_python_function(unsigned char *image/*, vector<bbox_t> predictions*/)
{
	PyObject* numpy_image_array = PyArray_SimpleNewFromData(3, image_dimensions, NPY_UBYTE, image);        //convert testVector to a numpy array


	PyArrayObject* identifications = (PyArrayObject*)PyObject_CallFunctionObjArgs(python_pedestrian_tracker_function, numpy_image_array,NULL); //add this line
  //  PyArrayObject* identifications = (PyArrayObject*)PyObject_CallFunctionObjArgs(python_pedestrian_tracker_function, numpy_image_array, numpy_predictions_array, NULL);

	// Imprimir o formato da matriz (shape)
	/*
	int ndims = PyArray_NDIM(identifications);
	std::cerr << "Shape of identifications: ";
	for (int i = 0; i < ndims; ++i) {
		std::cerr << PyArray_DIMS(identifications)[i] << " ";
	}
	std::cerr << std::endl;

	// Imprimir o tipo de dados da matriz (type)
	std::cerr << "Type of identifications: " << PyArray_TYPE(identifications) << " (";
	switch (PyArray_TYPE(identifications)) {
		case NPY_BOOL:
			std::cerr << "NPY_BOOL";
			break;
		case NPY_BYTE:
			std::cerr << "NPY_BYTE";
			break;
		case NPY_UBYTE:
			std::cerr << "NPY_UBYTE";
			break;
		case NPY_SHORT:
			std::cerr << "NPY_SHORT";
			break;
		case NPY_USHORT:
			std::cerr << "NPY_USHORT";
			break;
		case NPY_INT:
			std::cerr << "NPY_INT";
			break;
		case NPY_UINT:
			std::cerr << "NPY_UINT";
			break;
		case NPY_LONG:
			std::cerr << "NPY_LONG";
			break;
		case NPY_ULONG:
			std::cerr << "NPY_ULONG";
			break;
		case NPY_LONGLONG:
			std::cerr << "NPY_LONGLONG";
			break;
		case NPY_ULONGLONG:
			std::cerr << "NPY_ULONGLONG";
			break;
		case NPY_HALF:
			std::cerr << "NPY_HALF";
			break;
		case NPY_FLOAT:
			std::cerr << "NPY_FLOAT";
			break;
		case NPY_DOUBLE:
			std::cerr << "NPY_DOUBLE";
			break;
		case NPY_LONGDOUBLE:
			std::cerr << "NPY_LONGDOUBLE";
			break;
		default:
			std::cerr << "UNKNOWN";
		}
	std::cerr << ")" << std::endl;

	*/
	cv::Mat img0 = numpy_array_to_cv_mat(identifications);

	
    // Exibe a imagem
	if (!img0.empty()) {
		cv::imshow("Resultado", img0);
		cv::waitKey(0);
	} else {
		std::cerr << "Erro: A matriz OpenCV é inválida." << std::endl;
	}



	if (PyErr_Occurred())
		PyErr_Print();

	//free(array);
	Py_DECREF(numpy_image_array);
	Py_XDECREF(python_pedestrian_tracker_function);
	//Py_DECREF(numpy_predictions_array);
	Py_DECREF(identifications);
}


int
main()
{
	
    // Cria uma matriz vazia
    cv::Mat img0;

    // Tenta ler a imagem
    img0 = cv::imread("data/iara.png");
    if (img0.empty()) {
        std::cerr << "Erro ao ler a imagem." << std::endl;
        return -1;
    }

	int channels = 3;
    int height = img0.rows;
    int width = img0.cols;

    // 2. Transpor as dimensões da imagem (canais de cor, altura, largura)
    unsigned char *pixel_value = img0.data;

	std::cout << sizeof(pixel_value) << std::endl;
	
	
	init_python(width,height);

    // Chama a função Python com o valor do pixel
	
    call_python_function(pixel_value);

 
   return 0;
}


