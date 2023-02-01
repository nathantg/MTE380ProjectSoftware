# MTE380ProjectSoftware
Repository for MTE 380 Project Software 

### ****Coding Conventions****

#### Naming Conventions
- Branch Names: 'subtask/taskName' (subtask and task name can be found in the task breakdown)
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

### Building

You can build the project using these commands at the top-level of the repo:

```sh
make clean # Delete any previous build files
make # Build the executable for the dev version of the firmware. The .out file should appear in the build directory.
```

### Flashing
