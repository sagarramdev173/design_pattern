## Factory design pattern

The Fectory method patterns provides a generalized way to create instance of an object and can be great way to hide implementation details for derived class.

## Problem 

Imagine that you’re creating a logistics management application. The first version of your app can only handle transportation by trucks, so the bulk of your code lives inside the Truck class.

After a while, your app becomes pretty popular. Each day you receive dozens of requests from sea transportation companies to incorporate sea logistics into the app.

Great news, right? But how about the code? At present, most of your code is coupled to the Truck class. Adding Ships into the app would require making changes to the entire codebase. Moreover, if later you decide to add another type of transportation to the app, you will probably need to make all of these changes again.

As a result, you will end up with pretty nasty code, riddled with conditionals that switch the app’s behavior depending on the class of transportation objects.


## Solution

The Factory Method pattern suggests that you replace direct object construction calls (using the new operator) with calls to a special factory method. Don’t worry: the objects are still created via the new operator, but it’s being called from within the factory method. Objects returned by a factory method are often referred to as products.

## Abstract factory design pattern

Abstract Factory is a creational design pattern, which solves the problem of creating entire product families without specifying their concrete classes.

## Problem it solves

let suppose users wants different company vehicles like honda,tata etc. you want to hide the implemnetation of vehcile created by differnt companies fatcory then you will use
abstract factory design pattern.

<img src="image-2.png" align ="centre" height="220" width= "320" />


<img src="image.png" align="right" height="220" width="320" />
<img src="image-1.png" align="left" height="220" width="320" />



