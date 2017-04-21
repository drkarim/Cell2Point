#define HAS_VTK 1
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkFloatArray.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>
#include "vtkCellDataToPointData.h"
#include "vtkFileOutputWindow.h"

#define MAXDIST 50.0

int main(int argc, char * argv[])
{
	// Input file

	if (argc < 3)
	{
		cout << "Usage: <in_vtk> <out_vtk>" << endl;
		exit(1); 
	}

	char * input_file = argv[1];
	char* output_file = argv[2]; 


	vtkSmartPointer<vtkFileOutputWindow> fileOutputWindow = vtkSmartPointer<vtkFileOutputWindow>::New();
	fileOutputWindow->SetFileName("vtkLog.txt");

	vtkOutputWindow* outputWindow = vtkOutputWindow::GetInstance();
	if (outputWindow)
	{
		outputWindow->SetInstance(fileOutputWindow);
	}

	vtkPolyDataReader * reader = vtkPolyDataReader::New();
	reader->SetFileName(input_file);
	vtkPolyData* poly = vtkPolyData::New();
	reader->Update();
	poly = reader->GetOutput();

	vtkCellDataToPointData* c2p = vtkCellDataToPointData::New();
	c2p->SetInputData(poly); 
	c2p->Update(); 
	cout << "Cell data to point data error code = " << c2p->GetErrorCode() << endl;

	vtkPolyDataWriter* writer = vtkPolyDataWriter::New();
	writer->SetInputData(c2p->GetOutput());
	writer->SetFileName(output_file);
	writer->Update(); 
	

}
