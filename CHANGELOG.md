# sdev

## 1.3.6.25

Fix incorrect inspection items

## 1.3.5.24

Add range checks that were overlooked in version 1.3.5.23

## 1.3.5.23

Upgrade to C++ 23

## 1.3.4.22

Add ItemDuration class and function

Refactor ServerTime class

## 1.3.3.21

Refactor Duration class

Use std::chrono instead of GetTickCount in world_thread_update

## 1.3.2.20

Fix filesystem failures (dll import)

## 1.3.1.19

Fix item mall bugs reported by users

* Remove session packet buffers
* Remove CClientToMgr buffer hacks
* Rewrite item mall code to behave like episode 4
* Fix incorrect value assignment at address 00407942 in dbAgent
* Replace dbAgent binary
* Update [dbo].[usp_Save_User_BuyPointItems2]

## 1.3.0.18

Add chaotic square support (see wiki)

## 1.2.2.17

~~Fix null target id when buying point items~~

## 1.2.1.16

Add initialization file class

Add an empty export

## 1.2.0.15

Add DataFile class

Update utilities

Fix failure message when frenzy is triggered

Increment major revision

## 1.1.10.14

Refactor frenzied skills

Refactor main function to make export easier

Assign g_nPayLetterEnable with write_memory instead of a session packet

## 1.1.9.13

Fix character list packet

## 1.1.8.12

Add warehouse item expiration gameLog

## 1.1.7.11

Add gameLog support

## 1.1.6.10

Add write_memory overload

Refactor projects

## 1.1.5.9

Update synergy class

Add color exploit workaround for guild names and character names (client)

## 1.1.4.7

Update item exchange logic and packets

Add item expiration function that runs once per minute

## 1.1.3.6

Fix warehouse item expiration

Add item duration packet to quest result, gift claim, and bank claim

## 1.1.2.5

Fix revenge episode macro

## 1.1.1.4

Fix recovery packet handler (client)

## 1.1.0.3

Add revenge support

## 1.0.1.2

Fix conversion from days to seconds

## 1.0.0.1

Increment major version

# sdev-db

## 1.0.3.5

Refactor main function to make export easier

## 1.0.2.4

Fix database character definition

Fix character list packet

## 1.0.1.3

Fix character list logic

## 1.0.0.2

Increment build version

## 1.0.0.1

Increment major version