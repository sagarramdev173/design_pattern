# Observer (Also known as: Event-Subscriber) Design pattern

Observer is a behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

# Problem

Imagine that you have two types of objects: a Customer and a Store. The customer is very interested in a particular brand of product (say, it’s a new model of the iPhone) which should become available in the store very soon.

# Solution

The object that has some interesting state is often called subject, but since it’s also going to notify other objects about the changes to its state, we’ll call it publisher. All other objects that want to track changes to the publisher’s state are called subscribers.

# UML Diagram

```plantuml
@startuml
title Observer Pattern Implementation

interface IPublisher {
  + {abstract} attach(ISubscriber*): void
  + {abstract} detach(ISubscriber*): void
  + {abstract} notifySubscribers(string): void
}

class Publisher {
  - subscribers: vector<ISubscriber*>
  + attach(ISubscriber*): void
  + detach(ISubscriber*): void
  + notifySubscribers(string): void
}

interface ISubscriber {
  + {abstract} notify(string): void
}

class User {
  - userid: int
  + notify(string): void
}

Publisher ..|> IPublisher
Publisher "1" o.. "*" ISubscriber
User <|.. ISubscriber

@enduml
```
