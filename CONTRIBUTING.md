# Contributor Guidelines

First, we would like to thank you for contributing to the open source project!

This document contains information relavent to anyone wishing to contribute the [Faraday digital radio](https://faradayrf.com) CC430 firmware. Our core mission is laid out in our [Master Plan](https://faradayrf.com/faradayrf-master-plan/) and all contributions to the main project should help enable these goal set out.

[What should I know before I get started](#get_started)

* [Code of Coduct](#code_of_conduct)
* [Software Design and Purpose](#software_design)
* [Language(s)](#language)
* [Tools](#tools)

[How To Contribute](#how_to_contribute)

* [Bug Reports](#bug_reporting)
* [Suggesting Enhancements](#enhancement_suggestions)
* [Beginner Contributions](#beginner_contributions)
* [Pull Requests](#pull_requests)

[Styleguides](#styleguides)

* [C](#c_style)
* [Firmware Version Guide](#firmware_version_guide)

#What Should I Know Before I Get Started <a name="get_started"></a>
---

##Software Design and Purpose <a name="software_design"></a>
The Faraday CC430 firmware is responsible for providing basic "smart node" functionality. As described on the [Code Overview](https://faradayrf.com/code/) page, this firm provides both stand-alone operation and functionality when connected to a host computer.


## Language <a name="language"></a>
Faraday's firmware is written in [C](https://en.wikipedia.org/wiki/C_(programming_language)).


## Tools<a name="tools"></a>
Please use the tools of your choice but we recommend:

* [Code Composer Studio](http://www.ti.com/tool/ccstudio) - An IDE based on Eclipse provided by Texas Instruments.
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html) - An automatic code documentation tool. This is the defacto C tool and "Read The Docs" provides a method to import Doxygen.

# How To Contribute <a name="how_to_contribute"></a>

---

## Bug Reporting <a name="bug_reporting"></a>

Following these simple guidelines will help the maintainers better understand your bug report and to ensure a quality solution. Not all guidelines may be applicable to a given situation, please provide as much as possible.

* **Perform basic debugging**
  * Are you using the latest version?
  * Have you changed your configuration of both software or Faraday device from default? (if so please specify)
  * Are multiple programs running that may be interferring?
* **Use a clear and descriptive title****
* **Describe the exact steps used to reproduce the bug**
* **Describe the exact problem behavior you observed**
* **Provide a demonstration if possible**
  * An application script, log file, screenshots, video, etc...
* **Explain what behavior you expected to see and why**
* **When in doubt provide as much information as possible**!

## Enhancement Suggestions <a name="enhancement_suggestions"></a>

Suggesting enhancements is one of the most important factors to driving innovation within the Faraday digital amateur radio community! Please follow as best as possible these guidelines to ensure that maintainers clearly understand the request.

* **Use a clear and descriptive title**
* **Provide a descriptive overview of the enhancements operation(s)**
  * In addition to text screenshots, diagrams, etc... are welcome if they better explain your suggestion
* **Explain why this is a useful enhancement to the community**


## Begginer Contributions <a name="beginner_contributions"></a>

If you are not sure how to start off contributing to the project browse the tagged begginner issues below.

* Begginner Issues - Simple issues where the solution is likley a few lines of code or less
* Documentation Updates - Clear and consitant documenation is key to building a knowlegable and growing community

**TODO:** Add links to Github issue filters for the above.


##Pull Requests <a name="pull_requests"></a>

* Include examples/screenshots/videos of your pull request if applicable
* Include a detailed description of the pull requests purpose
* Follow our code [style guidelines](#styleguides)
 

#Styleguides <a name="styleguides"></a>
---

## C Style <a name="c_style"></a>

**TODO:** Implement clear C styleguide.

For now use:

* [Basic C Style Using Doxygen](https://wiki.icinga.org/display/Dev/Coding+and+documenting+style+guide)
* [Doxygen CheatSheet PDF](https://wiki.icinga.org/display/Dev/Coding+and+documenting+style+guide)

## Firmware Version Guide <a name="firmware_version_guide"></a>
Each firmware "Tag" or "Release" has a corresponding version embedded in the unit program that can be queried. This guide section shows how the current version is created. This should be done imediately prior to a pull request.

* Ensure all commits are made
* Obtain a shorten HASH of the HEAD commit: `git rev-list --max-count=1 --abbrev-commit --skip=# HEAD`
* Place this value as HEX into the `version = HASH_IN_HEX` global variable of `version.h`
  * e.g. HASH = a825d82 would be saved in variable as `version = 0xa825d82`
* Save and commit. Make sure to save with commit comment indicating version variable update.

