# UnitySimpleNativeLibrary

Unity native plugin

Simplest Plugin example
Example code from here: https://docs.unity3d.com/Manual/PluginsForDesktop.html

## Create native plugin - Windows
Follow this [**tutorial**](https://msdn.microsoft.com/en-us/library/ms235636.aspx)

### Visual Studio - Create project
1.	On the menu bar, choose **File**, **New**, **Project**.
2.	In the left pane of the **New Project** dialog box, expand **Installed, Templates, Visual C++**, and then select **Win32**.
3.	In the center pane, select **Win32 Console Application**.
4.	Specify a name for the project (for example, **SimpleNativeLibrary**). Choose the **OK** button.
5.	On the **Overview** page of the **Win32 Application Wizard** dialog box, choose the **Next** button.
6.	On the **Application Settings** page, under **Application type**, select **DLL**.
7.	Choose the **Finish** button to create the project.

### Visual Studio – Strip down project
If you don't need the precompiled headers.
1.	Open the project properties, in **C/C++, Precompiled Headers**.
2.	In the options on the right, under **Precompiled Header**, select **Not Using Precompiled Headers**
3.	Delete all source and headers files added automatically beside **SimpleNativeLibrary.cpp**
4.	Put code you want to include in this library

```c++
// SimpleNativeLibrary.cpp : Defines the exported functions for the DLL application.
//

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

// Link following functions C-style (required for plugins)
extern "C"
{

	// The functions we will call from Unity.
	//
	const EXPORT_API char*  PrintHello() {
		return "Hello";
	}

	int EXPORT_API PrintANumber() {
		return 5;
	}

	int EXPORT_API AddTwoIntegers(int a, int b) {
		return a + b;
	}

	float EXPORT_API AddTwoFloats(float a, float b) {
		return a + b;
	}

} // end of export C block
```
5.  Build the library.

## Create native plugin - Android
Reference guides: [**this**](https://github.com/makbn/opencv_android_setup_tutorial), and [**this**](https://stackoverflow.com/a/41037526)
1.	Open **Android Studio** and click on **New Project**
2.	Fill **Application Name** (for example SimpleNativeLibrary), **Company Domain** and check **Include C++ Support**
3.	Continue like all other default android project and in the last step before click on **Finish** you need to set your C++ Standard! I use **Toolchain Default**

-	if you got an exception with this message : Error:NDK not configured. Download it with SDK manager.) you should follow this steps:
  -	open **Project Structure** under File tab.
  -	set your NDK direction in **Android NDK location** and Done!

4.	In the project structure, under **app** module, open **CMakeLists.txt**
5.	Change the name of the library, under **add_library** and **target_link_libraries** sections. Replace **native-lib** to **SimpleNativeLibrary**
6.	Go to app, src, main, cpp and paste the C++ code in the source file there.

```c++
#include <jni.h>
#include <string>

// Link following functions C-style (required for plugins)
extern "C"
{
    // The functions we will call from Unity.

    const char* PrintHello() {
        return "Hello";
    }

    int PrintANumber() {
        return 5;
    }

    int AddTwoIntegers(int a, int b) {
        return a + b;
    }

    float AddTwoFloats(float a, float b) {
        return a + b;
    }

} // end of export C block
```

7.	Sync gradle and build the library


## Use native plugin - Unity
### Create project
1.	Open Unity and create a new project.
2.	Create folder **Plugins** in **Assets** folder. Put the compiled library in there.
3.	Create a new C# script **UseNativeLibrary**
4.	Add code to access the library in it:

```c#
using UnityEngine;
using System;
using System.Runtime.InteropServices;

public class UseNativeLibrary : MonoBehaviour {
    //Lets make our calls from the Plugin
    [DllImport("SimpleNativeLibrary")]
    private static extern int PrintANumber();

    [DllImport("SimpleNativeLibrary")]
    private static extern IntPtr PrintHello();

    [DllImport("SimpleNativeLibrary")]
    private static extern int AddTwoIntegers(int i1, int i2);

    [DllImport("SimpleNativeLibrary")]
    private static extern float AddTwoFloats(float f1, float f2);

    // Use this for initialization
    void Start()
    {
        Debug.Log(PrintANumber());
        Debug.Log(Marshal.PtrToStringAuto(PrintHello()));
        Debug.Log(AddTwoIntegers(2, 2));
        Debug.Log(AddTwoFloats(2.5F, 4F));
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
```

5.	In your scene, add an empty **GameObject** and drag **UseNativeLibrary** script to it.
6.	Press Run and you should see debug info in the console

