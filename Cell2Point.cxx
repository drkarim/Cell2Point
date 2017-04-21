#define HAS_VTK 1
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include "vtkCellDataToPointData.h"
#include "vtkFileOutputWindow.h"


int main(int argc, char * argv[])
{
	
	// Dirty check arguments 
	if (argc < 3)
	{
		cout << "Usage: <in_vtk> <out_vtk>" << endl;
		exit(1); 
	}

	// read command-line arguments 
	char* input_file = argv[1];
	char* output_file = argv[2]; 

	// For error logging, check your folder for vtkLog.txt for VTK run-time error messages 
	vtkSmartPointer<vtkFileOutputWindow> fileOutputWindow = vtkSmartPointer<vtkFileOutputWindow>::New();
	fileOutputWindow->SetFileName("vtkLog.txt");

	vtkOutputWindow* outputWindow = vtkOutputWindow::GetInstance();
	if (outputWindow)
	{
		outputWindow->SetInstance(fileOutputWindow);
	}

	// Now read the VTK file 
	vtkPolyDataReader * reader = vtkPolyDataReader::New();
	reader->SetFileName(input_file);
	vtkPolyData* poly = vtkPolyData::New();
	reader->Update();
	poly = reader->GetOutput();

	// Conversion to point data 
	vtkCellDataToPointData* c2p = vtkCellDataToPointData::New();
	c2p->SetInputData(poly); 
	c2p->Update(); 
	cout << "Cell data to point data error code = " << c2p->GetErrorCode() << endl;

	// Write to a file 
	vtkPolyDataWriter* writer = vtkPolyDataWriter::New();
	writer->SetInputData(c2p->GetOutput());
	writer->SetFileName(output_file);
	writer->Update(); 

	// Complete! 
	

}
