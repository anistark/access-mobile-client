# Access Mobile Client Architecture

## Access Secure Network:
<!--ToDo: elaborate this-->
The Access Secure Network (ASN) module combines OpenSSL and Ed25519 signature scheme to securely identify users. Each user is uniquely identified by their own pub-priv key pair.

## Access Request Protocol:
<!--ToDo: elaborate this-->
Access Requests follow a strict protocol between Access Mobile Client and Access Core Server. Requests are initiated by Client and Decisions (grant or deny) are made by Server. Access Core Server is executed on the target device for which Access is being granted or denied.

## Policy Creation:
<!--ToDo: elaborate this-->
Delegations and Obligations are defined by the device owner and encoded into Policies. Access Mobile Client allows the owner to create Policies for their devices.

## Policy Update:
<!--ToDo: elaborate this-->
After Policies are created they need to be updated into the target device.

# xxx
<!--
ToDo: write this
-->
xxx
