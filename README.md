# MTE380ProjectSoftware
Repository for MTE 380 Project Software 

### ****Coding Conventions****

#### Naming Conventions
- Branch Names: '<subtask>/<taskName>' (subtask and task name can be found in the task breakdown)
-   `variableNames` 
-   `Function_Name()` 
-   `CONSTANT_NAMES` 
-   `file_names` 
-   `type_defs` 
    -   Ex: 
        ```c
        typedef struct {
            int a;
            int b;
        } struct_name_t
        ```


#### Function Comments

Function comments should exist in at least the .h files. THey should follow the following format:
```c
/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void);
```

### Coding in VSCode

To code in vscode with good intelliSense, your `c_cpp_properties.json` file should look like this:

```c
{
    "configurations": [
        {
            "name": "STM32 F4",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/Core/Inc",
                "${workspaceFolder}/Drivers/CMSIS/Device/ST/STM32F4xx/Include",
                "${workspaceFolder}/Drivers/CMSIS/Include",
                "${workspaceFolder}/Drivers/STM32F4xx_HAL_Driver/Inc",
                "${workspaceFolder}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE",
                "USE_HAL_DRIVER",
                "STM32F401xE"
            ],
            "compilerPath": "<absolute path to arm-none-eabi-gcc compiler>",
            "cStandard": "gnu17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "gcc-arm",
            "compilerArgs": [
                "-mcpu=cortex-m4",
                "-mthumb"
            ]
        }
    ],
    "version": 4
}
```

Where the compilerPath is the only field that you need to change. 

### Building

You can build the project using these commands at the top-level of the repo:

```sh
make clean # Delete any previous build files
make # Build the executable for the dev version of the firmware. The .out file should appear in the build directory.
```

### Flashing