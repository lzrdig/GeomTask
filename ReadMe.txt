This folder contains the following VS solution files:

CylinderWebAPI.sln
GeometryProblem_CSharp.sln
GeometryProblem_MFC.sln
GeometryProblem_MFC_2.sln
WebGL.sln

1) The starting point is the solution GeometryProblem_MFC.sln, which contains the full app with the UI written in MFC with the use of OpenGL library for drawing 3D scenes. And, as the back end, a Static Library is linked in where the Cylinder class has been imlemented. One of its methods is used to calculate the distance from a 3D point to the cylinder (the nearest distance that is). The logic for the back end is simple, however, some of the code I had borrowed from John . I applied my own modifications simply to implement some OOP principles.

2) As a presentation of the initial step towards generation of the UI with MFC, I've included solution GeometryProblem_MFC_2.sln. The UI is primitive and the link to the back end was not complete.

3) To demonstrate the posibility of implmenting the UI in C#, the GeometryProblem_CSharp.sln was generated where the SharpGL library (a C# wrapper of OpenGL functions) was used.

4) Solution CylinderWebAPI.sln is included to show the path towards the creation of Javascript based UI (more specifically Angular 2) that uses the C++ functions through the mediation of a WebAPI (in C#). Calling C++ functions from C# was part of the task. The wrapping of a C++ class into a Managed type class is an option that I did not have time to complete.

5) Lastly, WebGL.sln solution demonstrates the Angular 2 based UI mentioned above. Unfortunately, Visual Studio is not friendly with the path resolutions that takes places when the modules/components get loaded. Therefore, currently, a NPM task runner is used to start the UI by going to the Task Run Esxplorer and running the "start" task. Patience will be required before all node modules will get downloaded.