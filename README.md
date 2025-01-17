# Geant4FlukaComparison
A simple guide to compare Geant4 and FLUKA results using ROOT and C


HOW TO USE IT:

Assuming that you have an Geant4 output that is in .root format and FLUKA output that is in .tab.lis format, you can follow this tutorial.

First, we are going to need to convert root file and Tree branches inside to text. Each of the histograms need to be in .txt format. 
Put your _geant4data_.root, _FLUKAdata_.tab.lis, SaveHistogramsToTxt.c and DrawOverlappingHistograms.c into the same folder.
Before compiling and running C files, open them with IDE of your choice. 

In SaveHistogramsToTxt.C file, change the name of rootFileName to your root file name.

In DrawOverlappingHistograms.C file, change both txt file name and tab.lis file name according to your files. I have put comments just above them to help you navigate.

txt name can be changed in "std::ifstream file1("")"
tab.lis can be changed in "std::ifstream file2("")"

![image](https://github.com/user-attachments/assets/6e571130-b1c1-4438-87b9-4ce3a32615b0)
![image](https://github.com/user-attachments/assets/f7ee3349-e68c-45b7-8c29-0021e220cd98)

After these steps, just save and exit. Now, in the same working directory where all these files are located, open up a terminal. This tutorial assumes you have ROOT installed. 
Type in "root .\SaveHistogramsToTxt.C"
This shoukd take care of converting ROOT histograms, assuming that you have correctly edited the C file and entered your file names.
Open up a terminal again. Type "root .\DrawOverlappingHistograms.C"
Now, a new canvas will be opened with both your geant4 and FLUKA data plotted.
