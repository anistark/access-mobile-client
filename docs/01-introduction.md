# IOTA Access

Check [IOTA Access main repository](https://github.com/iotaledger/access) for Access Core.

IOTA Access Mobile Client is used to interact with Access-controlled devices. It is the main User Interface that allows device owners to create Policies and device users to initiate Access Requests.

Eventually all functionality implemented in the Access Mobile Client will become part of the IOTA Trinity Wallet, which means it will be the main User Interface with human beings (via mobile and desktop platforms).

# Use Cases

Imagine the following scenarios.

## Scenario 1

Alice owns a Device that she wants to rent for Bob for x IOTAs. Bob will be able to use this device after transferring x IOTAs to the Device's (or Alice's) Wallet. **IOTA Access** enables this kind of scenario.

Alice uses Access Mobile Client to create the Policy that delegates device access to renters. Alice stores the Policy on an IOTA Permanode.

Bob uses Access Mobile Client to initiate Access Requests, and his requests are stored on the Tangle.

## Scenario 2
Alice is Carol's mother. Carol just turned 18 and she wants to drive Alice's car. Alice writes a Policy where she allows Carol to drive her car only under specific conditions (such as time, insurance, and GPS location).

Carol's ability to access the car is dictated by Access Policy written by her mom. Alice uploads her Policy to the vehicle, and Carol makes Access Requests.

Alice's uses Access Mobile Client to create the Policy that delegates device access to renters. Alice stores the Policy on an IOTA Permanode.

Carol's uses Access Mobile Client to initiate Access Requests, and her requests are stored on the Tangle.

## Scenario 3
Alice owns a company that functions in a building with smart locks. Alice writes a Policy where her employees are allowed to enter the building only under specific conditions (such as time, employee ID, clearance level).

Employee's ability to access the building is dictated by the Policy written by Alice.

Alice's uses Access Mobile Client to create the Policy that delegates device access to renters. Alice stores the Policy on an IOTA Permanode.

Employees use Access Mobile Client to initiate Access Requests, and their requests are stored on the Tangle.
