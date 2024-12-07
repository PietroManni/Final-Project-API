# Electric Car Charging Station Management System
## Overview
This program simulates the management system of a network of electric car charging stations. It allows users to manage stations, cars, and plan travel routes based on the stations' locations and vehicle autonomy. The system is designed to work with a binary tree to store charging stations, each with a list of cars and their battery autonomy. The program supports operations like adding or removing stations and cars, planning travel routes between stations, and calculating optimal paths based on vehicle autonomy.

## Features
**Add Charging Stations:** Users can add new charging stations to the system. Each station has a set distance and can have a number of cars with various battery autonomies.

**Demolish Stations:** Stations can be removed from the network.

**Add or Remove Cars:** Users can add or remove cars from specific stations, with each car having a specific autonomy value.

**Plan Route:** The program can compute a path between two charging stations based on the car's autonomy, considering the maximum autonomy available at each station.

**Show Path:** After calculating the route, the program shows the list of stations along the optimal path between two stations.

## Data Structures
**Binary Search Tree (BST)**
The stations are stored in a binary search tree (BST), where each node represents a station. The tree is organized based on the station distances, allowing for efficient searches and insertions. Each station also stores the cars present at that station along with their respective autonomies.

**Linked List for Path Calculation**
The program uses a linked list to store the stations included in the calculated route. This allows for easy traversal and manipulation when planning routes between stations.


## Conclusion
This program is a comprehensive solution for managing a network of electric car charging stations, supporting dynamic operations such as adding/removing stations and cars, and planning optimal travel routes based on vehicle autonomy. The code is structured to support efficient searching and path calculation using binary trees and linked lists.
