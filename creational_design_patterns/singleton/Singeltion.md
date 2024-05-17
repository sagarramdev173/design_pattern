# Singleton

Singleton is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.

The Singleton pattern solves two problems :- 

1 Ensure that a class has just a single instance.

2 Provide a global access point to that instance.

# steps to create single design pattern

* Make the default constructor private, to prevent other objects from using the new operator with the Singleton class.
  
* Create a static creation method that acts as a constructor. Under the hood, this method calls the private constructor to create an object and saves it in a static field. All following calls to this method return the cached object.
  





