#include <vtkVersion.h>
 
#include <vtkSmartPointer.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkDelimitedTextReader.h>
#include <vtkDoubleArray.h>
#include <vtkTable.h>
#include <vtkPointData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkXMLPolyDataWriter.h>
 
int main(int argc, char* argv[])
{
  // Verify input arguments
  if(argc != 3)
    {
    std::cout << "Usage: " << argv[0]
              << " Filename(.xyz) Outputfile(.vtp)" << std::endl;
    return EXIT_FAILURE;
    }
 
  std::string inputFilename = argv[1];
 
  vtkSmartPointer<vtkDelimitedTextReader> reader =
    vtkSmartPointer<vtkDelimitedTextReader>::New();
  reader->SetFileName(inputFilename.c_str());
  reader->DetectNumericColumnsOn();
  reader->SetFieldDelimiterCharacters(" ");
  reader->Update();
 
  vtkTable* table = reader->GetOutput();
 
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
//  vtkSmartPointer<vtkDoubleArray> normals =
//    vtkSmartPointer<vtkDoubleArray>::New();
  vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3); //3d normals (ie x,y,z)
 
  std::cout << "Table has " << table->GetNumberOfRows()
            << " rows." << std::endl;
  std::cout << "Table has " << table->GetNumberOfColumns()
            << " columns." << std::endl;
 
  for(vtkIdType i = 0; i < table->GetNumberOfRows(); i++)
    {
      // logs x, y, and z, then adds them to an array called points
    std::cout << "(x, y, z): " << (table->GetValue(i,0)).ToDouble() << ", "
              << (table->GetValue(i,1)).ToDouble() << ", "
              << (table->GetValue(i,2)).ToDouble() << " "
              << "(r, g, b): " << (table->GetValue(i,4)).ToDouble() << " "
              << (table->GetValue(i,5)).ToDouble() << " "
              << (table->GetValue(i,6)).ToDouble() << std::endl;
 
    points->InsertNextPoint((table->GetValue(i,0)).ToDouble(),
                            (table->GetValue(i,1)).ToDouble(),
                            (table->GetValue(i,2)).ToDouble());
    unsigned char pcol[3] = {(table->GetValue(i,4)).ToDouble(),
                             (table->GetValue(i,5)).ToDouble(),
                             (table->GetValue(i,6)).ToDouble()};

    colors->InsertNextTupleValue(pcol);
    }
 
  std::cout << "There are " << points->GetNumberOfPoints()
            << " points." << std::endl;
 
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->SetPoints(points);

  // Setup colors



    colors->SetNumberOfComponents(3);
    colors->SetName ("Colors");
    polydata->GetPointData()->SetScalars(colors);

  vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  glyphFilter->SetInputConnection(polydata->GetProducerPort());
#else
  glyphFilter->SetInputData(polydata);
#endif
  glyphFilter->Update();

  // Write the file
   vtkSmartPointer<vtkXMLPolyDataWriter> writer =
     vtkSmartPointer<vtkXMLPolyDataWriter>::New();
   writer->SetFileName(argv[2]);
 #if VTK_MAJOR_VERSION <= 5
   writer->SetInput(polydata);
 #else
   writer->SetInputData(polydata);
 #endif
  // Optional - set the mode. The default is binary.
   //writer->SetDataModeToBinary();
   //writer->SetDataModeToAscii();

     writer->Write();


//  // Visualize
//  vtkSmartPointer<vtkPolyDataMapper> mapper =
//    vtkSmartPointer<vtkPolyDataMapper>::New();
//  mapper->SetInputConnection(glyphFilter->GetOutputPort());
 
//  vtkSmartPointer<vtkActor> actor =
//    vtkSmartPointer<vtkActor>::New();
//  actor->SetMapper(mapper);
//  actor->GetProperty()->SetPointSize(3);
//  actor->GetProperty()->SetColor(1,0,0);
 
//  vtkSmartPointer<vtkRenderer> renderer =
//    vtkSmartPointer<vtkRenderer>::New();
//  vtkSmartPointer<vtkRenderWindow> renderWindow =
//    vtkSmartPointer<vtkRenderWindow>::New();
//  renderWindow->AddRenderer(renderer);
//  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
//    vtkSmartPointer<vtkRenderWindowInteractor>::New();
//  renderWindowInteractor->SetRenderWindow(renderWindow);
 
//  renderer->AddActor(actor);
//  renderer->SetBackground(.2, .2, .2); // Background color green
 
//  renderWindow->Render();
//  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
