# Process Model (Cross-Platform)

##  Program Description
This is cross-platform console-based program written in the C programming language made to perform the computations required for the design, simulation and fabrication of up to industrial size process equipment. The program is able to either show the data either in console or outputting results into either a (1) report written in markdown or (2) text file suitable for import into Microsoft Excel.

##  Product Properties
GitHub username: "mc97-stack".
GitHub Repository URL: "https://github.com/mc97-stack/IJTB-m2UY-7iPC-D0FN.git".

Development status: Under development (Research).
Repository visibility status: Public.

Features currently available:
- Topics 1 - 4 of B48BB (Process Engineering A (Fluid Statics and Dynamics))
- Topic 1 and 2 of B48BC (Process Engineering B (Thermodynamic Processes))

##  Windows Install (Using Visual Studio 2019)
1.  Ensure that "Mobile Development with C++" workload is installed in "Visual Studio Installer".
2.  On the "Welcome" window, click "Clone GitHub Repository".
3.  This repository is located at the URL: "https://github.com/mc97-stack/IJTB-m2UY-7iPC-D0FN.git".
4.  After allowing Visual Studio 2019 to download repository, compile the project.
5.  Locate the compiled project in file explorer with either command prompt or windows powershell.

##  MacOS Install (Using Xcode 11.6)
1.  On the "Welcome" window, click "Clone an Existing Project".
2.  This repository is located at the URL: "https://github.com/mc97-stack/IJTB-m2UY-7iPC-D0FN.git".
3.  After allowing Xcode 11.6 to download and build repository, compile the project.
4.  Locate project product in finder to run program within terminal.

##  Known Bugs
- Imported windows version will not properly compile the project.

Resolution:
- The program codebase will be finished before manually creating the Visual Studio solution file

- Program on MacOS Terminal will not create a file output. N.B. File output still works as intended within the xcode environment.

Resolution:
- All subroutines where calculations are performed will have a display function which displays the same output as what would appear in the text file if the program is working as intended. The console output can then be copied into a text editing software (e.g. textedit) for import into Microsoft Excel using the data import from text file facilities.
