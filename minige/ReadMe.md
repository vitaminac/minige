## Dependencies Graph

* math
  * N/A
* physics
  * math
* platform
  * N/A
* renderer
  * math
  * physics
  * platform

## Best Practices

### Header Files

#### Naming Convention

Use *.hpp for C++ header and use .h only for C compatible header

#### Namespace

Never use `using namespace` and `using` in the header files, it will pollute the names for all the source files that include it.

#### Include

Only include the header files that are required for the definition, never include the extra header files for implementation usage, this should be done in the source files.

##### Order

##### Inside of Header Files

0. so.h
1. Standard C++ library headers 
2. Third party library headers
3. Our own headers with alias
4. Our own headers with relative path

##### Inside of Source Files

0. Our header of prototype definition
1. Standard C++ library headers 
2. Third party library headers
3. Our own headers with alias
4. Our own headers with relative path

### Local Variables

* Use auto and const when possible

### Casting

* prefer static_cast than C style casting