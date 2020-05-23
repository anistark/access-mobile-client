# Project Scope (Scope)
[Scope]: #Scope

## Frontmatter
[frontmatter]: #frontmatter
```yaml
title: Access Mobile Client
stub: access-mobile-client
document: SCOPE
version: 0000
maintainer: Bernardo A. Rodrigues <bernardo.araujo@iota.org>
contributors: [Vladimir Vojnovic <vladimir.vojnovic@nttdata.ro>, Robert Černjanski <robert.cernjanski@nttdata.ro>]
sponsor: Jakub Cech <jakub.cech@iota.org>
licenses: ["Apache-2.0"]
updated: 2020-05-21
```

## License
[license]: #license
<!--
Please specify licenses here and in the frontmatter.
-->
All code is licensed under the [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0.html)., all text and images are licensed under the [Creative Commons Attribution 4.0 International](https://creativecommons.org/licenses/by/4.0/).

## Language
[language]: #language
<!--
Do not change this section.
-->
The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in RFC 2119.

## Versioning
[versioning]: #versioning
<!--
Do not change this section.
-->
These documents MUST use incremental numbering. New documents always start at 0000. Subsequent revisions to each RFI, RFP and RFC will have their number increased by one.

Software releases will follow [strict semantic versioning](https://semver.org/).

## Hierarchy
[hierarchy]: #hierarchy
<!--
Do not change this section.
-->
All documents in this specification are understood to flow from this document and be bound to its licenses and language as described above.

## Summary
[summary]: #summary
<!--
One paragraph explanation of the feature.
-->

Access Mobile Client is used to interact with Access-controlled devices. It is the main User Interface that allows device owners to create Policies and device users to initiate Access Requests.

## Motivation
[motivation]: #motivation
<!--
Why are we doing this? What use cases does it support? What is the expected outcome?
-->

There needs to be a way that users can interact with the Access-controlled devices in a friendly manner.

Users should not need to know JSON or Access Request Protocol to interact with the Product.

## Product Introduction
[product]: #product
<!--
Talk about the business reasons for the product's existence, what it is for and who it serves.
-->
DLT-based Access control enables interesting business opportunities around rental and sharing of devices, as well as related services.

The permission-less ledger allows for immutable and auditable registration of access policies and access events.

## Stakeholders
[stakeholders]: #stakeholders
<!--
- Who are the stakeholders?
- How has the community been involved?
-->
The list of Stakeholders can be summarized as:
- [IOTA Foundation](https://iota.org).
- IOTA Community.
- [XAIN AG](https://www.xain.io/).

The IOTA Foundation is working on the integration of FROST into the IOTA Ecosytem, which then gives birth to IOTA Access.

The IOTA Community (Corporate Partners, developers) will integrate IOTA Access into their own products.

XAIN AG. was the initial implementer of the product (previously known as [FROST](https://xain-documentation.readthedocs.io/en/latest/Frost/)), so it is in their interest what Access eventually evolves into.

## Guide-level explanation
[guide-level-explanation]: #guide-level-explanation
<!--
Explain the proposal as if it was already included in the language and you were
teaching it to another programmer. That generally means:

- Introducing new named concepts.
- Explaining the feature largely in terms of examples.
- Explaining how programmers should *think* about the feature, and how it should impact the
 way they use this software. It should explain the impact as concretely as possible.
- If applicable, provide sample error messages, deprecation warnings, or migration guidance.
- If applicable, describe the differences between teaching this to existing programmers
and new programmers.
-->

### Access Secure Network:
<!--ToDo: elaborate this-->
The Access Secure Network (ASN) module combines OpenSSL and Ed25519 signature scheme to securely identify users. Each user is uniquely identified by their own pub-priv key pair.

### Access Request Protocol:
<!--ToDo: elaborate this-->
Access Requests follow a strict protocol between Access Mobile Client and Access Core Server. Requests are initiated by Client and Decisions (grant or deny) are made by Server. Access Core Server is executed on the target device for which Access is being granted or denied.

### Policy Creation:
<!--ToDo: elaborate this-->
Delegations and Obligations are defined by the device owner and encoded into Policies. Access Mobile Client allows the owner to create Policies for their devices.

### Policy Update:
<!--ToDo: elaborate this-->
After Policies are created they need to be updated into the target device.

## Prior art
[prior-art]: #prior-art
<!--
Discuss prior art, both the good and the bad, in relation to this proposal.
A few examples of what this can include are:

- For language, library, tooling, and compiler proposals: Does this feature
exist in other similar projects and what experience have their community had?
- For community proposals: Is this done by some other community and what were their
experiences with it?
- For other teams: What lessons can we learn from what other communities have done here?
- Papers: Are there any published papers or great posts that discuss this? If you
have some relevant papers to refer to, this can serve as a more detailed theoretical background.

If there is no prior art, that is fine - your ideas are interesting to us whether
they are brand new or if it is an adaptation from other projects.
-->

Here's a list of resources on XAIN FROST:

* [Conference Paper] **Owner-centric sharing of physical resources, data, and data-driven insights in digital ecosystems**: https://spiral.imperial.ac.uk:8443/handle/10044/1/77522
* [ReadTheDocs] **FROST — Xain Documentation**: https://xain-documentation.readthedocs.io/en/latest/Frost/
* [Video Presentation] **Michael Huth (CTO) presents FROST at Birmingham**: https://www.youtube.com/watch?v=2mHQrmGt7CA
* [Medium Article] **A technical overview of XAIN Embedded Extension**: https://medium.com/xain/a-technical-overview-of-xain-embedded-905678f5b236
* [Medium Article] **Overview of the XAIN Pilot for Porsche Vehicles**: https://medium.com/xain/part-1-technical-overview-of-the-porsche-xain-vehicle-network-f70bb117be16
* [Medium Article] **The Porsche-XAIN Vehicle Blockchain Network: A Technical Overview**: https://medium.com/next-level-german-engineering/the-porsche-xain-vehicle-blockchain-network-a-technical-overview-e1f48c40e73d
* [Marketing Video] **XAIN and Porsche: Results of the pilot project**: https://www.youtube.com/watch?v=KvyF78RTj18
* [Presentation Slides] **Access Control via Belnap Logic: Intuitive, Expressive, and Analyzable Policy Composition**: http://www.doc.ic.ac.uk/~mrh/talks/BelnapTalk.pdf

## Unresolved questions
[unresolved-questions]: #unresolved-questions

<!--
- What parts of the design do you expect to resolve through the spec process
before this gets merged?
- What parts of the design do you expect to resolve through the implementation
of this product?
- What related issues do you consider out of scope for this prodect that could
be addressed in the future independently of the solution that comes out it?
-->
 - After Android is simplified for public release, do we move Access Mobile Client implementation into:
   - [Spark Wallet](https://github.com/iotaledger/spark-wallet)
   - [Trinity](https://trinity.iota.org/) 2.0 (WIP)
 - After we completely remove Policy Store and do Policy Update completely based on IOTA Nodes, how will the Access Mobile Client be affected?

## Future possibilities
[future-possibilities]: #future-possibilities
<!--
Think about what the natural extension and evolution of your proposal would
be and how it would affect the language and project as a whole in a holistic
way. Try to use this section as a tool to more fully consider all possible
interactions with the project in your proposal.

Also consider how the this all fits into the roadmap for the project
and of the relevant sub-team.

If you have tried and cannot think of any future possibilities,
you may simply state that you cannot think of anything.
-->

Eventually all functionality implemented in the Access Mobile Client will become part of the Trinity Wallet.
